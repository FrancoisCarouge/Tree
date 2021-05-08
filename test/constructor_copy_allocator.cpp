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

#include <memory>
// std::allocator

#include <set>
// std::multiset

#include <type_traits>
// std::is_copy_constructible_v

namespace
{
//! @test Verify the copy construction with allocator exists and its exception
//! specification.
[[maybe_unused]] constexpr auto traits = []() {
  // The container cannot satisty trivial copy construction because it is not a
  // scalar type, trivially copyable class, or array of such type/class. It has
  // non-static members with default initializers. The destructor is user
  // provided.
  static_assert(
      std::is_constructible_v<fcarouge::tree<char>, fcarouge::tree<char> &,
                              std::allocator<char> &>,
      "The container must be constructible from copying a tree and "
      "allocator.");
  // The container exception specification for copy construction with a custom
  // allocator is to be confirmed.

  return 0;
}();

//! @test Verify copy construction of an empty tree.
[[maybe_unused]] auto empty = []() {
  fcarouge::tree<int> auffay_linden;
  std::allocator<int> allocator;
  fcarouge::tree<int, decltype(allocator)> bunodiere_beech(auffay_linden,
                                                           allocator);

  assert(0 == bunodiere_beech.size() &&
         "The container must contain zero node.");
  assert(bunodiere_beech.empty() && "The container must be empty.");
  assert(bunodiere_beech.begin() == bunodiere_beech.end() &&
         "The container's beginning and ending iterators must be equal.");
  assert(bunodiere_beech.cbegin() == bunodiere_beech.cend() &&
         "The container's beginning and ending constant container iterators "
         "must be equal.");

  return 0;
}();

//! @test Verify copy construction of a one element tree.
[[maybe_unused]] auto one = []() {
  fcarouge::tree<int> auffay_linden(42);
  std::allocator<int> allocator;
  fcarouge::tree<int, decltype(allocator)> bunodiere_beech(auffay_linden,
                                                           allocator);

  assert(1 == bunodiere_beech.size() && "The container must contain one node.");
  assert(!bunodiere_beech.empty() && "The container must not be empty.");
  assert(42 == bunodiere_beech.front() &&
         "The container's front value and value used for construction "
         "must be equal on copy construction.");

  return 0;
}();

//! @test Verify the post conditions on a copied non-trivial tree with a custom
//! allocator.
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
  std::allocator<int> allocator;
  const fcarouge::tree<int, decltype(allocator)> allouville_oak(auffay_linden,
                                                                allocator);

  assert(
      13 == allouville_oak.size() &&
      "The container must have thirteen nodes upon pushing 13 element values.");
  assert(
      *node0 == allouville_oak.front() &&
      "The container's front value must be equal to the expected root value.");

  const std::multiset<int> expected_content{ 0,  1,  2,  3,  11, 12, 13,
                                             21, 22, 23, 31, 32, 33 };
  const std::multiset<int> content(allouville_oak.begin(),
                                   allouville_oak.end());

  assert(expected_content == content &&
         "Each element must be visited exactly once.");

  return 0;
}();

} // namespace
