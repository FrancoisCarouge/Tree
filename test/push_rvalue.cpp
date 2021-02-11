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
//! @test Verify the post conditions on pushing a moved element upon the
//! beginning iterator of an empty container.
[[maybe_unused]] auto one_beginning = []() {
  fcarouge::tree<int> auffay_linden;
  const fcarouge::tree<int>::const_iterator element =
      auffay_linden.push(auffay_linden.begin(), 42);

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

//! @test Verify the post conditions on pushing a moved element upon the
//! ending iterator of an empty container.
[[maybe_unused]] auto one_ending = []() {
  fcarouge::tree<int> auffay_linden;
  const fcarouge::tree<int>::const_iterator element =
      auffay_linden.push(auffay_linden.end(), 42);

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

//! @test Verify the post conditions on pushing another moved element upon
//! the beginning iterator of a container containing a single value.
[[maybe_unused]] auto two_beginning = []() {
  fcarouge::tree<int> auffay_linden;
  auffay_linden.push(auffay_linden.begin(), 41);
  const fcarouge::tree<int>::const_iterator element =
      auffay_linden.push(auffay_linden.begin(), 42);

  assert(2 == auffay_linden.size() &&
         "The container must have two nodes upon pushing a second value.");
  assert(*element == 42 && "The pushed element iterator value must be "
                           "equal to pushed value.");

  return 0;
}();

//! @test Verify the post conditions on pushing another moved element upon
//! the ending iterator of a container containing a single value.
[[maybe_unused]] auto two_ending = []() {
  fcarouge::tree<int> auffay_linden;
  auffay_linden.push(auffay_linden.end(), 41);
  const fcarouge::tree<int>::const_iterator element =
      auffay_linden.push(auffay_linden.end(), 42);

  assert(2 == auffay_linden.size() &&
         "The container must have two nodes upon pushing a second value.");
  assert(*element == 42 && "The pushed element iterator value must be "
                           "equal to pushed value.");

  return 0;
}();

//! @test Verify the post conditions on pushing three elements by value upon
//! the ending iterator of a container containing a single value, exercising
//! pushing upon the root with child.
[[maybe_unused]] auto three_ending = []() {
  fcarouge::tree<int> auffay_linden;
  auffay_linden.push(auffay_linden.end(), 41);
  auffay_linden.push(auffay_linden.end(), 42);
  const fcarouge::tree<int>::const_iterator element =
      auffay_linden.push(auffay_linden.end(), 43);

  assert(3 == auffay_linden.size() &&
         "The container must have three nodes upon pushing a third value.");
  assert(*element == 43 && "The pushed element iterator value must be "
                           "equal to the pushed value.");

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
[[maybe_unused]] auto multiple = []() {
  fcarouge::tree<int> auffay_linden;
  fcarouge::tree<int>::iterator node0 =
      auffay_linden.push(auffay_linden.begin(), 0);
  fcarouge::tree<int>::iterator node1 = auffay_linden.push(node0, 1);
  auffay_linden.push(node1, 11);
  auffay_linden.push(node1, 12);
  auffay_linden.push(node1, 13);
  fcarouge::tree<int>::iterator node2 = auffay_linden.push(node0, 2);
  auffay_linden.push(node2, 21);
  auffay_linden.push(node2, 22);
  auffay_linden.push(node2, 23);
  fcarouge::tree<int>::iterator node3 = auffay_linden.push(node0, 3);
  auffay_linden.push(node3, 31);
  auffay_linden.push(node3, 32);
  auffay_linden.push(node3, 33);
  const std::multiset<int> expected_content{ 0,  1,  2,  3,  11, 12, 13,
                                             21, 22, 23, 31, 32, 33 };
  std::multiset<int> iterated_content;
  fcarouge::tree<int>::const_iterator iterator = auffay_linden.begin();
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

} // namespace
