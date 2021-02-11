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

namespace
{
//! @test Verify the post-conditions on constructing and populating a container
//! with a standard allocator.
[[maybe_unused]] auto construction = []() {
  std::allocator<int> allocator;
  fcarouge::tree<int, decltype(allocator)> allouville_oak(allocator);
  fcarouge::tree<int, decltype(allocator)>::iterator node3 =
      allouville_oak.emplace(allouville_oak.begin(), 3);
  allouville_oak.emplace(allouville_oak.begin(), 0);
  allouville_oak.emplace(node3, 1);
  allouville_oak.emplace(node3, 2);
  allouville_oak.emplace(allouville_oak.end(), 4);

  assert(!allouville_oak.empty() &&
         "The container must not be empty on this construction with an "
         "allocator and elements.");
  assert(5 == allouville_oak.size() &&
         "The container must have five elements on this construction with an "
         "allocator and elements.");

  return 0;
}();

} // namespace
