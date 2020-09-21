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

namespace fcarouge::test::push_rvalue
{
//! @test Verify the post conditions on pushing a moved element upon the
//! beginning iterator of an empty container.
auto test_one_beginning = []() {
  tree<int> auffay_linden;
  const tree<int>::const_iterator element =
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
  assert(*element == auffay_linden.back() &&
         "The solely pushed element iterator value must be equal to the "
         "container's back value.");

  return 0;
}();

//! @test Verify the post conditions on pushing a moved element upon the
//! ending iterator of an empty container.
auto test_one_ending = []() {
  tree<int> auffay_linden;
  const tree<int>::const_iterator element =
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
  assert(*element == auffay_linden.back() &&
         "The solely pushed element iterator value must be equal to the "
         "container's back value.");

  return 0;
}();

//! @test Verify the post conditions on pushing another moved element upon
//! the beginning iterator of a container containing a single value.
auto test_two_beginning = []() {
  tree<int> auffay_linden;
  auffay_linden.push(auffay_linden.begin(), 41);
  const tree<int>::const_iterator element =
      auffay_linden.push(auffay_linden.begin(), 42);

  assert(2 == auffay_linden.size() &&
         "The container must have two nodes upon pushing a second value.");
  assert(*element == 42 && "The pushed element iterator value must be "
                           "equal to pushed value.");
  assert(
      *element == auffay_linden.back() &&
      "The second and last pushed element iterator value must be equal to the "
      "container's back value.");

  return 0;
}();

//! @test Verify the post conditions on pushing another moved element upon
//! the ending iterator of a container containing a single value.
auto test_two_ending = []() {
  tree<int> auffay_linden;
  auffay_linden.push(auffay_linden.end(), 41);
  const tree<int>::const_iterator element =
      auffay_linden.push(auffay_linden.end(), 42);

  assert(2 == auffay_linden.size() &&
         "The container must have two nodes upon pushing a second value.");
  assert(*element == 42 && "The pushed element iterator value must be "
                           "equal to pushed value.");
  assert(
      *element == auffay_linden.back() &&
      "The second and last pushed element iterator value must be equal to the "
      "container's back value.");

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
  tree<int>::iterator node0 = auffay_linden.push(auffay_linden.begin(), 0);
  tree<int>::iterator node1 = auffay_linden.push(node0, 1);
  auffay_linden.push(node1, 11);
  auffay_linden.push(node1, 12);
  auffay_linden.push(node1, 13);
  tree<int>::iterator node2 = auffay_linden.push(node0, 2);
  auffay_linden.push(node2, 21);
  auffay_linden.push(node2, 22);
  auffay_linden.push(node2, 23);
  tree<int>::iterator node3 = auffay_linden.push(node0, 3);
  auffay_linden.push(node3, 31);
  auffay_linden.push(node3, 32);
  auffay_linden.push(node3, 33);

  assert(13 == auffay_linden.size() &&
         "The container must have 13 nodes upon pushing 13 element values.");
  assert(node0 == auffay_linden.begin() &&
         "The container's beginning iterator must be equal to the expected "
         "root node.");
  assert(
      *node0 == auffay_linden.front() &&
      "The container's front value must be equal to the expected root value.");

  return 0;
}();

} // namespace fcarouge::test::push_rvalue
