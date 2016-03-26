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

#ifndef BRIDGE_HOLDING_HPP
#define BRIDGE_HOLDING_HPP

#include "Mask.hpp"
#include <cstddef>
#include <cstdint>
#include <utility>

namespace Bridge {

using std::rel_ops::operator!=;

class Holding : public Mask<Holding>
{
  private:
    std::uint16_t _data;

  public:
    class reference;

    enum { Jack = 11, Queen, King, Ace };

    constexpr Holding();
    explicit constexpr Holding(std::uint16_t);

    constexpr bool all() const;
    constexpr bool any() const;
    constexpr bool verify() const;
    constexpr bool test(std::size_t) const;
    constexpr bool operator[](std::size_t) const;
    constexpr bool operator==(Holding) const;

    constexpr Holding operator~() const;
    constexpr Holding operator&(Holding) const;
    constexpr Holding operator^(Holding) const;
    constexpr Holding operator|(Holding) const;

    constexpr std::size_t count() const;
    constexpr std::size_t size() const;

    constexpr std::uint16_t cast() const;

    inline Holding& normalize();

    inline Holding& flip(std::size_t);
    inline Holding& reset(std::size_t);

    inline Holding& set();
    inline Holding& set(std::size_t, bool = true);

    inline reference operator[](std::size_t position);
};

class Holding::reference
{
    friend reference Holding::operator[](std::size_t position);

  private:
    Holding& _parent;
    std::size_t _position;

    constexpr reference(Holding&, std::size_t);

  public:
    constexpr operator bool() const;
    constexpr bool operator~() const;

    inline reference& operator=(bool);
    inline reference& operator=(const reference&);

    inline reference& flip();
};

constexpr Holding::Holding():
    _data()
{}

constexpr Holding::Holding(std::uint16_t value):
    _data(value)
{}

constexpr bool Holding::all() const
{
    return (_data & 0x7FFC) == 0x7FFC;
}

constexpr bool Holding::any() const
{
    return _data;
}

constexpr bool Holding::verify() const
{
    return (_data & 0x7FFC) == _data;
}

constexpr bool Holding::test(std::size_t position) const
{
    return _data & (1 << position);
}

constexpr bool Holding::operator[](std::size_t position) const
{
    return test(position);
}

constexpr bool Holding::operator==(Holding other) const
{
    return _data == other._data;
}

constexpr Holding Holding::operator~() const
{
    return Holding(~_data);
}

constexpr Holding Holding::operator&(Holding other) const
{
    return Holding(_data & other._data);
}

constexpr Holding Holding::operator^(Holding other) const
{
    return Holding(_data ^ other._data);
}

constexpr Holding Holding::operator|(Holding other) const
{
    return Holding(_data | other._data);
}

constexpr std::size_t Holding::count() const
{
#ifdef __POPCNT__
    return __builtin_popcount(_data);
#else
    return (_data * UINT64_C(0x200040008001) & UINT64_C(0x111111111111111)) % 0xF;
#endif
}

constexpr std::size_t Holding::size() const
{
    return 15;
}

constexpr std::uint16_t Holding::cast() const
{
    return _data;
}

Holding& Holding::normalize()
{
    _data &= 0x7FFC;
    return *this;
}

Holding& Holding::flip(std::size_t position)
{
    _data ^= 1 << position;
    return *this;
}

Holding& Holding::reset(std::size_t position)
{
    _data &= ~(1 << position);
    return *this;
}

Holding& Holding::set()
{
    _data = -1;
    return *this;
}

Holding& Holding::set(std::size_t position, bool value)
{
    if (value)
        _data |= 1 << position;
    else
        _data &= ~(1 << position);

    return *this;
}

constexpr Holding::reference::reference(Holding& parent, std::size_t position):
    _parent(parent),
    _position(position)
{}

constexpr Holding::reference::operator bool() const
{
    return _parent.test(_position);
}

constexpr bool Holding::reference::operator~() const
{
    return !_parent.test(_position);
}

Holding::reference& Holding::reference::operator=(bool value)
{
    _parent.set(_position, value);
    return *this;
}

Holding::reference& Holding::reference::operator=(const reference& ref)
{
    return *this = bool(ref);
}

Holding::reference& Holding::reference::flip()
{
    _parent.flip(_position);
    return *this;
}

Holding::reference Holding::operator[](std::size_t position)
{
    return { *this, position };
}

} // namespace Bridge

#endif // BRIDGE_HOLDING_HPP
