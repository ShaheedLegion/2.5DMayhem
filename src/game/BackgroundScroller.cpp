// Copyright (c) 2015, Shaheed Abdol
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
// OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include "game/BackgroundScroller.h"
#include "game/Universe.hpp"

namespace d2 {

BackgroundScroller::BackgroundScroller(Universe *universe,
                                       util::Transform &transform)
    : m_universe(universe), m_transform(transform) {}

BackgroundScroller::~BackgroundScroller() {}

// Override sf::Drawable
void BackgroundScroller::draw(sf::RenderTarget &target,
                              sf::RenderStates states) const {
  for (const auto &i : m_layers) {
    target.draw(i.sprite);
  }

  for (const auto &i : m_actors) {
    target.draw(i.GetSprite());
  }

  for (const auto &i : m_overlays) {
    target.draw(i.overlay);
  }
}

// Override Renderable
void BackgroundScroller::tick(float delta) {
  // Use the transformable to get the speed/position attributes.
  m_transform.Update();

  for (auto &i : m_layers) {
    i.position = m_transform.GetPositionOffsetX(i.position, i.speed);

    sf::Vector2u size(i.sprite.getTexture()->getSize());
    i.sprite.setTextureRect(sf::IntRect(i.position, 0, size.x, size.y));
  }

  // For all the right reasons, there should only be on overlay. And the sprites
  // should be on top ov it.
  for (auto &i : m_overlays) {
    i.position = m_transform.GetPositionOffsetX(i.position, i.speed);

    sf::Vector2u size(m_universe->GetW(), m_universe->GetH());
    i.overlay.setTextureRect(sf::IntRect(i.position, 0, size.x, size.y));
  }

  for (auto &i : m_actors) {
    int positionX = m_transform.GetPositionOffsetX(i.GetX(), i.GetSpeed());
    int positionY = m_transform.GetPositionOffsetY(i.GetY(), i.GetSpeed());
    // Apply "gravity" to the actor here ... and take care of collision
    // handling.
    i.UpdateSprite(delta, positionX, positionY);
  }
}

void BackgroundScroller::AddLayer(const std::string &name) {

  TextureLoader &loader(m_universe->GetTextureLoader());
  SpriteManager &spriteMan(m_universe->GetSpriteManager());

  std::pair<bool, int> texId(loader.Load(name));
  sf::Texture &texture = loader.Get(texId.second);
  texture.setRepeated(true);

  m_layers.push_back(Layer(spriteMan.Get(texId.second, texture)));
  int idx = m_layers.size();

  Layer &layer{m_layers[idx - 1]};
  layer.position = 0;
  layer.speed = idx;
}

void BackgroundScroller::AddMapOverlay(const std::string &mapData,
                                       const std::string &mapTile) {
  TextureLoader &loader(m_universe->GetTextureLoader());
  SpriteManager &spriteMan(m_universe->GetSpriteManager());

  std::pair<bool, int> mapTexId{loader.Load(mapData)};
  sf::Texture &mapTex = loader.Get(mapTexId.second);

  std::pair<bool, int> tileTexId{loader.Load(mapTile)};
  sf::Texture &tileTex = loader.Get(tileTexId.second);

  // Get an empty texture to use for this sprite.
  std::pair<bool, int> overlayTexId(loader.Load("null"));
  sf::Texture &overlayTex = loader.Get(overlayTexId.second);

  m_overlays.push_back(TileMap(spriteMan.Get(mapTexId.second, mapTex),
                               spriteMan.Get(tileTexId.second, tileTex),
                               spriteMan.Get(overlayTexId.second, overlayTex)));

  TileMap &tileMap{m_overlays[m_overlays.size() - 1]};
  tileMap.speed = m_overlays.size() + 3;

  // Now that we have the sprites, we need to populate the map data vector in
  // the TileMap struct.
  sf::Vector2u size{mapTex.getSize()};
  tileMap.width = size.x;
  tileMap.height = size.y;
  sf::Image img{mapTex.copyToImage()};
  const int *pixels{reinterpret_cast<const int *>(img.getPixelsPtr())};
  unsigned int len{size.x * size.y};

  while (len-- > 0)
    tileMap.inputData.push_back(*pixels++);

  sf::Image overlayImg;
  sf::Image tileImg{tileTex.copyToImage()};
  overlayImg.create(tileTex.getSize().x * tileMap.width,
             tileTex.getSize().y * tileMap.height, sf::Color(0, 0, 0, 0));
  for (int y = 0; y < tileMap.height; ++y) {
    for (int x = 0; x < tileMap.width; ++x) {
      int index = y * tileMap.width + x;
      if (tileMap.inputData[index] >> 24 != 0) {
        // Map the input tile locations
        int xLocation = x * tileTex.getSize().x;
        int yLocation = y * tileTex.getSize().y;
        overlayImg.copy(tileImg, xLocation, yLocation);
      }
    }
  }

  overlayTex.loadFromImage(overlayImg);
}

void BackgroundScroller::AddActor(const std::string &sheet, int hFrames,
                                  int vFrames, int frameDelta) {
  TextureLoader &loader(m_universe->GetTextureLoader());
  SpriteManager &spriteMan(m_universe->GetSpriteManager());

  std::pair<bool, int> texId(loader.Load(sheet));
  sf::Texture &texture = loader.Get(texId.second);

  m_actors.push_back(SpriteActor(spriteMan.Get(texId.second, texture), hFrames,
                                 vFrames, frameDelta));
}

sf::Sprite &BackgroundScroller::GetLayer(int idx) {
  if (idx >= 0 && idx < m_layers.size())
    return m_layers[idx].sprite;

  return sf::Sprite();
}

// Called once all the resources have been added to place the actors in the
// correct positions on the stage.
void BackgroundScroller::SetupStage() {
  // Here we walk through the first column of pixels in the source data to
  // discover where the first usable tile is. Then we position the character on
  // that tile.
  TileMap &tileMap{m_overlays[m_overlays.size() - 1]};
  sf::Vector2u size{tileMap.tile.getTexture()->getSize()};

  for (int y = 0; y < tileMap.height; ++y) {
    int index = y * tileMap.width + 0;
    if (tileMap.inputData[index] >> 24 != 0) {
      // We have the first non-empty tile in this column
      int yLocation = y * size.y;
      m_actors[0].SetLocation(0, yLocation - m_actors[0].GetFrameHeight());
      return;
    }
  }
}

} // namespace d2
