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

namespace
{
//! @test Verify the post conditions on inserting an element at the beginning
//! iterator of an emptry tree.
[[maybe_unused]] auto empty_begin = []() {
  fcarouge::tree<int> allouville_oak;
  const int value = 42;
  const fcarouge::tree<int>::iterator node =
      allouville_oak.insert(allouville_oak.begin(), value);

  assert(1 == allouville_oak.size() &&
         "The container must contain one element as built.");
  assert(node == allouville_oak.begin() &&
         "The container's beginning iterator must be equal to the expected "
         "root node.");
  assert(
      42 == *allouville_oak.begin() &&
      "The container's beginning iterator value must be equal to the expected "
      "root node value.");
  assert(
      *node == *allouville_oak.begin() &&
      "The container's beginning iterator value must be equal to the expected "
      "root node value.");
  assert(*node == *allouville_oak.cbegin() &&
         "The container's constant beginning iterator value must be equal to "
         "the expected root node value.");
  assert(*node == allouville_oak.front() &&
         "The container's front node value must be equal to the expected root "
         "node value.");

  return 0;
}();

//! @test Verify the post conditions on inserting an element at the ending
//! iterator of an emptry tree.
[[maybe_unused]] auto empty_end = []() {
  fcarouge::tree<int> allouville_oak;
  const int value = 42;
  const fcarouge::tree<int>::iterator node =
      allouville_oak.insert(allouville_oak.end(), value);

  assert(1 == allouville_oak.size() &&
         "The container must contain one element as built.");
  assert(node == allouville_oak.begin() &&
         "The container's beginning iterator must be equal to the expected "
         "root node.");
  assert(
      42 == *allouville_oak.begin() &&
      "The container's beginning iterator value must be equal to the expected "
      "root node value.");
  assert(
      *node == *allouville_oak.begin() &&
      "The container's beginning iterator value must be equal to the expected "
      "root node value.");
  assert(*node == *allouville_oak.cbegin() &&
         "The container's constant beginning iterator value must be equal to "
         "the expected root node value.");
  assert(*node == allouville_oak.front() &&
         "The container's front node value must be equal to the expected root "
         "node value.");

  return 0;
}();

//! @test Verify the post conditions on inserting an element at the root
//! iterator.
[[maybe_unused]] auto root_begin = []() {
  fcarouge::tree<int> allouville_oak(42);
  const int value = 41;
  const fcarouge::tree<int>::iterator node =
      allouville_oak.insert(allouville_oak.begin(), value);

  assert(2 == allouville_oak.size() &&
         "The container must contain one element as built.");
  assert(41 == *node && "The container's node iterator value must be equal to "
                        "the expected value.");

  return 0;
}();

//! @test Verify the post conditions on inserting an element at the ending
//! iterator of a tree with a single node.
[[maybe_unused]] auto root_end = []() {
  fcarouge::tree<int> allouville_oak(42);
  const int value = 43;
  allouville_oak.insert(allouville_oak.end(), value);

  assert(2 == allouville_oak.size() &&
         "The container must contain one element as built.");
  assert(
      42 == *allouville_oak.begin() &&
      "The container's beginning iterator value must be equal to the expected "
      "root node value.");

  return 0;
}();

//! @test Verify the post conditions on a non-trivial tree built by inserting
//! elements.
//!
//! @dot
//! digraph {
//!   node [shape=circle fontsize="10"];
//!   -1 -> {1, 2, 3}
//!   3 -> {31, 32, 33}
//!   33 -> {331, 332, 333}
//! }
//! @enddot
//!
[[maybe_unused]] auto multiple = []() {
  fcarouge::tree<int> allouville_oak;
  int value = 33;
  const fcarouge::tree<int>::iterator node33 =
      allouville_oak.insert(allouville_oak.begin(), value);
  value = 3;
  const fcarouge::tree<int>::iterator node3 =
      allouville_oak.insert(node33, value);
  value = 333;
  const fcarouge::tree<int>::iterator node333 =
      allouville_oak.insert(allouville_oak.end(), value);
  value = -1;
  const fcarouge::tree<int>::const_iterator node0 =
      allouville_oak.insert(allouville_oak.begin(), value);
  value = 1;
  allouville_oak.insert(node3, value);
  value = 2;
  allouville_oak.insert(node3, value);
  value = 31;
  allouville_oak.insert(node33, value);
  value = 32;
  allouville_oak.insert(node33, value);
  value = 331;
  allouville_oak.insert(node333, value);
  value = 332;
  allouville_oak.insert(node333, value);

  assert(10 == allouville_oak.size() &&
         "The container must contain 10 elements as built.");
  assert(-1 == *node0 &&
         "The container's node iterator value must be equal to the expected "
         "node value.");

  return 0;
}();

} // namespace
