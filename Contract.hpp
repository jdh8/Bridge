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

#ifndef BRIDGE_CONTRACT_HPP
#define BRIDGE_CONTRACT_HPP

#include "constants.hpp"
#include <string>
#include <sstream>

namespace Bridge {

class Contract
{
  private:
    typedef unsigned char Data;
    Data _level: 3;
    Data _denomination: 3;
    Data _doubled: 2;

  public:
    constexpr Contract(int, Denomination, Double = Double::_);

    constexpr int level() const { return _level; }
    constexpr Denomination denomination() const { return Denomination(_denomination); }
    constexpr Double doubled() const { return Double(_doubled); }

    template<typename T> operator std::basic_string<T>() const;
};

constexpr Contract::Contract(int level, Denomination denomination, Double doubled):
    _level(level),
    _denomination(Data(denomination)),
    _doubled(Data(doubled))
{}

template<typename T>
std::basic_ostream<T>& operator<<(std::basic_ostream<T>& s, Contract contract)
{
    return s << contract.level()
             << Symbol<T>::values[int(contract.denomination())]
             << std::basic_string<T>(int(contract.doubled()), 'x');
}

template<typename T>
Contract::operator std::basic_string<T>() const
{
    std::basic_ostringstream<T> s;
    s << *this;
    return s.str();
}

} // namespace Bridge

#endif // BRIDGE_CONTRACT_HPP
