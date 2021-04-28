/*_______ _____  ______ ______
 |__   __|  __ \|  ____|  ____|  Tree data structure for C++
    | |  | |__) | |__  | |__     version 0.1.0
    | |  |  _  /|  __| |  __|    https://github.com/FrancoisCarouge/Tree
    | |  | | \ \| |____| |____
    |_|  |_|  \_\______|______|

Licensed under the MIT License <http://opensource.org/licenses/MIT>.
SPDX-License-Identifier: MIT
Copyright 2020 Francois Carouge.

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "fcarouge/tree.hpp"
// fcarouge::tree

#include <benchmark/benchmark.h>
// BENCHMARK benchmark::ClobberMemory benchmark::kNanosecond benchmark::State

#include <cassert>
// assert

#include <chrono>
// std::chrono::duration_cast std::chrono::high_resolution_clock
// benchmark::oAuto

namespace
{
//! @benchmark Measure the performance of the container's clearing algorithm.
void clear(benchmark::State &state)
{
  for (auto _ : state) {
    fcarouge::tree_uint64_t bunodiere_beech;
    for (int i = 0; i < state.range(0); ++i) {
      bunodiere_beech.emplace_front(i);
    }
    assert(state.range(0) == bunodiere_beech.size() &&
           "The size of the container does not meet expectations.");
    benchmark::ClobberMemory();

    auto start = std::chrono::high_resolution_clock::now();
    bunodiere_beech.clear();
    benchmark::ClobberMemory();
    auto end = std::chrono::high_resolution_clock::now();

    assert(0 == bunodiere_beech.size() &&
           "The size of the container does not meet expectations.");
    state.SetIterationTime(
        std::chrono::duration_cast<std::chrono::duration<double>>(end - start)
            .count());
  }
}

BENCHMARK(clear)
    ->Name("clear")
    ->Unit(benchmark::kNanosecond)
    ->ComputeStatistics("min",
                        [](const std::vector<double> &v) -> double {
                          return *(
                              std::min_element(std::begin(v), std::end(v)));
                        })
    ->ComputeStatistics("max",
                        [](const std::vector<double> &v) -> double {
                          return *(
                              std::max_element(std::begin(v), std::end(v)));
                        })
    ->Arg(0)
    ->UseManualTime()
    ->Complexity(benchmark::oAuto)
    ->DisplayAggregatesOnly(true)
    ->RangeMultiplier(2)
    ->Repetitions(10)
    ->Range(1, 1 << 28);

} // namespace
