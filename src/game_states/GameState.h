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

#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include "interfaces/Interfaces.h"
#include "util/Transform.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

namespace d2 {

class GameState : public Renderable, public Inputable {
public:
  GameState(StateManager *manager) : m_manager(manager) {}

  ~GameState() {}

protected:
  StateManager *m_manager;
  util::Transform m_transform;
};

} // namespace d2

#endif // _GAME_STATE_H_