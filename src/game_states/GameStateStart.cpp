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
    : GameState(manager), m_bgScroller(manager->GetUniverse(), m_transform) {
  m_bgScroller.AddLayer("res\\level1\\layer-1-sky.png");
  m_bgScroller.AddLayer("res\\level1\\layer-2-mountain.png");
  m_bgScroller.AddLayer("res\\level1\\layer-3-forest.png");
  m_bgScroller.AddMapOverlay("res\\level1\\level.png", "res\\level1\\tile.png");
  m_bgScroller.AddActor("res\\level1\\chiraku.png", 4, 1, 15);

  m_transform.SetX(0);
  m_transform.SetY(0);
  m_transform.SetZ(0);
  m_transform.SetDX(0);
  m_transform.SetDXLimits(-5, 5);
  m_transform.SetDY(0);
  m_transform.SetDYLimits(0, 0);
  m_transform.SetDZ(0);
  m_transform.SetDZLimits(0, 0);

  // Load all the resources and set up all the transform data.
  m_bgScroller.SetupStage();
}

GameStateStart::~GameStateStart() {}

// Override sf::Drawable
void GameStateStart::draw(sf::RenderTarget &target,
                          sf::RenderStates states) const {

  m_bgScroller.draw(target, states);
}

// Override Renderable
void GameStateStart::tick(float delta) {
  m_bgScroller.tick(delta);
}

// Override Inputable
// Each state handles its own "transformations", which deal with
// rotating/translating the current view according to the user input.
void GameStateStart::handleInput(sf::Event &evt) {
  if (evt.type == sf::Event::KeyPressed) {
    if (evt.key.code == sf::Keyboard::Left) {
      m_transform.SetDX(m_transform.GetDX() - 1);
    } else if (evt.key.code == sf::Keyboard::Right) {
      m_transform.SetDX(m_transform.GetDX() + 1);
    }
  }
}

} // namespace d2
