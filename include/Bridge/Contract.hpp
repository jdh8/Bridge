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

#ifndef BRIDGE_CONTRACT_HPP
#define BRIDGE_CONTRACT_HPP

#include "enum.hpp"

namespace Bridge {

class Contract
{
  private:
    unsigned char _level: 3;
    unsigned char _denomination: 3;
    unsigned char _doubled: 2;

  public:
    constexpr Contract(int, Denomination, Double = Double::_);

    constexpr int level() const;
    constexpr Denomination denomination() const;
    constexpr Double doubled() const;
};

constexpr Contract::Contract(int level, Denomination denomination, Double doubled):
    _level(level),
    _denomination(int(denomination)),
    _doubled(int(doubled))
{}

constexpr int Contract::level() const
{
    return _level;
}

constexpr Denomination Contract::denomination() const
{
    return Denomination(_denomination);
}

constexpr Double Contract::doubled() const
{
    return Double(_doubled);
}

} // namespace Bridge

#endif // BRIDGE_CONTRACT_HPP
