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

#ifndef BRIDGE_HAND_HPP
#define BRIDGE_HAND_HPP

#include "Holding.hpp"
#include "enum.hpp"

namespace Bridge {

class Hand
{
  private:
    Holding _data[4];

  public:
    constexpr Hand(Holding = {}, Holding = {}, Holding = {}, Holding = {});
    constexpr Holding operator[](Denomination) const;
    inline Holding& operator[](Denomination);
};

constexpr Hand::Hand(Holding spades, Holding hearts, Holding diamonds, Holding clubs):
    _data { spades, hearts, diamonds, clubs }
{}

constexpr Holding Hand::operator[](Denomination suit) const
{
    return _data[int(suit)];
}

Holding& Hand::operator[](Denomination suit)
{
    return _data[int(suit)];
}

} // namespace Bridge

#endif // BRIDGE_HAND_HPP
