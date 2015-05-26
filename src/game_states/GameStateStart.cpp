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
  m_bgScroller.AddLayer("res\\level1\\layer-1-sky.png");
  m_bgScroller.AddLayer("res\\level1\\layer-2-mountain.png");
  m_bgScroller.AddLayer("res\\level1\\layer-3-forest.png");
  m_bgScroller.AddMapOverlay("res\\level1\\mapdata.png",
                             "res\\level1\\tile.png");
  m_bgScroller.AddActor("res\\level1\\chiraku.png", 4, 1, 25);
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
#if 0
sf::Sprite& topMost{m_bgScroller.GetLayer(2)};
int universeW = m_manager->GetUniverse()->GetW();
int universeH =  m_manager->GetUniverse()->GetH();
static int posx = 0;
static int posy = 0;
static int w = 64;
static int h = 64;
static int speedx = 0;
static int speedy = 2;
// "walk" down the sprite in the current space where the "player" is, and check if something was hit.

{
	// First find the "column" of pixels at the sprites projected x position.
	int projectedX = posx + speedx;
	const sf::Texture* texture{topMost.getTexture()};
	sf::Vector2u size{texture->getSize()};

	// If the player is clearly out of bounds, then we don't update it.
	if ((posx + w + speedx) > universeW)
		return;
	if ((posy + h + speedy) > universeH)
		return;
	if ((posx + w + speedx) < 0)
		return;
	if ((posy + h + speedy) < 0)
		return;

	// Calculate where the center of the player will be (horiz)
	int centerx = posx + (w >> 1) + speedx;
	// Next, get the first non-opaque pixel on the top layer.
	for (int i = 0; i < size.y; ++i) {
		texture->
	}
}
#endif // 0
}

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
