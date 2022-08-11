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

#ifndef BRIDGE_DEAL_HPP
#define BRIDGE_DEAL_HPP

#include <array>
#include <iosfwd>
#include <cstdint>

namespace Bridge {

enum class Strain { C, D, H, S, N };
enum class Seat { N, E, S, W };

namespace Rank {
enum { J = 11, Q, K, A };
} // namespace Rank

class Card
{
  unsigned char _suit : 2;
  unsigned char _rank : 4;

public:
  constexpr Card(Strain suit, int rank)
    : _suit(static_cast<int>(suit)), _rank(rank)
  {}

  constexpr Strain suit() const { return static_cast<Strain>(_suit); }
  constexpr int rank() const { return _rank; }
};

class Holding
{
  std::uint16_t _data = 0;

public:
  std::uint16_t bits() const { return _data; }
  unsigned size() const { return __builtin_popcount(bits()); }
  bool empty() const { return !bits(); }
  bool test(int rank) const { return bits() & 1u << rank; }

  void set(int rank) { _data |= 1u << rank; }
};

class Hand
{
  Holding _data[4] = {};

public:
  Holding operator[](Strain suit) const { return _data[static_cast<int>(suit)]; }
  Holding & operator[](Strain suit) { return _data[static_cast<int>(suit)]; }

  bool empty() const
  {
    return _data[0].empty()
        && _data[1].empty()
        && _data[2].empty()
        && _data[3].empty();
  }

  unsigned size() const
  {
    return __builtin_popcountll(
        static_cast<unsigned long long>(_data[0].bits())       |
        static_cast<unsigned long long>(_data[1].bits()) << 16 |
        static_cast<unsigned long long>(_data[2].bits()) << 32 |
        static_cast<unsigned long long>(_data[3].bits()) << 48);
  }

  bool test(Card card) const { return (*this)[card.suit()].test(card.rank()); }
  void set(Card card) { (*this)[card.suit()].set(card.rank()); }
};

struct Deal : private std::array<Hand, 4>
{
  using std::array<Hand, 4>::array;
  const Hand & operator[](Seat seat) const { return data()[static_cast<int>(seat)]; }
  Hand & operator[](Seat seat) { return data()[static_cast<int>(seat)]; }
};

Deal getRandomDeal();
void fillRandomCards(Deal &);

template <typename Ch>
std::basic_ostream<Ch> & operator<<(std::basic_ostream<Ch> &stream, const Holding &holding)
{
  const Ch table[] = { '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A' };

  for (int rank = 14; rank > 1; --rank)
    if (holding.test(rank))
      stream << table[rank - 2];

  return stream;
}

template <typename Ch>
std::basic_ostream<Ch> & operator<<(std::basic_ostream<Ch> &stream, const Hand &hand)
{
  return stream
    << hand[Strain::S] << '.'
    << hand[Strain::H] << '.'
    << hand[Strain::D] << '.'
    << hand[Strain::C];
}

template <typename Ch>
std::basic_ostream<Ch> & operator<<(std::basic_ostream<Ch> &stream, const Deal &deal)
{
  return stream << "N:"
    << deal[Seat::N] << ' '
    << deal[Seat::E] << ' '
    << deal[Seat::S] << ' '
    << deal[Seat::W];
}

} // namespace Bridge

#endif
