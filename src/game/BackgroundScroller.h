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
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <vector>

namespace d2 {

class BackgroundScroller : public Renderable {
public:
  BackgroundScroller(Universe *universe);
  ~BackgroundScroller();

  // Override sf::Drawable
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;

  // Override Renderable
  virtual void tick(float delta) override;

  void AddLayer(const std::string &name);

  float GetSpeed() const { return m_speed; }
  void SetSpeed(float speed) { m_speed = speed; }

protected:
  struct Layer {
    float speed;
    float position;
    sf::Sprite sprite;
  };
  std::vector<Layer> m_layers;

  Universe *m_universe;
  float m_speed;
};

} // namespace d2

#endif // BACKGROUND_SCROLLER_H_
