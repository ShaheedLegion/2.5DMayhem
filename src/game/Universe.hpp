#ifndef _UNIVERSE_HPP_
#define _UNIVERSE_HPP_

#include <SFML/Graphics/RenderStates.hpp>
#include "resources/TextureLoader.hpp"
#include "resources/SpriteManager.hpp"
#include "interfaces/Interfaces.h"

namespace d2 {

class Universe : public Renderable, public Inputable {
public:
  Universe(...) {
    std::pair<bool, int> texId(loader.Load("res\\forest_bg.png"));
    sf::Texture &texture = loader.Get(texId.second);
    m_sprite = spriteManager.Get(texId.second, texture);
  }
  ~Universe() {}

  // Override sf::Drawable
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override {
    target.draw(m_sprite);
  }

  // Override Renderable
  virtual void tick(float delta) override {}

  // Override Inputable
  virtual void handleInput(sf::Event &evt) override {
    if (evt.type == sf::Event::MouseMoved) {
      m_sprite.setPosition(sf::Vector2f(evt.mouseMove.x, evt.mouseMove.y));
    } else if (evt.type == sf::Event::MouseWheelMoved) {
      static float scale = 1.0f;
      if (evt.mouseWheel.delta < 0) {
        scale -= 0.1f;
        if (scale < 0.1f)
          scale = 0.1f;
      } else {
        scale += 0.1f;
        if (scale > 10.0f)
          scale = 10.0f;
      }
      m_sprite.setScale(sf::Vector2f(scale, scale));
    }
  }

protected:
  TextureLoader loader;
  SpriteManager spriteManager;
  sf::Sprite m_sprite;
};
} // namespace d2

#endif // _UNIVERSE_HPP_