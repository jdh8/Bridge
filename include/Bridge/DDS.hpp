// This file is part of Bridge, a library and utility for bridge.
//
// Copyright (C) 2016, 2022 Chen-Pang He <https://jdh8.org/>
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

#ifndef BRIDGE_DDS_HPP
#define BRIDGE_DDS_HPP

#include "Deal.hpp"
#include <span>
#include <vector>

struct ddTableResults;

namespace Bridge {

// Mask strains you don't want to solve
struct StrainMask
{
  unsigned char c : 1;
  unsigned char d : 1;
  unsigned char h : 1;
  unsigned char s : 1;
  unsigned char n : 1;
};

class Result
{
  struct PerStrain
  {
    std::uint16_t n : 4;
    std::uint16_t e : 4;
    std::uint16_t s : 4;
    std::uint16_t w : 4;
  };

  PerStrain _strains[5];

public:
  Result(const ::ddTableResults &);

  constexpr int operator()(Strain strain, Seat seat) const
  {
    const PerStrain result = _strains[static_cast<int>(strain)];

    switch (seat) {
      case Seat::N: return result.n;
      case Seat::E: return result.e;
      case Seat::S: return result.s;
      case Seat::W: return result.w;
    }
    return 0;
  }
};

std::vector<Result> solve(std::span<const Deal> deals, StrainMask mask = {});

} // namespace Bridge

#endif
