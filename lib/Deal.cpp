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
#include <boost/container/small_vector.hpp>
#include <algorithm>
#include <random>

static std::mt19937 generator(std::random_device{}());

Bridge::Deal Bridge::getRandomDeal()
{
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

static auto combine(const Bridge::Deal &deal, Bridge::Strain strain)
{
  return deal[Bridge::Seat::N][strain].bits()
       | deal[Bridge::Seat::E][strain].bits()
       | deal[Bridge::Seat::W][strain].bits()
       | deal[Bridge::Seat::S][strain].bits();
}

void Bridge::fillRandomCards(Bridge::Deal &deal)
{
  const auto c = combine(deal, Strain::C);
  const auto d = combine(deal, Strain::D);
  const auto h = combine(deal, Strain::H);
  const auto s = combine(deal, Strain::S);

  boost::container::small_vector<Card, 52> deck;

  for (int rank = 2; rank <= 14; ++ rank) {
    if (!(1u << rank & c))
      deck.emplace_back(Strain::C, rank);
    if (!(1u << rank & d))
      deck.emplace_back(Strain::D, rank);
    if (!(1u << rank & h))
      deck.emplace_back(Strain::H, rank);
    if (!(1u << rank & s))
      deck.emplace_back(Strain::S, rank);
  }

  std::shuffle(deck.begin(), deck.end(), generator);
  auto take = deck.cbegin();

  for (auto slots = 13 - deal[Bridge::Seat::N].size(); slots--;)
    deal[Bridge::Seat::N].set(*take++);

  for (auto slots = 13 - deal[Bridge::Seat::E].size(); slots--;)
    deal[Bridge::Seat::E].set(*take++);

  for (auto slots = 13 - deal[Bridge::Seat::S].size(); slots--;)
    deal[Bridge::Seat::S].set(*take++);

  for (auto slots = 13 - deal[Bridge::Seat::W].size(); slots--;)
    deal[Bridge::Seat::W].set(*take++);
}
