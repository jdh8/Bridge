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

#ifndef BRIDGE_MASK_HPP
#define BRIDGE_MASK_HPP

namespace Bridge {

template<typename Derived>
struct Mask
{
    constexpr const Derived& derived() const;
    Derived& derived();

    constexpr bool none() const;

    Derived& flip();
    Derived& reset();

    Derived& operator&=(Derived);
    Derived& operator^=(Derived);
    Derived& operator|=(Derived);
};

template<typename Derived>
constexpr const Derived& Mask<Derived>::derived() const
{
    return static_cast<const Derived&>(*this);
}

template<typename Derived>
Derived& Mask<Derived>::derived()
{
    return static_cast<Derived&>(*this);
}

template<typename Derived>
constexpr bool Mask<Derived>::none() const
{
    return derived().any();
}

template<typename Derived>
Derived& Mask<Derived>::flip()
{
    return derived() = ~derived();
}

template<typename Derived>
Derived& Mask<Derived>::reset()
{
    return derived() = Derived();
}

template<typename Derived>
Derived& Mask<Derived>::operator&=(Derived other)
{
    return derived() = derived() & other;
}

template<typename Derived>
Derived& Mask<Derived>::operator^=(Derived other)
{
    return derived() = derived() ^ other;
}

template<typename Derived>
Derived& Mask<Derived>::operator|=(Derived other)
{
    return derived() = derived() | other;
}

} // namespace Bridge

#endif // BRIDGE_MASK_HPP
