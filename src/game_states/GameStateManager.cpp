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

#include "game_states/GameStateManager.h"
#include "game_states/GameStateStart.h"
#include "game_states/GameState.h"
#include "game/Universe.hpp"

namespace d2 {

GameStateManager::GameStateManager(Universe *universe)
    : m_universe(universe), m_currentState(nullptr), m_scale(1.0f) {
  // Create the game states.
  m_states.push_back(new GameStateStart(this));
  m_currentState = m_states[0];
}

GameStateManager::~GameStateManager() {
  // Delete the game states.
  m_currentState = nullptr;
  for (auto state : m_states)
    delete state;
}

// Override sf::Drawable
void GameStateManager::draw(sf::RenderTarget &target,
                            sf::RenderStates states) const {
  if (!m_currentState)
    return;

  m_currentState->draw(target, states);
}

// Override Renderable
void GameStateManager::tick(float delta) {
  if (!m_currentState)
    return;

  m_currentState->tick(delta);
}

// Override Inputable
void GameStateManager::handleInput(sf::Event &evt) {
  // We handle some input events on our own, then pass along the rest of the
  // events to the individual game states.

  if (evt.type == sf::Event::MouseWheelMoved) {
    if (evt.mouseWheel.delta < 0) {
      m_scale -= 0.1f;
      if (m_scale < 0.1f)
        m_scale = 0.1f;
    } else {
      m_scale += 0.1f;
      if (m_scale > 10.0f)
        m_scale = 10.0f;
    }

    if (!m_currentState)
      return;
    m_currentState->handleInput(evt);
  }
}

float GameStateManager::GetScale() const { return m_scale; }
Universe *GameStateManager::GetUniverse() const { return m_universe; }

} // namespace d2
