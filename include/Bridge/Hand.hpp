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

namespace Bridge {

class Hand
{
  private:
    union
    {
        std::uint64_t _raw;
        Holding _data[4];
    };

    static constexpr std::uint64_t _first(std::uint64_t v);
    static constexpr std::uint64_t _second(std::uint64_t v);
    static constexpr std::uint64_t _last(std::uint64_t v);

  public:
    explicit constexpr Hand(std::uint64_t);
    constexpr Hand(Holding = {}, Holding = {}, Holding = {}, Holding = {});

    constexpr bool all() const;
    constexpr bool any() const;
    constexpr bool none() const;
    constexpr bool verify() const;

    constexpr std::size_t count() const;

    constexpr Hand operator&(Hand) const;
    constexpr Hand operator^(Hand) const;
    constexpr Hand operator|(Hand) const;

    constexpr Holding operator[](Denomination) const;
    inline Holding& operator[](Denomination);

    inline Hand& normalize();
    inline Hand& flip();
    inline Hand& set();
    inline Hand& reset();
};

constexpr std::uint64_t Hand::_first(std::uint64_t v)
{
    return v - ((v >> 1) & UINT64_C(0x5555555555555555));
}

constexpr std::uint64_t Hand::_second(std::uint64_t v)
{
    return (v & UINT64_C(0x3333333333333333)) + ((v >> 2) & UINT64_C(0x3333333333333333));
}

constexpr std::uint64_t Hand::_last(std::uint64_t v)
{
    return UINT64_C(0x0101010101010101) * ((v + (v >> 4)) & UINT64_C(0x0F0F0F0F0F0F0F0F));
}

constexpr Hand::Hand(std::uint64_t raw):
    _raw(raw)
{}

constexpr Hand::Hand(Holding spades, Holding hearts, Holding diamonds, Holding clubs):
    _data { clubs, diamonds, hearts, spades }
{}

constexpr bool Hand::all() const
{
    return (_raw & UINT64_C(0x7FFC7FFC7FFC7FFC)) == UINT64_C(0x7FFC7FFC7FFC7FFC);
}

constexpr bool Hand::any() const
{
    return _raw;
}

constexpr bool Hand::none() const
{
    return !_raw;
}

constexpr bool Hand::verify() const
{
    return count() < 14 && (_raw & UINT64_C(0x7FFC7FFC7FFC7FFC)) == _raw;
}

constexpr std::size_t Hand::count() const
{
#ifdef __POPCNT__
    return __builtin_popcountll(_raw);
#else
    return _last(_second(_first(_raw))) >> 56;
#endif
}

constexpr Hand Hand::operator&(Hand other) const
{
    return Hand(_raw & other._raw);
}

constexpr Hand Hand::operator^(Hand other) const
{
    return Hand(_raw ^ other._raw);
}

constexpr Hand Hand::operator|(Hand other) const
{
    return Hand(_raw | other._raw);
}

constexpr Holding Hand::operator[](Denomination suit) const
{
    return _data[int(suit)];
}

Holding& Hand::operator[](Denomination suit)
{
    return _data[int(suit)];
}

Hand& Hand::normalize()
{
    _raw &= UINT64_C(0x7FFC7FFC7FFC7FFC);
    return *this;
}

Hand& Hand::flip()
{
    _raw = ~_raw;
    return *this;
}

Hand& Hand::set()
{
    _raw = -1;
    return *this;
}

Hand& Hand::reset()
{
    _raw = 0;
    return *this;
}

} // namespace Bridge

#endif // BRIDGE_HAND_HPP
