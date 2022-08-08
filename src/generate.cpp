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

#include <Bridge/Deal.hpp>
#include <dll.h>
#include <llvm/Support/CommandLine.h>

static ::ddTableDeal toDDS(const Bridge::Deal &deal)
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

static ::ddTableDeals getRandomDealPack(int count)
{
  ::ddTableDeals pack = { count, {} };

  for (int i = 0; i < count; ++i)
    pack.deals[i] = toDDS(Bridge::getRandomDeal());

  return pack;
}

static void solve(llvm::ArrayRef<Bridge::Deal> deals)
{
  const std::size_t strains = 5;
  const std::size_t packSize = MAXNOOFTABLES * 5 / strains;
  const std::size_t q = deals.size() / packSize;
  const std::size_t r = deals.size() % packSize;
  int filters[5] = {};

  for (std::size_t i = 0; i < q; ++i) {
    ::ddTableDeals pack = { packSize, {} };
    llvm::transform(deals.slice(i * packSize, packSize), pack.deals, toDDS);
    ::ddTablesRes results;
    ::CalcAllTables(&pack, -1, filters, &results, nullptr);
  }

  if (r) {
    ::ddTableDeals pack = { r, {} };
    llvm::transform(deals.slice(q * packSize, packSize), pack.deals, toDDS);
    ::ddTablesRes results;
    ::CalcAllTables(&pack, -1, filters, &results, nullptr);
  }
}

static int procedure(std::size_t number)
{
  llvm::SmallVector<Bridge::Deal, 0> deals;
  deals.reserve(number);

  for (std::size_t i = 0; i < number; ++i) {
    deals.push_back(Bridge::getRandomDeal());
    llvm::outs() << deals.back() << '\n';
  }

  solve(deals);
  return 0;
}

int main(int argc, char **argv)
{
  using namespace llvm;
  cl::opt<std::size_t> number(cl::Positional, cl::desc("<number of deals>"), cl::init(10));

  if (!cl::ParseCommandLineOptions(argc, argv, "Description?"))
    return 1;

  return procedure(number);
}
