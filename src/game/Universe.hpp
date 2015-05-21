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

#ifndef _UNIVERSE_HPP_
#define _UNIVERSE_HPP_

#include <SFML/Graphics/RenderStates.hpp>
#include "resources/TextureLoader.hpp"
#include "resources/SpriteManager.hpp"
#include "interfaces/Interfaces.h"
#include "game_states/GameStateManager.h"

namespace d2 {

class Universe : public Renderable, public Inputable {
public:
  Universe() : m_stateManager(this) {}
  ~Universe() {}

  // Override sf::Drawable
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override {
    m_stateManager.draw(target, states);
  }

  // Override Renderable
  virtual void tick(float delta) override { m_stateManager.tick(delta); }

  // Override Inputable
  virtual void handleInput(sf::Event &evt) override {
    m_stateManager.handleInput(evt);
  }
  // The texture loader and sprite manager are global objects, and are, in a
  // sense, handled as if they were singletons. This is thy the universe
  // object
  // will be accessible from any class in the game - or it should be.
  TextureLoader &GetTextureLoader() { return loader; }
  SpriteManager &GetSpriteManager() { return spriteManager; }

protected:
  TextureLoader loader;
  SpriteManager spriteManager;
  GameStateManager m_stateManager;
};

} // namespace d2

#endif // _UNIVERSE_HPP_