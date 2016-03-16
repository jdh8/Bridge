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

#include <Bridge/Deal.hpp>
#include <Bridge/Result.hpp>
#include <dll.h>
#include <algorithm>
#include <random>
#include <iostream>
#include <sstream>
#include <cassert>

namespace Bridge {

Deal& Deal::operator=(Random)
{
    static std::mt19937 generator((std::random_device())());

    unsigned char deck[] = {
         8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
        21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,
        34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46,
        47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59
    };

    std::shuffle(deck, deck + 52, generator);

    for (int i = 0; i < 4; ++i) {
        const unsigned char* cards = deck + 13 * i;
        _data[i].reset();

        for (int j = 0; j < 13; ++j)
            _data[i][Denomination(cards[j] & 3)].set(cards[j] >> 2);
    }

    return *this;
}

constexpr Deal::operator ::ddTableDeal() const
{
    return {{
        {
            _data[0][Denomination::Spades].data,
            _data[0][Denomination::Hearts].data,
            _data[0][Denomination::Diamonds].data,
            _data[0][Denomination::Clubs].data
        },
        {
            _data[1][Denomination::Spades].data,
            _data[1][Denomination::Hearts].data,
            _data[1][Denomination::Diamonds].data,
            _data[1][Denomination::Clubs].data
        },
        {
            _data[2][Denomination::Spades].data,
            _data[2][Denomination::Hearts].data,
            _data[2][Denomination::Diamonds].data,
            _data[2][Denomination::Clubs].data
        },
        {
            _data[3][Denomination::Spades].data,
            _data[3][Denomination::Hearts].data,
            _data[3][Denomination::Diamonds].data,
            _data[3][Denomination::Clubs].data
        }
    }};
}

Result::Table Deal::solve() const
{
    ::ddTableResults result;
    ::CalcDDtable(*this, &result);

    return result;
}

template<typename T>
std::basic_ostream<T>& operator<<(std::basic_ostream<T>& stream, Holding holding)
{
    constexpr T table[] = { 0, 0, '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A' };

    for (int rank = 14; rank > 1; --rank)
        if (holding.test(rank))
            stream << table[rank];

    return stream;
}

template<typename T>
std::basic_ostream<T>& operator<<(std::basic_ostream<T>& stream, const Hand& hand)
{
    return stream << hand[Denomination::Spades] << '.'
                  << hand[Denomination::Hearts] << '.'
                  << hand[Denomination::Diamonds] << '.'
                  << hand[Denomination::Clubs];
}

template<typename T>
std::basic_ostream<T>& operator<<(std::basic_ostream<T>& stream, const Deal& deal)
{
    return stream << deal[Direction::North] << ' '
                  << deal[Direction::East] << ' '
                  << deal[Direction::South] << ' '
                  << deal[Direction::West];
}

namespace Result {

constexpr Table::Table(const ::ddTableResults& table):
    Table(
        table.resTable[3],
        table.resTable[2],
        table.resTable[1],
        table.resTable[0],
        table.resTable[4])
{}

template<typename T>
std::basic_ostream<T>& operator<<(std::basic_ostream<T>& stream, const Row& row)
{
    constexpr char hex[] = "0123456789ABCDEF";

    return stream << hex[row[Direction::North]]
                  << hex[row[Direction::East]]
                  << hex[row[Direction::South]]
                  << hex[row[Direction::West]];
}

template<typename T>
std::basic_ostream<T>& operator<<(std::basic_ostream<T>& stream, const Table& result)
{
    return stream << result[Denomination::Clubs]
                  << result[Denomination::Diamonds]
                  << result[Denomination::Hearts]
                  << result[Denomination::Spades]
                  << result[Denomination::Notrump];
}

} // namespace Result

} // namespace Bridge

static void procedure(std::size_t number)
{
    Bridge::Deal deal;

    for (; number; --number) {
        deal = Bridge::Deal::Random();
        assert(deal.verify() && "The generated deal does not verify.");
        std::cout << deal << ' ' << deal.solve() << '\n';
    }
}

static void usage(std::ostream& stream, const char* program)
{
    stream << "Usage: " << program << " NUMBER\n\n"
        "This program generates bridge deals and their double-dummy solutions.\n";
}

int main(int argc, char** argv)
{
    std::size_t number;

    if (argc == 1) {
        usage(std::cout, argv[0]);
    }
    else {
        std::istringstream(argv[1]) >> number;
        number ? procedure(number) : usage(std::cerr, argv[0]);
    }

    return 0;
}
