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

#ifndef BRIDGE_DEAL_HPP
#define BRIDGE_DEAL_HPP

#include "Hand.hpp"

namespace Bridge {

class Deal
{
  private:
    Hand _data[4];

  public:
    constexpr Deal(Hand = {}, Hand = {}, Hand = {}, Hand = {});
    constexpr Hand operator[](Direction) const;
    inline Hand& operator[](Direction);

    void randomize();
};

constexpr Deal::Deal(Hand north, Hand east, Hand south, Hand west):
    _data { north, east, south, west }
{}

constexpr Hand Deal::operator[](Direction player) const
{
    return _data[int(player)];
}

Hand& Deal::operator[](Direction player)
{
    return _data[int(player)];
}

} // namespace Bridge

#endif // BRIDGE_DEAL_HPP