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

#include "Deal.hpp"
#include <algorithm>
#include <random>

namespace Bridge {

void Deal::randomize()
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

        for (int j = 0; j < 13; ++j)
            _data[i][Denomination(cards[j] & 3)].set(cards[j] >> 2);
    }
}

} // namespace Bridge
