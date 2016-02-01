// This file is part of Bridge, a library and utility for bridge.
//
// Copyright (C) 2016 Chen-Pang He <http://jdh8.org/>
//
// Bridge is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Bridge is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef BRIDGE_RESULT_HPP
#define BRIDGE_RESULT_HPP

#include "enum.hpp"
#include <cstdint>

struct ddTableResults;

namespace Bridge {
namespace Result {

class Row
{
  private:
    std::uint16_t _data;

  public:
    constexpr Row(int, int, int, int);
    constexpr int operator[](Direction) const;

    class reference
    {
        friend class Row;

        Row& _parent;
        Direction _direction;

        constexpr reference(Row&, Direction);

      public:
        constexpr operator int() const;
        inline reference& operator=(int);
        inline reference& operator=(const reference&);
    };

    inline reference operator[](Direction position);
};

constexpr Row::Row(int north, int east, int south, int west):
    _data(north | east << 4 | south << 8 | west << 12)
{}

constexpr int Row::operator[](Direction direction) const
{
    return _data >> (int(direction) << 2) & 0xF;
}

constexpr Row::reference::reference(Row& parent, Direction direction):
    _parent(parent),
    _direction(direction)
{}

constexpr Row::reference::operator int() const
{
    return static_cast<const Row&>(_parent)[_direction];
}

Row::reference& Row::reference::operator=(int value)
{
    int shift = int(_direction) << 2;
    _parent._data ^= (_parent._data ^ value << shift) & (0xF << shift);
    return *this;
}

Row::reference& Row::reference::operator=(const reference& ref)
{
    return *this = int(ref);
}

class Table
{
    Row _data[5];
};

} // namespace Result
} // namespace Bridge

#endif // BRIDGE_RESULT_HPP
