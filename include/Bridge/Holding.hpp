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

#include <cstddef>
#include <cstdint>

namespace Bridge {

struct Holding
{
    enum { Jack = 11, Queen, King, Ace };

    std::uint16_t data;

    constexpr bool all() const;
    constexpr bool any() const;
    constexpr bool none() const;
    constexpr bool verify() const;
    constexpr bool test(std::size_t) const;
    constexpr bool operator[](std::size_t) const;

    constexpr std::size_t count() const;
    constexpr std::size_t size() const;

    inline Holding& normalize();

    inline Holding& flip();
    inline Holding& flip(std::size_t);

    inline Holding& set();
    inline Holding& set(std::size_t, bool = true);

    inline Holding& reset();
    inline Holding& reset(std::size_t);

    class reference
    {
        friend struct Holding;

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

    inline reference operator[](std::size_t position);
};

constexpr bool Holding::all() const
{
    return (data & 0x7FFC) == 0x7FFC;
}

constexpr bool Holding::any() const
{
    return data;
}

constexpr bool Holding::none() const
{
    return !data;
}

constexpr bool Holding::verify() const
{
    return (data & 0x7FFC) == data;
}

constexpr bool Holding::test(std::size_t position) const
{
    return data & (1 << position);
}

constexpr bool Holding::operator[](std::size_t position) const
{
    return test(position);
}

constexpr std::size_t Holding::count() const
{
#ifdef __POPCNT__
    return __builtin_popcount(data);
#else
    return (data * UINT64_C(0x200040008001) & UINT64_C(0x111111111111111)) % 0xF;
#endif
}

constexpr std::size_t Holding::size() const
{
    return 15;
}

Holding& Holding::normalize()
{
    data &= 0x7FFC;
    return *this;
}

Holding& Holding::flip()
{
    data = ~data;
    return *this;
}

Holding& Holding::flip(std::size_t position)
{
    data ^= 1 << position;
    return *this;
}

Holding& Holding::set()
{
    data = -1;
    return *this;
}

Holding& Holding::set(std::size_t position, bool value)
{
    if (value)
        data |= 1 << position;
    else
        data &= ~(1 << position);

    return *this;
}

Holding& Holding::reset()
{
    data = 0;
    return *this;
}

Holding& Holding::reset(std::size_t position)
{
    data &= ~(1 << position);
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
