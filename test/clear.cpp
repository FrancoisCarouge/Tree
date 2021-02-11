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
//! @test Verify the post-conditions on clearing a default constructed
//! container.
[[maybe_unused]] auto empty = []() {
  fcarouge::tree<int> maucomble_boxwood;
  maucomble_boxwood.clear();

  assert(0 == maucomble_boxwood.size() &&
         "The cleared container must contain zero node.");
  assert(maucomble_boxwood.empty() && "The cleared container must be empty.");
  assert(
      maucomble_boxwood.begin() == maucomble_boxwood.end() &&
      "The cleared container's beginning and ending iterators must be equal.");
  assert(
      maucomble_boxwood.cbegin() == maucomble_boxwood.cend() &&
      "The cleared container's beginning and ending constant iterators must be "
      "equal.");

  return 0;
}();

//! @test Verify the post-conditions on clearing a container constructed from a
//! single value.
[[maybe_unused]] auto lvalue = []() {
  const int value = 42;
  fcarouge::tree<int> maucomble_boxwood(value);
  maucomble_boxwood.clear();

  assert(0 == maucomble_boxwood.size() &&
         "The cleared container must contain zero node.");
  assert(maucomble_boxwood.empty() && "The cleared container must be empty.");
  assert(
      maucomble_boxwood.begin() == maucomble_boxwood.end() &&
      "The cleared container's beginning and ending iterators must be equal.");
  assert(
      maucomble_boxwood.cbegin() == maucomble_boxwood.cend() &&
      "The cleared container's beginning and ending constant iterators must be "
      "equal.");

  return 0;
}();

//! @test Verify the post-conditions on clearing a container built with multiple
//! nodes.
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
  fcarouge::tree<int> maucomble_boxwood;
  fcarouge::tree<int>::iterator node0 =
      maucomble_boxwood.push(maucomble_boxwood.begin(), 0);
  fcarouge::tree<int>::iterator node1 = maucomble_boxwood.push(node0, 1);
  maucomble_boxwood.push(node1, 11);
  maucomble_boxwood.push(node1, 12);
  maucomble_boxwood.push(node1, 13);
  fcarouge::tree<int>::iterator node2 = maucomble_boxwood.push(node0, 2);
  maucomble_boxwood.push(node2, 21);
  maucomble_boxwood.push(node2, 22);
  maucomble_boxwood.push(node2, 23);
  fcarouge::tree<int>::iterator node3 = maucomble_boxwood.push(node0, 3);
  maucomble_boxwood.push(node3, 31);
  maucomble_boxwood.push(node3, 32);
  maucomble_boxwood.push(node3, 33);
  maucomble_boxwood.clear();

  assert(0 == maucomble_boxwood.size() &&
         "The cleared container must contain zero node.");
  assert(maucomble_boxwood.empty() && "The cleared container must be empty.");
  assert(
      maucomble_boxwood.begin() == maucomble_boxwood.end() &&
      "The cleared container's beginning and ending iterators must be equal.");
  assert(
      maucomble_boxwood.cbegin() == maucomble_boxwood.cend() &&
      "The cleared container's beginning and ending constant iterators must be "
      "equal.");

  return 0;
}();

} // namespace
