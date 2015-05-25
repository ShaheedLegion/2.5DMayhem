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

#ifndef _SPRITE_ACTOR_H_
#define _SPRITE_ACTOR_H_
#include <SFML/Graphics/Sprite.hpp>

namespace d2 {

class SpriteActor {
public:
  SpriteActor(const sf::Sprite &sprite)
      : m_sprite(sprite), m_currentFrame(0), m_horizontalFrames(1),
        m_verticalFrames(1) {}

  SpriteActor(const sf::Sprite &sprite, int hframes, int vframes)
      : m_sprite(sprite), m_currentFrame(0), m_horizontalFrames(hframes),
        m_verticalFrames(vframes) {}

  ~SpriteActor() {}

  const int GetCurrentFrame() const { return m_currentFrame; }
  void SetCurrentFrame(int frame) { m_currentFrame = frame; }

  void SetHorizontalFrames(int hframes) { m_horizontalFrames = hframes; }
  void SetVerticalFrames(int vframes) { m_verticalFrames = vframes; }

  sf::Sprite& GetSprite() const { return m_sprite; }

  void UpdateSprite(float delta)
{
    sf::Vector2u size(sprite.getTexture()->GetSize());
	int frameWidth = size.x / m_horizontalFrames;
	int frameHeight = size.y / m_verticalFrames;

    currentFrame %= imgSheet.GetWidth() / frameWidth; // Makes the animation loop
    sheet.SetSubRect(IntRect(frameWidth * currentFrame,
                             frameHeight * animationID,
                             frameWidth * (currentFrame + 1),
                             frameHeight * animationID));
}

protected:
  sf::Sprite &m_sprite;
  int m_currentFrame;
  int m_horizontalFrames;
  int m_verticalFrames;
};

} // namespace d2

#endif _SPRITE_ACTOR_H_
