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

#ifndef _SPRITE_MANAGER_
#define _SPRITE_MANAGER_

#include <SFML/Graphics/Sprite.hpp>

#include <map>

namespace d2 {

class SpriteManager {
public:
  SpriteManager() {}
  ~SpriteManager() {}

  sf::Sprite &Get(int id, sf::Texture &texture) {
    // This will just return an empty texture if the id is not
    // found in the map.
    auto &it = m_sprites.find(id);
    if (it == m_sprites.end()) {
      sf::Sprite sprite(texture);
      m_sprites[id] = sprite;
      return m_sprites[id];
    }
    return it->second;
  }

protected:
  std::map<int, sf::Sprite> m_sprites;
};

} // namespace d2

#endif // _SPRITE_MANAGER_