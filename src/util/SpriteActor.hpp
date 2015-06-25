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
#include <SFML/Graphics/Texture.hpp>

namespace d2 {

class SpriteActor {
public:
  SpriteActor(sf::Sprite &sprite)
      : m_sprite(sprite), m_currentFrame(0), m_horizontalFrames(1),
        m_verticalFrames(1), m_millisPerFrame(0) {
    UpdateSprite();
  }

  SpriteActor(sf::Sprite &sprite, int hframes, int vframes, int millisPF)
      : m_sprite(sprite), m_currentFrame(0), m_horizontalFrames(hframes),
        m_verticalFrames(vframes), m_millisPerFrame(millisPF) {
    UpdateSprite();
  }

  ~SpriteActor() {}

  const int GetCurrentFrame() const { return m_currentFrame; }
  void SetCurrentFrame(int frame) { m_currentFrame = frame; }

  void SetHorizontalFrames(int hframes) { m_horizontalFrames = hframes; }
  void SetVerticalFrames(int vframes) { m_verticalFrames = vframes; }

  int GetFrameWidth() const { return m_frameWidth; }
  int GetFrameHeight() const { return m_frameHeight; }

  void SetLocation(int x, int y) {
    m_xLocation = x;
    m_yLocation = y;
  }

  sf::Sprite &GetSprite() const { return m_sprite; }
  int GetX() const { return m_xLocation; }
  int GetY() const { return m_yLocation; }
  int GetSpeed() const  { return 1; }

  void UpdateSprite(float delta, int posX, int posY) {
    // Set the position of the actor - even for single frame entities.
    SetLocation(posX, posY);

    // Don't update the actor if it's a single frame.
    if (m_horizontalFrames == 1 && m_verticalFrames == 1)
      return;

    // the delta is in milliseconds;
    static float timePassedMillis{0.f};
    timePassedMillis += delta;

    if (timePassedMillis < static_cast<float>(m_millisPerFrame))
      return;

    timePassedMillis = 0.f;

    int totalFrames{m_horizontalFrames * m_verticalFrames};
    m_currentFrame = ++m_currentFrame % totalFrames;

    int frameX = (m_currentFrame % m_horizontalFrames) * m_frameWidth;
    int frameY = (m_currentFrame / m_horizontalFrames) * m_frameHeight;

    m_sprite.setTextureRect(
        sf::IntRect(frameX, frameY, m_frameWidth, m_frameHeight));
    m_sprite.setPosition(static_cast<float>(m_xLocation),
                         static_cast<float>(m_yLocation));
  }

protected:
  void UpdateSprite() {
    m_currentFrame = 0;
    m_xLocation = 0;
    m_yLocation = 0;

    sf::Vector2u size(m_sprite.getTexture()->getSize());
    if (m_horizontalFrames == 1 && m_verticalFrames == 1) {
      m_frameWidth = size.x;
      m_frameHeight = size.y;
      return;
    }
    m_frameWidth = size.x / m_horizontalFrames;
    m_frameHeight = size.y / m_verticalFrames;
  }

  sf::Sprite &m_sprite;
  int m_currentFrame;
  int m_horizontalFrames;
  int m_verticalFrames;
  int m_millisPerFrame;
  int m_frameWidth;
  int m_frameHeight;
  int m_xLocation;
  int m_yLocation;
};

} // namespace d2

#endif _SPRITE_ACTOR_H_
