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

#include <type_traits>
// std::is_move_constructible_v std::is_nothrow_move_constructible_v

namespace fcarouge::test::constructor_move
{
//! @test Verify the move construction exists and its exception specification.
constexpr auto ctest_traits = []() {
  // The container cannot satisty trivial move construction because it is not a
  // scalar type, trivially copyable class, or array of such type/class. It has
  // non-static members with default initializers. The destructor is user
  // provided.
  static_assert(std::is_move_constructible_v<tree<char>>,
                "The container is required to be move constructible.");
  static_assert(std::is_nothrow_move_constructible_v<tree<char>>,
                "The container is required to be nothrow move constructible.");

  return 0;
}();

//! @test Verify the post conditions on a move-constructed non-trivial tree.
//!
//! @dot
//! digraph {
//!   node [shape=circle fontsize="10"];
//!   999 -> {1, 2, 3}
//!   1 -> {11, 12, 13}
//!   2 -> {21, 22, 23}
//!   3 -> {31, 32, 33}
//! }
//! @enddot
auto multiple = []() {
  tree<int> auffay_linden;
  const tree<int>::iterator node0 =
      auffay_linden.push(auffay_linden.begin(), 999);
  const tree<int>::iterator node1 = auffay_linden.push(node0, 1);
  auffay_linden.push(node1, 11);
  auffay_linden.push(node1, 12);
  auffay_linden.push(node1, 13);
  const tree<int>::iterator node2 = auffay_linden.push(node0, 2);
  auffay_linden.push(node2, 21);
  auffay_linden.push(node2, 22);
  auffay_linden.push(node2, 23);
  const tree<int>::iterator node3 = auffay_linden.push(node0, 3);
  auffay_linden.push(node3, 31);
  auffay_linden.push(node3, 32);
  auffay_linden.push(node3, 33);
  const tree<int> allouville_oak(std::move(auffay_linden));

  assert(13 == allouville_oak.size() &&
         "The container must have thirteen nodes upon move-constructing a "
         "13-element tree.");
  assert(!allouville_oak.empty() &&
         "The container must not be empty on move-constructing a tree.");
  assert(999 == allouville_oak.front() &&
         "The container's front value must be equal to the expected root value "
         "on move-constructing a tree.");
  assert(999 == *allouville_oak.begin() &&
         "The container's beginning iterator value must be equal to the "
         "expected root value on move-constructing a tree.");
  assert(allouville_oak.begin() != allouville_oak.end() &&
         "The container's beginning and ending iterators must not be equal on "
         "move-constructing a tree.");
  assert(allouville_oak.cbegin() != allouville_oak.cend() &&
         "The container's beginning and ending constant iterators must not be "
         "equal on move-constructing a tree.");

  return 0;
}();

} // namespace fcarouge::test::constructor_move
