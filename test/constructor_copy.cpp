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

#include <type_traits>
// std::is_copy_constructible_v

namespace
{
//! @test Verify the copy construction exists and its exception specification.
[[maybe_unused]] constexpr auto traits = []() {
  // The container cannot satisty trivial copy construction because it is not a
  // scalar type, trivially copyable class, or array of such type/class. It has
  // non-static members with default initializers. The destructor is user
  // provided.
  static_assert(std::is_copy_constructible_v<fcarouge::tree<char>>,
                "The container is required to be copy constructible.");
  // The container exception specification for copy construction with the
  // default standard allocator is to be confirmed.

  return 0;
}();

//! @test Verify the post conditions on a copied non-trivial tree.
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
[[maybe_unused]] auto multiple = []() {
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
  const fcarouge::tree<int> allouville_oak(auffay_linden);

  assert(
      13 == allouville_oak.size() &&
      "The container must have thirteen nodes upon pushing 13 element values.");
  assert(
      *node0 == allouville_oak.front() &&
      "The container's front value must be equal to the expected root value.");

  const std::multiset<int> expected_content{ 0,  1,  2,  3,  11, 12, 13,
                                             21, 22, 23, 31, 32, 33 };
  std::multiset<int> iterated_content;
  fcarouge::tree<int>::const_iterator iterator = allouville_oak.begin();
  for (; iterator != allouville_oak.end(); ++iterator) {
    iterated_content.insert(*iterator);
  }

  assert(expected_content == iterated_content &&
         "Each element must be visited exactly once.");

  return 0;
}();

} // namespace
