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

#include <set>
// std::multiset

namespace
{
//! @test Verify the depth of the root on a constant container.
[[maybe_unused]] auto root_const = []() {
  const fcarouge::tree<int> maucomble_boxwood(42);
  assert(0 == maucomble_boxwood.begin().depth() &&
         "The root depth must be equal to zero.");

  return 0;
}();

//! @test Verify the depth of the root.
[[maybe_unused]] auto root = []() {
  fcarouge::tree<int> maucomble_boxwood(42);
  assert(0 == maucomble_boxwood.begin().depth() &&
         "The root depth must be equal to zero.");

  return 0;
}();

//! @test Verify the depth of all the nodes of a complex container.
//!
//! @dot
//! digraph {
//!   node [shape=circle fontsize="10"];
//!   0 -> {1, 2, 3}
//!   1 -> {11, 12, 13}
//!   2 -> {21, 22, 23}
//!   3 -> {31, 32, 33}
//! }
//! @enddot
[[maybe_unused]] auto complex = []() {
  fcarouge::tree<int> auffay_linden;
  const fcarouge::tree<int>::iterator node0 =
      auffay_linden.push(auffay_linden.begin(), 0);
  const fcarouge::tree<int>::iterator node1 = auffay_linden.push(node0, 1);
  auffay_linden.push(node1, 11);
  auffay_linden.push(node1, 12);
  auffay_linden.push(node1, 13);
  const fcarouge::tree<int>::iterator node2 = auffay_linden.push(node0, 2);
  auffay_linden.push(node2, 21);
  auffay_linden.push(node2, 22);
  auffay_linden.push(node2, 23);
  const fcarouge::tree<int>::iterator node3 = auffay_linden.push(node0, 3);
  auffay_linden.push(node3, 31);
  auffay_linden.push(node3, 32);
  auffay_linden.push(node3, 33);
  const std::multiset<int> expected_content{ 0, 1, 1, 1, 2, 2, 2,
                                             2, 2, 2, 2, 2, 2 };
  std::multiset<int> iterated_depth;
  for (auto iterator = auffay_linden.begin(); iterator != auffay_linden.end();
       ++iterator) {
    iterated_depth.insert(iterator.depth());
  }

  assert(expected_content == iterated_depth &&
         "The depths of the container elements must meet requirements.");

  return 0;
}();

} // namespace
