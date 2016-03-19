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

#ifndef BRIDGE_BINARY_HPP
#define BRIDGE_BINARY_HPP

#include <iosfwd>

namespace Bridge {

template<typename Derived>
struct Binary
{
    template<typename T>
    std::basic_istream<T>& read(std::basic_istream<T>&);

    template<typename T>
    std::basic_ostream<T>& write(std::basic_ostream<T>&) const;
};

template<typename Derived>
template<typename T>
std::basic_istream<T>& Binary<Derived>::read(std::basic_istream<T>& stream)
{
    Derived* derived = static_cast<Derived*>(this);
    T* buffer = reinterpret_cast<T*>(derived);

    return stream.read(buffer, sizeof(Derived));
}

template<typename Derived>
template<typename T>
std::basic_ostream<T>& Binary<Derived>::write(std::basic_ostream<T>& stream) const
{
    const Derived* derived = static_cast<const Derived*>(this);
    const T* buffer = reinterpret_cast<const T*>(derived);

    return stream.write(buffer, sizeof(Derived));
}

} // namespace Bridge

#endif // BRIDGE_BINARY_HPP
