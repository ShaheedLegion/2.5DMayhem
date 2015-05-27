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

BackgroundScroller::BackgroundScroller(Universe *universe)
    : m_universe(universe), m_speed(0.f) {}

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
}

// Override Renderable
void BackgroundScroller::tick(float delta) {
  for (auto &i : m_layers) {
    i.position += (i.speed * m_speed);
    sf::Vector2u size(i.sprite.getTexture()->getSize());

    i.sprite.setTextureRect(
        sf::IntRect(static_cast<int>(i.position), 0, size.x, size.y));
  }

  for (auto &i : m_actors) {
    i.UpdateSprite(delta);
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
  layer.position = 0.f;
  layer.speed = static_cast<float>(idx);
}

void BackgroundScroller::AddMapOverlay(const std::string &mapData,
                                       const std::string &mapTile) {
  TextureLoader &loader(m_universe->GetTextureLoader());
  SpriteManager &spriteMan(m_universe->GetSpriteManager());

  std::pair<bool, int> mapTexId{loader.Load(mapData)};
  sf::Texture &mapTex = loader.Get(mapTexId.second);

  std::pair<bool, int> tileTexId{loader.Load(mapTile)};
  sf::Texture &tileTex = loader.Get(tileTexId.second);

  m_overlays.push_back(TileMap(spriteMan.Get(mapTexId.second, mapTex),
                               spriteMan.Get(tileTexId.second, tileTex)));

  TileMap &tileMap{m_overlays[m_overlays.size() - 1]};
  // Now that we have the sprites, we need to populate the map data vector in
  // the TileMap struct.
  sf::Vector2u size{mapTex.getSize()};
  sf::Image img{mapTex.copyToImage()};
  const int *pixels{reinterpret_cast<const int *>(img.getPixelsPtr())};
  unsigned int len{size.x * size.y};

  while (--len > 0)
    tileMap.inputData.push_back(*pixels++);
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

} // namespace d2
