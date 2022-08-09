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

#include <Bridge/Deal.hpp>
#include <llvm/Support/raw_ostream.h>
#include <algorithm>
#include <random>

Bridge::Deal Bridge::getRandomDeal()
{
  static std::mt19937 generator(std::random_device{}());

  Card deck[] = {
    { Strain::S,  2 }, { Strain::H,  2 }, { Strain::D,  2 }, { Strain::C,  2 },
    { Strain::S,  3 }, { Strain::H,  3 }, { Strain::D,  3 }, { Strain::C,  3 },
    { Strain::S,  4 }, { Strain::H,  4 }, { Strain::D,  4 }, { Strain::C,  4 },
    { Strain::S,  5 }, { Strain::H,  5 }, { Strain::D,  5 }, { Strain::C,  5 },
    { Strain::S,  6 }, { Strain::H,  6 }, { Strain::D,  6 }, { Strain::C,  6 },
    { Strain::S,  7 }, { Strain::H,  7 }, { Strain::D,  7 }, { Strain::C,  7 },
    { Strain::S,  8 }, { Strain::H,  8 }, { Strain::D,  8 }, { Strain::C,  8 },
    { Strain::S,  9 }, { Strain::H,  9 }, { Strain::D,  9 }, { Strain::C,  9 },
    { Strain::S, 10 }, { Strain::H, 10 }, { Strain::D, 10 }, { Strain::C, 10 },
    { Strain::S, 11 }, { Strain::H, 11 }, { Strain::D, 11 }, { Strain::C, 11 },
    { Strain::S, 12 }, { Strain::H, 12 }, { Strain::D, 12 }, { Strain::C, 12 },
    { Strain::S, 13 }, { Strain::H, 13 }, { Strain::D, 13 }, { Strain::C, 13 },
    { Strain::S, 14 }, { Strain::H, 14 }, { Strain::D, 14 }, { Strain::C, 14 },
  };

  std::shuffle(std::begin(deck), std::end(deck), generator);
  Deal deal = {};

  for (int seat = 0; seat < 4; ++seat)
    for (int i = 0; i < 13; ++i)
      deal[Seat(seat)].set(deck[13 * seat + i]);

  return deal;
}

llvm::raw_ostream &Bridge::operator<<(llvm::raw_ostream &stream, const Bridge::Holding &holding)
{
  const char table[] = "23456789TJQKA";

  for (int rank = 14; rank > 1; --rank)
    if (holding.test(rank))
      stream << table[rank - 2];

  return stream;
}

llvm::raw_ostream &Bridge::operator<<(llvm::raw_ostream &stream, const Bridge::Hand &hand)
{
  return stream
    << hand[Strain::S] << '.'
    << hand[Strain::H] << '.'
    << hand[Strain::D] << '.'
    << hand[Strain::C];
}

llvm::raw_ostream &Bridge::operator<<(llvm::raw_ostream &stream, const Bridge::Deal &deal)
{
  return stream << "N:"
    << deal[Seat::N] << ' '
    << deal[Seat::E] << ' '
    << deal[Seat::S] << ' '
    << deal[Seat::W];
}
