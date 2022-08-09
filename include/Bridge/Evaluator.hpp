// This file is part of Bridge, a library and utility for bridge.
//
// Copyright (C) 2022 Chen-Pang He <https://jdh8.org/>
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

#include "Deal.hpp"
#include <Eigen/Core>

namespace Bridge {

template <typename F>
auto addShortness(const F &f)
{
  return [&f](Holding holding)
  {
    const auto points = f(holding);
    const decltype(points) shortness = 3 - std::min<int>(holding.size(), 3);
    return std::max(std::max(points, shortness), points + shortness - 1);
  };
}

template <typename F>
auto apply(const F &f, const Hand &hand)
{
  return f(hand[Strain::C]) + f(hand[Strain::D]) + f(hand[Strain::H]) + f(hand[Strain::S]);
}

template <typename T>
struct Evaluator : private Eigen::Matrix<T, Eigen::Dynamic, 1, Eigen::ColMajor, 12>
{
  using Eigen::Matrix<T, Eigen::Dynamic, 1, Eigen::ColMajor, 12>::Matrix;

  T operator()(Holding holding) const
  {
    T points {};

    for (typename Evaluator::Index i = 0; i < this->size(); ++i)
      points += (*this)[i] * holding.test(14 - i);

    return points;
  }
};

const Evaluator<int> HCP {{ 4, 3, 2, 1 }};
const Evaluator<float> BUMRAP {{ 4.5f, 3.0f, 1.5f, 0.75f, 0.25f }};

// https://bridge.thomasoandrews.com/valuations/cardvaluesfor3nt.html
// We use 10x values to avoid floating-point errors
const Evaluator<int> Fifths {{ 40, 28, 18, 10, 4 }};

} // namespace Bridge
