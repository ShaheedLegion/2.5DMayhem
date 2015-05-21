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

#include <SFML/OpenGL.hpp>
#include "game_states/GameStateStart.h"
#include "game/Universe.hpp"

namespace d2 {

GameStateStart::GameStateStart(StateManager *manager)
    : GameState(manager), m_bgScroller(manager->GetUniverse()) {
  m_bgScroller.AddLayer("res\\layer-1-sky.png");
  m_bgScroller.AddLayer("res\\layer-2-mountain.png");
  m_bgScroller.AddLayer("res\\layer-3-ground.png");
}

GameStateStart::~GameStateStart() {}

// Override sf::Drawable
void GameStateStart::draw(sf::RenderTarget &target,
                          sf::RenderStates states) const {

  m_bgScroller.draw(target, states);
}

// Override Renderable
void GameStateStart::tick(float delta) { m_bgScroller.tick(delta); }

// Override Inputable
void GameStateStart::handleInput(sf::Event &evt) {
  if (evt.type == sf::Event::KeyPressed) {
    if (evt.key.code == sf::Keyboard::Left) {
      m_bgScroller.SetSpeed(m_bgScroller.GetSpeed() - 0.1f);
    } else if (evt.key.code == sf::Keyboard::Right) {
      m_bgScroller.SetSpeed(m_bgScroller.GetSpeed() + 0.1f);
    }
  }
}

} // namespace d2
