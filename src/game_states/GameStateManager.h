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

#ifndef _GAME_STATE_MANAGER_H
#define _GAME_STATE_MANAGER_H

#include "interfaces/Interfaces.h"

#include <vector>

namespace d2 {
class Universe;
class GameState;

class GameStateManager : public StateManager,
                         public Renderable,
                         public Inputable {
public:
  GameStateManager(Universe *universe);

  ~GameStateManager();

  // Override sf::Drawable
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;

  // Override Renderable
  virtual void tick(float delta) override;

  // Override Inputable
  virtual void handleInput(sf::Event &evt) override;

  // Override StateManager
  virtual float GetScale() const override;
  virtual Universe *GetUniverse() const override;

protected:
  std::vector<GameState *> m_states;
  Universe *m_universe;
  GameState *m_currentState;
  float m_scale;
};

} // namespace d2

#endif // _GAME_STATE_MANAGER_H