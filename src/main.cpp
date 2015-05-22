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

#include <cstdlib>
#include <chrono>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/View.hpp>
#include "game/Universe.hpp"

int main() {
  // Seed the random number generator.
  /// std::srand(static_cast<unsigned int>(std::time(nullptr)));
  unsigned int width{800};
  unsigned int height{600};
  float scale{1.0f};
  sf::ContextSettings settings{32, 0, 4};
  sf::RenderWindow window{sf::VideoMode{width, height, 32}, "2.5DMayhem",
                          sf::Style::Default, settings};

  window.setVerticalSyncEnabled(true);
  window.setKeyRepeatEnabled(false);

  d2::Universe universe(width, height);

  using Clock = std::chrono::high_resolution_clock;
  auto lastTick = Clock::now();

  while (window.isOpen()) {
    sf::Event evt;
    if (window.pollEvent(evt)) {
      switch (evt.type) {
      case sf::Event::Closed:
        window.close();
        break;
      case sf::Event::Resized:
        // adjust the viewport when the window is resized
        glViewport(0, 0, evt.size.width, evt.size.height);
        break;
      // We handle some input events on our own, then pass along the rest of the
      // events to the individual game states.

      case sf::Event::MouseWheelMoved: {
        if (evt.mouseWheel.delta > 0) {
          scale -= 0.2f;
          if (scale < 0.2f)
            scale = 0.2f;
        } else {
          scale += 0.2f;
          if (scale > 1.0f)
            scale = 1.0f;
        }
        sf::View view(window.getDefaultView());
        view.zoom(scale);
        window.setView(view);
      } break;
      default:
        break;
      }

      // Let the universe also handle events.
      universe.handleInput(evt);
    }

    // We expect that 16.666ms went by since the last tick.  (60fps)
    auto now = Clock::now();
    std::chrono::duration<float, std::chrono::milliseconds::period> timePassed =
        std::chrono::duration_cast<std::chrono::microseconds>(now - lastTick);
    lastTick = now;

    // We calculate the adjust we must make to get a smooth 60fps tick.
    float adjustment = timePassed.count() * 60.f / 1000.f;
    universe.tick(adjustment);

    // Clear the viewport with black.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // window.clear(sf::Color(31, 31, 31, 255));

    window.draw(universe);
    window.display();
  }

  return 0;
}
