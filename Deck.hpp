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

#ifndef BRIDGE_DECK_HPP
#define BRIDGE_DECK_HPP

#include "constants.hpp"
#include <algorithm>
#include <random>

#define BRIDGE_EXPAND_SUIT(suit) \
    { suit, 2 }, { suit, 3 }, { suit, 4 }, { suit, 5 }, \
    { suit, 6 }, { suit, 7 }, { suit, 8 }, { suit, 9 }, \
    { suit, 10 }, { suit, 11 }, { suit, 12 }, { suit, 13 }, { suit, 14 }

namespace Bridge {

struct Deck
{
    class Card
    {
      private:
        unsigned char _suit: 2;
        unsigned char _rank: 4;

      public:
        constexpr Card(Denomination, int);
        constexpr Denomination suit() const;
        constexpr int rank() const;
    };

    Card cards[52] = {
        BRIDGE_EXPAND_SUIT(Denomination::Spades),
        BRIDGE_EXPAND_SUIT(Denomination::Hearts),
        BRIDGE_EXPAND_SUIT(Denomination::Diamonds),
        BRIDGE_EXPAND_SUIT(Denomination::Clubs)
    };

    inline void shuffle(std::size_t = 52);
};

constexpr Deck::Card::Card(Denomination suit, int rank):
    _suit(int(suit)),
    _rank(rank)
{}

constexpr Denomination Deck::Card::suit() const
{
    return Denomination(_suit);
}

constexpr int Deck::Card::rank() const
{
    return _rank;
}

inline void Deck::shuffle(std::size_t length)
{
    static std::mt19937 generator((std::random_device())());

    std::shuffle(cards, cards + length, generator);
}

} // namespace Bridge

#endif // BRIDGE_DECK_HPP
