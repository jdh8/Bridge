// This file is part of Bridge, a library and utility for bridge.
//
// Copyright (C) 2022 Chen-Pang He <https://jdh8.org/>
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

#include <Bridge/DDS.hpp>
#include <dll.h>
#include <algorithm>

Bridge::Result::Result(const ::ddTableResults &table)
  : _strains {
    { table.resTable[3][0], table.resTable[3][1], table.resTable[3][2], table.resTable[3][3] },
    { table.resTable[2][0], table.resTable[2][1], table.resTable[2][2], table.resTable[2][3] },
    { table.resTable[1][0], table.resTable[1][1], table.resTable[1][2], table.resTable[1][3] },
    { table.resTable[0][0], table.resTable[0][1], table.resTable[0][2], table.resTable[0][3] },
    { table.resTable[4][0], table.resTable[4][1], table.resTable[4][2], table.resTable[4][3] },
  }
{}

static ::ddTableDeal convertToDDS(const Bridge::Deal &deal)
{
  using namespace Bridge;

  return {{
    {
      deal[Seat::N][Strain::S].bits(),
      deal[Seat::N][Strain::H].bits(),
      deal[Seat::N][Strain::D].bits(),
      deal[Seat::N][Strain::C].bits(),
    },
    {
      deal[Seat::E][Strain::S].bits(),
      deal[Seat::E][Strain::H].bits(),
      deal[Seat::E][Strain::D].bits(),
      deal[Seat::E][Strain::C].bits(),
    },
    {
      deal[Seat::S][Strain::S].bits(),
      deal[Seat::S][Strain::H].bits(),
      deal[Seat::S][Strain::D].bits(),
      deal[Seat::S][Strain::C].bits(),
    },
    {
      deal[Seat::W][Strain::S].bits(),
      deal[Seat::W][Strain::H].bits(),
      deal[Seat::W][Strain::D].bits(),
      deal[Seat::W][Strain::C].bits(),
    },
  }};
}

std::vector<Bridge::Result> Bridge::solve(std::span<const Bridge::Deal> deals, Bridge::StrainMask mask)
{
  const std::size_t strains = !mask.c + !mask.d + !mask.h + !mask.s + !mask.n;
  const std::size_t packSize = MAXNOOFTABLES * DDS_STRAINS / strains;
  const std::size_t q = deals.size() / packSize;
  const std::size_t r = deals.size() % packSize;

  int filters[5] = { mask.s, mask.h, mask.d, mask.c, mask.n };
  std::vector<Bridge::Result> results;
  results.reserve(deals.size());

  for (std::size_t i = 0; i < q; ++i) {
    ::ddTablesRes res = {};
    ::ddTableDeals pack = { packSize, {} };
    std::transform(deals.begin() + i * packSize, deals.begin() + (i + 1) * packSize, pack.deals, convertToDDS);
    ::CalcAllTables(&pack, -1, filters, &res, nullptr);
    std::copy(res.results, res.results + packSize, std::back_inserter(results));
  }

  if (r) {
    ::ddTablesRes res = {};
    ::ddTableDeals pack = { r, {} };
    std::transform(deals.begin() + q * packSize, deals.end(), pack.deals, convertToDDS);
    ::CalcAllTables(&pack, -1, filters, &res, nullptr);
    std::copy(res.results, res.results + r, std::back_inserter(results));
  }

  return results;
}
