// This file is part of Bridge, a library and utility for bridge.
//
// Copyright (C) 2016 Chen-Pang He <https://jdh8.org/>
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
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

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
    Row(int, int, int, int);

    template<typename T>
    Row(const T*);

    int operator[](Direction) const;

    class reference
    {
        friend class Row;

        Row& _parent;
        Direction _direction;

        reference(Row&, Direction);

      public:
        operator int() const;
        reference& operator=(int);
        reference& operator=(const reference&);
    };

    reference operator[](Direction position);
};

inline
Row::Row(int north, int east, int south, int west):
    _data(north | east << 4 | south << 8 | west << 12)
{}

template<typename T>
Row::Row(const T* array):
    Row(array[0], array[1], array[2], array[3])
{}

inline
int Row::operator[](Direction direction) const
{
    return _data >> (int(direction) << 2) & 0xF;
}

inline
Row::reference::reference(Row& parent, Direction direction):
    _parent(parent),
    _direction(direction)
{}

inline
Row::reference::operator int() const
{
    return static_cast<const Row&>(_parent)[_direction];
}

inline
Row::reference& Row::reference::operator=(int value)
{
    int shift = int(_direction) << 2;
    _parent._data ^= (_parent._data ^ value << shift) & (0xF << shift);
    return *this;
}

inline
Row::reference& Row::reference::operator=(const reference& ref)
{
    return *this = int(ref);
}

class Table
{
  private:
    Row _data[5];

  public:
    Table(Row, Row, Row, Row, Row);
    Table(const ::ddTableResults&);

    Row operator[](Denomination) const;
    Row& operator[](Denomination);
};

inline
Table::Table(Row clubs, Row diamonds, Row hearts, Row spades, Row notrump):
    _data { clubs, diamonds, hearts, spades, notrump }
{}

inline
Row Table::operator[](Denomination denomination) const
{
    return _data[int(denomination)];
}

inline
Row& Table::operator[](Denomination denomination)
{
    return _data[int(denomination)];
}

} // namespace Result
} // namespace Bridge

#endif // BRIDGE_RESULT_HPP
