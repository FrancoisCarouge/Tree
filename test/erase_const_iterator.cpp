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
//! @test Verify the post-conditions on erasing the sole element of a container.
[[maybe_unused]] auto sole = []() {
  fcarouge::tree<int> allouville_oak(42);
  const fcarouge::tree<int>::const_iterator iterator =
      allouville_oak.erase(allouville_oak.begin());

  assert(allouville_oak.empty() && "The container must be empty on erasing the "
                                   "sole element of a container.");
  assert(0 == allouville_oak.size() &&
         "The container must have zero node on erasing the sole element of a "
         "container.");
  assert(allouville_oak.begin() == allouville_oak.end() &&
         "The container's beginning and ending iterators must be equal on "
         "erasing the sole element of a container.");
  assert(allouville_oak.cbegin() == allouville_oak.cend() &&
         "The container's beginning and ending constant iterators must be "
         "equal on erasing the sole element of a container.");
  assert(iterator == allouville_oak.cend() &&
         "The iterator following the erased element must be the constant "
         "ending iterator.");

  return 0;
}();

//! @test Verify the post-conditions on erasing the last element of a tree.
[[maybe_unused]] auto last = []() {
  fcarouge::tree<int> allouville_oak;
  const fcarouge::tree<int>::const_iterator node3 =
      allouville_oak.emplace(allouville_oak.begin(), 3);
  allouville_oak.emplace(allouville_oak.begin(), 0);
  allouville_oak.emplace(node3, 1);
  allouville_oak.emplace(node3, 2);
  const fcarouge::tree<int>::const_iterator iterator =
      allouville_oak.erase(node3);

  assert(
      !allouville_oak.empty() &&
      "The container must not be empty after erasing the last node of four.");
  assert(3 == allouville_oak.size() &&
         "The container must contain three nodes after erasing the last "
         "node of four.");
  assert(iterator == allouville_oak.cend() &&
         "The iterator following the erased last element must be the constant "
         "ending iterator.");

  return 0;
}();

//! @test Verify the post-conditions on erasing the root element of a tree.
[[maybe_unused]] auto root = []() {
  fcarouge::tree<int> allouville_oak;
  const fcarouge::tree<int>::const_iterator node3 =
      allouville_oak.emplace(allouville_oak.begin(), 3);
  const fcarouge::tree<int>::const_iterator root =
      allouville_oak.emplace(allouville_oak.begin(), 0);
  allouville_oak.emplace(node3, 1);
  allouville_oak.emplace(node3, 2);
  const fcarouge::tree<int>::const_iterator iterator =
      allouville_oak.erase(root);

  assert(allouville_oak.empty() &&
         "The container must be empty on erasing its root.");
  assert(0 == allouville_oak.size() &&
         "The container must contain zero node on erasing its root.");
  assert(allouville_oak.begin() == allouville_oak.end() &&
         "The container's beginning and ending iterators must be equal on "
         "erasing its root.");
  assert(allouville_oak.cbegin() == allouville_oak.cend() &&
         "The container's beginning and ending constant iterators must be "
         "equal on erasing its root.");
  assert(iterator == allouville_oak.cend() &&
         "The iterator following the erased last element must be the constant "
         "ending iterator.");

  return 0;
}();

//! @test Verify the post-conditions on erasing various elements of a tree.
[[maybe_unused]] auto multiple = []() {
  fcarouge::tree<int> allouville_oak;
  const fcarouge::tree<int>::const_iterator node33 =
      allouville_oak.emplace(allouville_oak.begin(), 33);
  const fcarouge::tree<int>::const_iterator node3 =
      allouville_oak.emplace(node33, 3);
  allouville_oak.emplace(allouville_oak.begin(), 0);
  allouville_oak.emplace(node3, 1);
  allouville_oak.emplace(node3, 2);
  const fcarouge::tree<int>::const_iterator node31 =
      allouville_oak.emplace(node33, 31);
  const fcarouge::tree<int>::const_iterator node32 =
      allouville_oak.emplace(node33, 32);
  fcarouge::tree<int>::const_iterator iterator = allouville_oak.erase(node32);

  assert(6 == allouville_oak.size() && "The container must contain six nodes.");
  assert(!allouville_oak.empty() && "The container must not be empty.");
  assert(node33 == iterator &&
         "The iterator following the erased element must be for node 33.");

  iterator = allouville_oak.erase(node31);

  assert(5 == allouville_oak.size() &&
         "The container must contain five nodes.");
  assert(!allouville_oak.empty() && "The container must not be empty.");
  assert(node33 == iterator &&
         "The iterator following the erased element must be for node 33.");

  iterator = allouville_oak.erase(node3);

  assert(3 == allouville_oak.size() &&
         "The container must contain three nodes.");
  assert(!allouville_oak.empty() && "The container must not be empty.");
  assert(allouville_oak.end() == iterator &&
         "The iterator following the erased element must be for node 33.");

  return 0;
}();

} // namespace
