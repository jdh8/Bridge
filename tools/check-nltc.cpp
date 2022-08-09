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

#include <Bridge/Evaluator.hpp>
#include <Bridge/DDS.hpp>
#include <Eigen/Core>
#include <iostream>

static int ltc(Bridge::Holding holding)
{
  const int length = std::min<int>(holding.size(), 3);
  return length - __builtin_popcount(holding.bits() >> (15 - length));
}

static float nltc(Bridge::Holding holding)
{
  const auto length = holding.size();

  return 1.5f * (length >= 1 && !holding.test(14))
       + 1.0f * (length >= 2 && !holding.test(13))
       + 0.5f * (length >= 3 && !holding.test(12));
}

static float altc(Bridge::Holding holding)
{
  return std::min<float>(nltc(holding), holding.size());
}

static auto observe(const Bridge::Result &solution, const Bridge::Deal &deal, Bridge::Seat seat)
{
  using namespace Bridge;
  Eigen::RowVector<double, 6> vector;

  vector.coeffRef(0) = std::max({
    solution(Strain::C, seat),
    solution(Strain::D, seat),
    solution(Strain::H, seat),
    solution(Strain::S, seat),
  });

  const Hand hand = deal[seat];
  vector.coeffRef(1) = apply(addShortness(HCP), hand);
  vector.coeffRef(2) = apply(addShortness(BUMRAP), hand);
  vector.coeffRef(3) = apply(ltc, hand);
  vector.coeffRef(4) = apply(nltc, hand);
  vector.coeffRef(5) = apply(altc, hand);
  return vector;
}

static auto observe(std::span<const Bridge::Result> solutions, std::span<const Bridge::Deal> deals)
{
  using namespace Bridge;
  using namespace Eigen;

  assert(solutions.size() == deals.size());
  const auto Cols = decltype(observe(std::declval<Result>(), {}, Seat::N))::ColsAtCompileTime;

  Matrix<double, Dynamic, Cols, RowMajor> result(4 * deals.size(), Cols);

  for (std::size_t i = 0; i < deals.size(); ++i)
    for (int seat = 0; seat < 4; ++seat)
      result.row(4 * i + seat) = observe(solutions[i], deals[i], static_cast<Seat>(seat));

  return result;
}

static void procedure(std::size_t number)
{
  std::vector<Bridge::Deal> deals;
  deals.reserve(number);
  std::generate_n(std::back_inserter(deals), number, Bridge::getRandomDeal);

  // Filter out notrump contracts
  const Bridge::StrainMask mask = { false, false, false, false, /*.n=*/true };
  const auto solutions = Bridge::solve(deals, mask);
  auto x = observe(solutions, deals);
  x.rowwise() -= x.colwise().mean();

  const auto covariance = ((x.adjoint() * x) / (x.rows() - 1)).eval();
  const auto diag = covariance.diagonal().array().rsqrt().eval();
  const auto r = (covariance.array().colwise() * diag).rowwise() * diag.transpose();

  std::cout << "   Tricks      HCP+  BUM-RAP+       LTC      NLTC      ALTC\n" << r << '\n';
}

int main(int argc, char **argv)
{
  if (argc < 2) {
    procedure(100);
    return 0;
  }

  if (argc == 2) {
    unsigned long number = std::strtoul(argv[1], nullptr, 10);

    if (number && number != static_cast<unsigned long>(-1)) {
      procedure(number);
      return 0;
    }
  }

  std::cout << "USAGE: " << argv[0] << " <number of deals>\n";
  return 1;
}
