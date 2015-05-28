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

#ifndef BACKGROUND_SCROLLER_H_
#define BACKGROUND_SCROLLER_H_

#include "interfaces/Interfaces.h"
#include "util/SpriteActor.hpp"
#include "util/Transform.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <vector>

namespace d2 {

class BackgroundScroller : public Renderable {
public:
  BackgroundScroller(Universe *universe, util::Transform &transform);
  ~BackgroundScroller();

  // Override sf::Drawable
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;

  // Override Renderable
  virtual void tick(float delta) override;

  void AddLayer(const std::string &name);
  void AddMapOverlay(const std::string &mapData, const std::string &mapTile);
  void AddActor(const std::string &sheet, int hFrames, int vFrames,
                int frameDelta);

  sf::Sprite &GetLayer(int idx);

protected:
  struct Layer {
    int speed;
    int position;
    sf::Sprite &sprite;

    Layer(sf::Sprite &sprite) : sprite(sprite) {}
  };
  std::vector<Layer> m_layers;

  std::vector<d2::SpriteActor> m_actors;

  struct TileMap {
    int speed;
    int position;
    sf::Sprite &inputMap;
    sf::Sprite &tile;
    std::vector<int> inputData;

    TileMap(sf::Sprite &inputMap, sf::Sprite &tile)
        : inputMap(inputMap), tile(tile), speed(0.f), position(0.f) {}
  };

  std::vector<TileMap> m_overlays;

  Universe *m_universe;
  util::Transform &m_transform;
};

} // namespace d2

#endif // BACKGROUND_SCROLLER_H_
