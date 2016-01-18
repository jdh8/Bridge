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

#ifndef BRIDGE_CONST_HPP
#define BRIDGE_CONST_HPP

namespace Bridge {
/*!
 * \brief The 5 denominations, \e aka strains.
 *
 * The values are compatible with dds-bridge/dds, \e the double-dummy solver.
 *
 * \warning Notrump is closer to Clubs instead of Spades.
 */
enum class Denomination: unsigned char {
    Spades,   //!< \brief The spade suit
    Hearts,   //!< \brief The heart suit
    Diamonds, //!< \brief The diamond suit
    Clubs,    //!< \brief The club suit

    /*!
     * \brief No trump
     * \warning Notrump is closer to Clubs instead of Spades.
     */
    Notrump
};

//! \brief Enumeration of doubles.
enum class Double: unsigned char {
    _, //!< \brief No double
    X, //!< \brief Double
    XX //!< \brief Redouble
};

template<typename T> class Symbol;

template<>
struct Symbol<char>
{
    static constexpr char values[][4] = { "\u2660", "\u2665", "\u2666", "\u2663", "NT" };
};

template<>
struct Symbol<char16_t>
{
    static constexpr char16_t values[][3] = { u"\u2660", u"\u2665", u"\u2666", u"\u2663", u"NT" };
};

template<>
struct Symbol<char32_t>
{
    static constexpr char32_t values[][3] = { U"\u2660", U"\u2665", U"\u2666", U"\u2663", U"NT" };
};

constexpr char Symbol<char>::values [][4];
constexpr char16_t Symbol<char16_t>::values [][3];
constexpr char32_t Symbol<char32_t>::values [][3];

} // namespace Bridge

#endif // BRIDGE_CONST_HPP
