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

namespace fcarouge::test::push_lvalue
{
//! @test Verify the post conditions on pushing an element by value upon the
//! beginning iterator of an empty container.
auto test_one_beginning = []() {
  tree<int> auffay_linden;
  const int value = 42;
  const tree<int>::const_iterator element =
      auffay_linden.push(auffay_linden.begin(), value);

  assert(1 == auffay_linden.size() &&
         "The container must have one node upon pushing one value.");
  assert(*element == 42 && "The solely pushed element iterator value must be "
                           "equal to pushed value.");
  assert(element == auffay_linden.begin() &&
         "The solely pushed element iterator must be equal to the container's "
         "beginning iterator.");
  assert(*element == *auffay_linden.begin() &&
         "The solely pushed element iterator value must be equal to the "
         "container's beginning iterator value.");
  assert(*element == auffay_linden.front() &&
         "The solely pushed element iterator value must be equal to the "
         "container's front value.");

  return 0;
}();

//! @test Verify the post conditions on pushing an element by value upon the
//! ending iterator of an empty container.
auto test_one_ending = []() {
  tree<int> auffay_linden;
  const int value = 42;
  const tree<int>::const_iterator element =
      auffay_linden.push(auffay_linden.end(), value);

  assert(1 == auffay_linden.size() &&
         "The container must have one node upon pushing one value.");
  assert(*element == 42 && "The solely pushed element iterator value must be "
                           "equal to pushed value.");
  assert(element == auffay_linden.begin() &&
         "The solely pushed element iterator must be equal to the container's "
         "beginning iterator.");
  assert(*element == *auffay_linden.begin() &&
         "The solely pushed element iterator value must be equal to the "
         "container's beginning iterator value.");
  assert(*element == auffay_linden.front() &&
         "The solely pushed element iterator value must be equal to the "
         "container's front value.");

  return 0;
}();

//! @test Verify the post conditions on pushing another element by value upon
//! the beginning iterator of a container containing a single value.
auto test_two_beginning = []() {
  const int first_value = 41;
  tree<int> auffay_linden;
  auffay_linden.push(auffay_linden.begin(), first_value);
  const int second_value = 42;
  const tree<int>::const_iterator element =
      auffay_linden.push(auffay_linden.begin(), second_value);

  assert(2 == auffay_linden.size() &&
         "The container must have two nodes upon pushing a second value.");
  assert(*element == 42 && "The pushed element iterator value must be "
                           "equal to pushed value.");

  return 0;
}();

//! @test Verify the post conditions on pushing another element by value upon
//! the ending iterator of a container containing a single value.
auto test_two_ending = []() {
  const int first_value = 41;
  tree<int> auffay_linden;
  auffay_linden.push(auffay_linden.end(), first_value);
  const int second_value = 42;
  const tree<int>::const_iterator element =
      auffay_linden.push(auffay_linden.end(), second_value);

  assert(2 == auffay_linden.size() &&
         "The container must have two nodes upon pushing a second value.");
  assert(*element == 42 && "The pushed element iterator value must be "
                           "equal to pushed value.");

  return 0;
}();

//! @test Verify the post conditions on a non-trivial tree built by pushing
//! elements.
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
  int value = 0;
  tree<int>::iterator node0 = auffay_linden.push(auffay_linden.begin(), value);
  value = 1;
  tree<int>::iterator node1 = auffay_linden.push(node0, value);
  value = 11;
  auffay_linden.push(node1, value);
  value = 12;
  auffay_linden.push(node1, value);
  value = 13;
  auffay_linden.push(node1, value);
  value = 2;
  tree<int>::iterator node2 = auffay_linden.push(node0, value);
  value = 21;
  auffay_linden.push(node2, value);
  value = 22;
  auffay_linden.push(node2, value);
  value = 23;
  auffay_linden.push(node2, value);
  value = 3;
  tree<int>::iterator node3 = auffay_linden.push(node0, value);
  value = 31;
  auffay_linden.push(node3, value);
  value = 32;
  auffay_linden.push(node3, value);
  value = 33;
  auffay_linden.push(node3, value);
  const std::multiset<int> expected_content{ 0,  1,  2,  3,  11, 12, 13,
                                             21, 22, 23, 31, 32, 33 };
  std::multiset<int> iterated_content;
  tree<int>::const_iterator iterator = auffay_linden.begin();
  for (; iterator != auffay_linden.end(); ++iterator) {
    iterated_content.insert(*iterator);
  }

  assert(13 == auffay_linden.size() &&
         "The container must have 13 nodes upon pushing 13 element values.");
  assert(node0 == auffay_linden.begin() &&
         "The container's beginning iterator must be equal to the expected "
         "root node.");
  assert(
      *node0 == auffay_linden.front() &&
      "The container's front value must be equal to the expected root value.");
  assert(expected_content == iterated_content &&
         "The container's content must meet expected content.");

  return 0;
}();

} // namespace fcarouge::test::push_lvalue
