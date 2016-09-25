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

#ifndef BRIDGE_BITSET_HPP
#define BRIDGE_BITSET_HPP

namespace Bridge {

template<typename Derived>
class Bitset
{
  friend bool operator!=(const Derived& x, const Derived& y) { return !(x == y); }

  friend Derived operator&(Derived x, const Derived& y) { return x &= y; }
  friend Derived operator^(Derived x, const Derived& y) { return x ^= y; }
  friend Derived operator|(Derived x, const Derived& y) { return x |= y; }
};

}

#endif
