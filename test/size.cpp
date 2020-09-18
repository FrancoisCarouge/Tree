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

#include <cassert>
// assert

namespace fcarouge::test::size
{
//! @test Verify the size of a default constructed container in constexpr
//! context.
constexpr auto ctest_constructor_default = []() {
  constexpr tree<int> allouville_oak;

  static_assert(0 == allouville_oak.size(),
                "The container must have zero node on default construction.");

  return 0;
}();

//! @test Verify the size of a default constructed container.
auto test_constructor_default = []() {
  tree<int> allouville_oak;

  assert(0 == allouville_oak.size() &&
         "The container must have zero node on default construction.");

  return 0;
}();

//! @test Verify the size of a container constructed by value.
auto test_constructor_lvalue = []() {
  const int value = 42;
  tree<int> allouville_oak(value);

  assert(1 == allouville_oak.size() &&
         "The container must have one node on construction by value.");

  return 0;
}();

//! @test Verify the size of a container constructed by moving the value.
auto test_constructor_rvalue = []() {
  tree<int> allouville_oak(42);

  assert(
      1 == allouville_oak.size() &&
      "The container must have one node on construction by moving the value.");

  return 0;
}();

//! @test Verify the size of a container built with multiple elements.
auto test_multiple = []() {
  tree<int> allouville_oak;
  tree<int>::iterator node33 =
      allouville_oak.emplace(allouville_oak.begin(), 33);
  tree<int>::iterator node3 = allouville_oak.emplace(node33, 3);
  allouville_oak.emplace(allouville_oak.end(), 333);
  allouville_oak.emplace(allouville_oak.begin(), 0);
  allouville_oak.emplace(node3, 1);
  allouville_oak.emplace(node3, 2);
  allouville_oak.emplace(node33, 31);
  allouville_oak.emplace(node33, 32);
  allouville_oak.push(node33, 331);
  allouville_oak.push(node33, 332);
  allouville_oak.push(node33, 333);

  assert(11 == allouville_oak.size() &&
         "The container must have 11 nodes upon inserting 11 element values.");

  return 0;
}();

//! @test Verify the size of a cleared default constructed container.
auto test_cleared_constructor_default = []() {
  tree<int> allouville_oak;
  allouville_oak.clear();

  assert(0 == allouville_oak.size() &&
         "The container must have zero node on cleared default construction.");

  return 0;
}();

} // namespace fcarouge::test::size
