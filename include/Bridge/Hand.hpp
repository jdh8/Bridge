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

#ifndef BRIDGE_HAND_HPP
#define BRIDGE_HAND_HPP

#include "Holding.hpp"
#include "enum.hpp"
#include <cstring>

namespace Bridge {

class Hand : public Mask<Hand>
{
  private:
    Holding _data[4];

  public:
    explicit Hand(std::uint64_t);
    Hand(Holding = {}, Holding = {}, Holding = {}, Holding = {});

    explicit operator std::uint64_t() const;

    bool all() const;
    bool any() const;
    bool verify() const;

    std::size_t count() const;

    bool operator==(Hand) const;

    Hand operator~() const;
    Hand operator&(Hand) const;
    Hand operator^(Hand) const;
    Hand operator|(Hand) const;

    Holding operator[](Denomination) const;
    Holding& operator[](Denomination);

    Hand& normalize();
    Hand& set();

    template<typename Result, typename F>
    Result evaluate(const F&) const;

    template<typename F>
    auto evaluate(const F& f) const -> decltype(f(Holding()));
};

inline
Hand::Hand(std::uint64_t raw)
{
    std::memcpy(_data, &raw, sizeof(std::uint64_t));
}

inline
Hand::Hand(Holding spades, Holding hearts, Holding diamonds, Holding clubs):
    _data { clubs, diamonds, hearts, spades }
{}

inline
Hand::operator std::uint64_t() const
{
    std::uint64_t result;

    std::memcpy(&result, _data, sizeof(std::uint64_t));

    return result;
}

inline
bool Hand::all() const
{
    std::uint64_t raw(*this);

    return (raw & UINT64_C(0x7FFC7FFC7FFC7FFC)) == UINT64_C(0x7FFC7FFC7FFC7FFC);
}

inline
bool Hand::any() const
{
    std::uint64_t raw(*this);

    return raw;
}

inline
bool Hand::verify() const
{
    std::uint64_t raw(*this);

    return count() < 14 && (raw & UINT64_C(0x7FFC7FFC7FFC7FFC)) == raw;
}

inline
std::size_t Hand::count() const
{
    std::uint64_t v(*this);

#ifdef __POPCNT__
    return __builtin_popcountll(v);
#else
    v = v - ((v >> 1) & UINT64_C(0x5555555555555555));
    v = (v & UINT64_C(0x3333333333333333)) + ((v >> 2) & UINT64_C(0x3333333333333333));
    v = UINT64_C(0x0101010101010101) * ((v + (v >> 4)) & UINT64_C(0x0F0F0F0F0F0F0F0F));

    return v >> 56;
#endif
}

inline
bool Hand::operator==(Hand other) const
{
    std::uint64_t x(*this);
    std::uint64_t y(other);

    return x == y;
}

inline
Hand Hand::operator~() const
{
    std::uint64_t raw(*this);

    return Hand(~raw);
}

inline
Hand Hand::operator&(Hand other) const
{
    std::uint64_t x(*this);
    std::uint64_t y(other);

    return Hand(x & y);
}

inline
Hand Hand::operator^(Hand other) const
{
    std::uint64_t x(*this);
    std::uint64_t y(other);

    return Hand(x ^ y);
}

inline
Hand Hand::operator|(Hand other) const
{
    std::uint64_t x(*this);
    std::uint64_t y(other);

    return Hand(x | y);
}

inline
Holding Hand::operator[](Denomination suit) const
{
    return _data[int(suit)];
}

inline
Holding& Hand::operator[](Denomination suit)
{
    return _data[int(suit)];
}

inline
Hand& Hand::normalize()
{
    std::uint64_t raw(*this);

    return *this = Hand(raw & UINT64_C(0x7FFC7FFC7FFC7FFC));
}

inline
Hand& Hand::set()
{
    return *this = Hand(-1);
}

template<typename Result, typename F>
Result Hand::evaluate(const F& f) const
{
    return f(_data[0]) + f(_data[1]) + f(_data[2]) + f(_data[3]);
}

template<typename F>
auto Hand::evaluate(const F& f) const -> decltype(f(Holding()))
{
    return evaluate<decltype(f(Holding()))>(f);
}

} // namespace Bridge

#endif // BRIDGE_HAND_HPP
