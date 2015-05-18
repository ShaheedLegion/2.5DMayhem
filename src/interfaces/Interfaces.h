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

#ifndef _INTERFACES_H_
#define _INTERFACES_H_

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>

namespace d2 {

class Renderable : public sf::Drawable {
public:
  virtual ~Renderable();

  // Tick the component with the supplied adjustment to make a smooth 60fps.
  virtual void tick(float adjustment) = 0;
};

class Inputable {
public:
  virtual ~Inputable();

  // Handle input on the component.
  virtual void handleInput(sf::Event &event) = 0;
};

}; // namespace d2

#endif // _INTERFACES_H_