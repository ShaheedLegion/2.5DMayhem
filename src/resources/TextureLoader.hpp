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

#include <SFML/Graphics/Texture.hpp>

#include <map>

#include "util/Utilities.hpp"

#ifndef _TEXTURE_LOADER_H_
#define _TEXTURE_LOADER_H_

namespace d2 {

class TextureLoader {
public:
  TextureLoader() {}
  ~TextureLoader() {}

  std::pair<bool, int> Load(const std::string &name) {
    int highest = m_textures.size();
    sf::Texture &tex = m_textures[highest];

    bool loaded = tex.loadFromFile(name);

    // Apply a shim which only works on Windows so far.
    if (!loaded) {
      std::string path;
      util::GetQualifiedPath(name, &path);
      loaded = tex.loadFromFile(path);
    }
    // Make sure we are using high quality (anti-aliased) textures.
    tex.setSmooth(true);

    return std::pair<bool, int>(loaded, highest);
  }

  sf::Texture &Get(int id) {
    // This will just return an empty texture if the id is not
    // found in the map.
    return m_textures[id];
  }

protected:
  std::map<int, sf::Texture> m_textures;
};
} // namespace d2

#endif // _TEXTURE_LOADER_H_