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

#ifndef _TRANSFORM_HPP_
#define _TRANSFORM_HPP_

#include "interfaces/Interfaces.h"
#include "util/Transform.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

namespace util {

class Transform {
public:
  Transform()
      : m_x(0), m_y(0), m_z(0), m_dx(0), m_dy(0), m_dz(0), m_dxMin(0),
        m_dxMax(0), m_dyMin(0), m_dyMax(0), m_dzMin(0), m_dzMax(0) {}

  ~Transform() {}

  int GetX() const { return m_x; }
  int GetY() const { return m_y; }
  int GetZ() const { return m_z; }
  void SetX(int x) { m_x = x; }
  void SetY(int y) { m_y = y; }
  void SetZ(int z) { m_z = z; }

  int GetDX() const { return m_dx; }
  int GetDY() const { return m_dy; }
  int GetDZ() const { return m_dz; }
  void SetDX(int dx) {
    m_dx = dx;
    if (m_dx < m_dxMin)
      m_dx = m_dxMin;
    if (m_dx > m_dxMax)
      m_dx = m_dxMax;
  }
  void SetDXLimits(int min, int max) {
    m_dxMin = min;
    m_dxMax = max;
  }
  void SetDY(int dy) {
    m_dy = dy;
    if (m_dy < m_dyMin)
      m_dy = m_dyMin;
    if (m_dy > m_dyMax)
      m_dy = m_dyMax;
  }
  void SetDYLimits(int min, int max) {
    m_dyMin = min;
    m_dyMax = max;
  }
  void SetDZ(int dz) {
    m_dz = dz;
    if (m_dz < m_dzMin)
      m_dz = m_dzMin;
    if (m_dz > m_dzMax)
      m_dz = m_dzMax;
  }
  void SetDZLimits(int min, int max) {
    m_dzMin = min;
    m_dzMax = max;
  }

  void Update() {
    m_x += m_dx;
    m_y += m_dy;
    m_z += m_dz;
  }

  int GetPositionOffsetX(int x, int speed) { return (x + (m_dx * speed)); }

  int GetPositionOffsetY(int y, int speed) { return (y + (m_dy * speed)); }

  int GetPositionOffsetZ(int z, int speed) { return (z + (m_dz * speed)); }

protected:
  // The transform class will take care of moving a hypothetical point (the
  // origin) around in an infinite universe. This will include having attributes
  // like speed and position.
  int m_x;
  int m_y;
  int m_z;
  int m_dx;
  int m_dy;
  int m_dz;
  int m_dxMin;
  int m_dxMax;
  int m_dyMin;
  int m_dyMax;
  int m_dzMin;
  int m_dzMax;
};

} // namespace d2

#endif // _TRANSFORM_HPP_