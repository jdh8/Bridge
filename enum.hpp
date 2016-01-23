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

//! \brief Enumeration of the directions.
enum class Direction: unsigned char { North, East, South, West };

//! \brief Enumeration of doubles.
enum class Double: unsigned char {
    _, //!< \brief No double
    X, //!< \brief Double
    XX //!< \brief Redouble
};

} // namespace Bridge

#endif // BRIDGE_CONST_HPP
