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

    Holding();
    explicit Holding(std::uint16_t);

    bool all() const;
    bool any() const;
    bool verify() const;
    bool test(std::size_t) const;
    bool operator[](std::size_t) const;
    bool operator==(Holding) const;

    Holding operator~() const;
    Holding operator&(Holding) const;
    Holding operator^(Holding) const;
    Holding operator|(Holding) const;

    std::size_t count() const;
    std::size_t size() const;

    std::uint16_t cast() const;

    Holding& normalize();

    Holding& flip(std::size_t);
    Holding& reset(std::size_t);

    Holding& set();
    Holding& set(std::size_t, bool = true);

    reference operator[](std::size_t position);
};

inline
Holding::Holding():
    _data()
{}

inline
Holding::Holding(std::uint16_t value):
    _data(value)
{}

inline
bool Holding::all() const
{
    return (_data & 0x7FFC) == 0x7FFC;
}

inline
bool Holding::any() const
{
    return _data;
}

inline
bool Holding::verify() const
{
    return (_data & 0x7FFC) == _data;
}

inline
bool Holding::test(std::size_t position) const
{
    return _data & (1 << position);
}

inline
bool Holding::operator[](std::size_t position) const
{
    return test(position);
}

inline
bool Holding::operator==(Holding other) const
{
    return _data == other._data;
}

inline
Holding Holding::operator~() const
{
    return Holding(~_data);
}

inline
Holding Holding::operator&(Holding other) const
{
    return Holding(_data & other._data);
}

inline
Holding Holding::operator^(Holding other) const
{
    return Holding(_data ^ other._data);
}

inline
Holding Holding::operator|(Holding other) const
{
    return Holding(_data | other._data);
}

inline
std::size_t Holding::count() const
{
#ifdef __POPCNT__
    return __builtin_popcount(_data);
#else
    return (_data * UINT64_C(0x200040008001) & UINT64_C(0x111111111111111)) % 0xF;
#endif
}

inline
std::size_t Holding::size() const
{
    return 15;
}

inline
std::uint16_t Holding::cast() const
{
    return _data;
}

inline
Holding& Holding::normalize()
{
    _data &= 0x7FFC;
    return *this;
}

inline
Holding& Holding::flip(std::size_t position)
{
    _data ^= 1 << position;
    return *this;
}

inline
Holding& Holding::reset(std::size_t position)
{
    _data &= ~(1 << position);
    return *this;
}

inline
Holding& Holding::set()
{
    _data = -1;
    return *this;
}

inline
Holding& Holding::set(std::size_t position, bool value)
{
    if (value)
        _data |= 1 << position;
    else
        _data &= ~(1 << position);

    return *this;
}

class Holding::reference
{
    friend reference Holding::operator[](std::size_t position);

  private:
    Holding& _parent;
    std::size_t _position;

    reference(Holding&, std::size_t);

  public:
    operator bool() const;
    bool operator~() const;

    reference& operator=(bool);
    reference& operator=(const reference&);

    reference& flip();
};

inline
Holding::reference::reference(Holding& parent, std::size_t position):
    _parent(parent),
    _position(position)
{}

inline
Holding::reference::operator bool() const
{
    return _parent.test(_position);
}

inline
bool Holding::reference::operator~() const
{
    return !_parent.test(_position);
}

inline
Holding::reference& Holding::reference::operator=(bool value)
{
    _parent.set(_position, value);
    return *this;
}

inline
Holding::reference& Holding::reference::operator=(const reference& ref)
{
    return *this = bool(ref);
}

inline
Holding::reference& Holding::reference::flip()
{
    _parent.flip(_position);
    return *this;
}

inline
Holding::reference Holding::operator[](std::size_t position)
{
    return { *this, position };
}

} // namespace Bridge

#endif // BRIDGE_HOLDING_HPP
