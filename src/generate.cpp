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
#include <fstream>
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

Deal::operator ::ddTableDeal() const
{
    return {{
        {
            _data[0][Denomination::Spades].cast(),
            _data[0][Denomination::Hearts].cast(),
            _data[0][Denomination::Diamonds].cast(),
            _data[0][Denomination::Clubs].cast()
        },
        {
            _data[1][Denomination::Spades].cast(),
            _data[1][Denomination::Hearts].cast(),
            _data[1][Denomination::Diamonds].cast(),
            _data[1][Denomination::Clubs].cast()
        },
        {
            _data[2][Denomination::Spades].cast(),
            _data[2][Denomination::Hearts].cast(),
            _data[2][Denomination::Diamonds].cast(),
            _data[2][Denomination::Clubs].cast()
        },
        {
            _data[3][Denomination::Spades].cast(),
            _data[3][Denomination::Hearts].cast(),
            _data[3][Denomination::Diamonds].cast(),
            _data[3][Denomination::Clubs].cast()
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
    const T table[] = { 0, 0, '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A' };

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

Table::Table(const ::ddTableResults& table):
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
    const char hex[] = "0123456789ABCDEF";

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

template<typename T, typename Data>
static std::basic_ostream<T>& write(std::basic_ostream<T>& stream, const Data& data)
{
    return stream.write(reinterpret_cast<const T*>(&data), sizeof(Data));
}

static int procedure(std::size_t number, const char* filename)
{
    Bridge::Deal deal;
    std::ofstream stream(filename, std::ios_base::binary);

    if (stream.rdstate()) {
        std::clog << "Error opening " << filename << '\n';
        return 2;
    }

    for (; number; --number) {
        deal = Bridge::Deal::Random();
        assert(deal.verify() && "The generated deal does not verify.");

        write(stream, deal);
        write(stream, deal.solve());
    }

    return 0;
}

static int procedure(std::size_t number)
{
    Bridge::Deal deal;

    for (; number; --number) {
        deal = Bridge::Deal::Random();
        assert(deal.verify() && "The generated deal does not verify.");
        std::cout << deal << ' ' << deal.solve() << '\n';
    }

    return 0;
}

static int usage(std::ostream& stream, const char* program)
{
    stream << "Usage: " << program << " NUMBER [FILE]\n\n"
        "This program generates bridge deals and their double-dummy solutions.\n\n"
        "By default, text-based deals and solutions are written to the standard output.\n"
        "However, if FILE is given, it is written in binary format.\n\n"
        "This program is single-threaded to avoid race condition in I/O.  To make use\n"
        "of multiple computing units, please run several instances with different\n"
        "output streams.\n";

    return 1;
}

int main(int argc, char** argv)
{
    std::size_t number;

    std::ios_base::sync_with_stdio(false);

    switch (argc) {
      case 0:
        return usage(std::cout, "generate");
      case 1:
        return usage(std::cout, argv[0]);

      case 2:
        std::istringstream(argv[1]) >> number;
        return number ? procedure(number) : usage(std::clog, argv[0]);

      case 3:
        std::istringstream(argv[1]) >> number;
        return number ? procedure(number, argv[2]) : usage(std::clog, argv[0]);

      default:
        return usage(std::cerr, argv[0]);
    }
}
