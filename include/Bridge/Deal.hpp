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

#ifndef BRIDGE_DEAL_HPP
#define BRIDGE_DEAL_HPP

#include "Hand.hpp"

struct ddTableDeal;

namespace Bridge {

namespace Result { class Table; }

class Deal
{
  private:
    Hand _data[4];

  public:
    class Random {};

    Deal(Hand = {}, Hand = {}, Hand = {}, Hand = {});
    Deal(Random);

    Hand operator[](Direction) const;
    Hand& operator[](Direction);
    Deal& operator=(Random);

    operator ::ddTableDeal() const;

    bool verify() const;
    Result::Table solve() const;
};

inline
Deal::Deal(Hand north, Hand east, Hand south, Hand west):
    _data { north, east, south, west }
{}

inline
Deal::Deal(Random random)
{
    *this = random;
}

inline
Hand Deal::operator[](Direction player) const
{
    return _data[int(player)];
}

inline
Hand& Deal::operator[](Direction player)
{
    return _data[int(player)];
}

inline
bool Deal::verify() const
{
    return
        _data[0].verify() && _data[1].verify() &&
        _data[2].verify() && _data[3].verify() &&
        _data[0].count() == _data[1].count() &&
        _data[1].count() == _data[2].count() &&
        _data[2].count() == _data[3].count() &&
        !((_data[0] & _data[1]).any() || (_data[0] & _data[2]).any() ||
          (_data[0] & _data[3]).any() || (_data[1] & _data[2]).any() ||
          (_data[1] & _data[3]).any() || (_data[2] & _data[3]).any());
}

} // namespace Bridge

#endif // BRIDGE_DEAL_HPP
