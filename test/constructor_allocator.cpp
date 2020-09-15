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

namespace fcarouge::test::constructor_allocator
{
//! @test Verify the post-conditions on constructing and populating a container
//! with a standard allocator.
auto test_construction = []() {
  std::allocator<int> allocator;
  tree<int, decltype(allocator)> allouville_oak(allocator);
  tree<int, decltype(allocator)>::iterator n3 =
      allouville_oak.emplace(allouville_oak.begin(), 3);
  allouville_oak.emplace(allouville_oak.begin(), 0);
  allouville_oak.emplace(n3, 1);
  allouville_oak.emplace(n3, 2);
  allouville_oak.emplace(allouville_oak.end(), 4);

  assert(!allouville_oak.empty() &&
         "The container must not be empty on this construction with an "
         "allocator and elements.");
  assert(5 == allouville_oak.size() &&
         "The container must have five elements on this construction with an "
         "allocator and elements.");

  return 0;
}();

//! @test Verify the post-conditions on clearing a populated a container
//! with a standard allocator.
auto test_clearing = []() {
  std::allocator<int> allocator;
  tree<int, decltype(allocator)> allouville_oak(allocator);
  tree<int, decltype(allocator)>::iterator n3 =
      allouville_oak.emplace(allouville_oak.begin(), 3);
  allouville_oak.emplace(allouville_oak.begin(), 0);
  allouville_oak.emplace(n3, 1);
  allouville_oak.emplace(n3, 2);
  allouville_oak.emplace(allouville_oak.end(), 4);
  allouville_oak.clear();

  assert(0 == allouville_oak.size() &&
         "The cleared container must contain zero node.");
  assert(allouville_oak.empty() && "The cleared container must be empty.");
  assert(
      allouville_oak.begin() == allouville_oak.end() &&
      "The cleared container's beginning and ending iterators must be equal.");
  assert(
      allouville_oak.cbegin() == allouville_oak.cend() &&
      "The cleared container's beginning and ending constant iterators must be "
      "equal.");

  return 0;
}();

} // namespace fcarouge::test::constructor_allocator
