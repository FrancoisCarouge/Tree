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
// std::is_move_assignable_v std::is_nothrow_move_assignable_v

namespace fcarouge::test::operator_assignment_move
{
//! @test Verify the move assignment exists and its exception specification.
constexpr auto ctest_traits = []() {
  // The container cannot satisty trivial move assignment because it is not a
  // scalar type, trivially copyable class, or array of such type/class. It has
  // non-static members with default initializers. The destructor is user
  // provided.
  static_assert(std::is_move_assignable_v<tree<char>>,
                "The container is required to be move constructible.");
  static_assert(std::is_nothrow_move_assignable_v<tree<char>>,
                "The container is required to be nothrow move constructible.");

  return 0;
}();

//! @test Verify the post conditions on a moved assigned non-trivial tree.
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
auto test_multiple = []() {
  tree<int> auffay_linden;
  const tree<int>::iterator node0 =
      auffay_linden.push(auffay_linden.begin(), 0);
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
  tree<int> allouville_oak;
  allouville_oak = std::move(auffay_linden);
  const std::multiset<int> expected_content{ 0,  1,  2,  3,  11, 12, 13,
                                             21, 22, 23, 31, 32, 33 };
  std::multiset<int> iterated_content;
  tree<int>::const_iterator iterator = allouville_oak.begin();
  for (; iterator != allouville_oak.end(); ++iterator) {
    iterated_content.insert(*iterator);
  }

  assert(13 == allouville_oak.size() &&
         "The container must have thirteen nodes upon move-constructing a "
         "13-element tree.");
  assert(!allouville_oak.empty() &&
         "The container must not be empty on move-constructing a tree.");
  assert(0 == allouville_oak.front() &&
         "The container's front value must be equal to the expected root value "
         "on move-constructing a tree.");
  assert(0 == *allouville_oak.begin() &&
         "The container's beginning iterator value must be equal to the "
         "expected root value on move-constructing a tree.");
  assert(allouville_oak.begin() != allouville_oak.end() &&
         "The container's beginning and ending iterators must not be equal on "
         "move-constructing a tree.");
  assert(allouville_oak.cbegin() != allouville_oak.cend() &&
         "The container's beginning and ending constant iterators must not be "
         "equal on move-constructing a tree.");
  assert(expected_content == iterated_content &&
         "The container's content must meet expected content.");

  return 0;
}();

//! @test Verify the post conditions on a self moved assigned non-trivial tree.
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
auto test_self = []() {
  tree<int> auffay_linden;
  const tree<int>::iterator node0 =
      auffay_linden.push(auffay_linden.begin(), 0);
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
  auffay_linden = std::move(auffay_linden);
  const std::multiset<int> expected_content{ 0,  1,  2,  3,  11, 12, 13,
                                             21, 22, 23, 31, 32, 33 };
  std::multiset<int> iterated_content;
  tree<int>::const_iterator iterator = auffay_linden.begin();
  for (; iterator != auffay_linden.end(); ++iterator) {
    iterated_content.insert(*iterator);
  }

  assert(13 == auffay_linden.size() &&
         "The container must have thirteen nodes upon move-constructing a "
         "13-element tree.");
  assert(!auffay_linden.empty() &&
         "The container must not be empty on move-constructing a tree.");
  assert(0 == auffay_linden.front() &&
         "The container's front value must be equal to the expected root value "
         "on move-constructing a tree.");
  assert(0 == *auffay_linden.begin() &&
         "The container's beginning iterator value must be equal to the "
         "expected root value on move-constructing a tree.");
  assert(auffay_linden.begin() != auffay_linden.end() &&
         "The container's beginning and ending iterators must not be equal on "
         "move-constructing a tree.");
  assert(auffay_linden.cbegin() != auffay_linden.cend() &&
         "The container's beginning and ending constant iterators must not be "
         "equal on move-constructing a tree.");
  assert(expected_content == iterated_content &&
         "The container's content must meet expected content.");

  return 0;
}();

} // namespace fcarouge::test::operator_assignment_move
