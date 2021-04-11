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
//! @test Verify the post conditions on emplacing front an element in an emptry
//! tree.
[[maybe_unused]] auto empty_front = []() {
  fcarouge::tree<int> allouville_oak;
  const int value = allouville_oak.emplace_front(42);

  assert(1 == allouville_oak.size() &&
         "The container must contain one element as built.");
  assert(
      42 == value &&
      "The container's beginning iterator value must be equal to the expected "
      "root node value.");
  assert(
      value == *allouville_oak.begin() &&
      "The container's beginning iterator value must be equal to the expected "
      "root node value.");
  assert(value == *allouville_oak.cbegin() &&
         "The container's constant beginning iterator value must be equal to "
         "the expected root node value.");
  assert(value == allouville_oak.front() &&
         "The container's front node value must be equal to the expected root "
         "node value.");

  return 0;
}();

//! @test Verify the post conditions on emplacing front an element in an
//! non-empty tree.
[[maybe_unused]] auto root_front = []() {
  fcarouge::tree<int> allouville_oak(42);
  const int value = allouville_oak.emplace_front(41);
  allouville_oak.emplace_front(40);

  assert(3 == allouville_oak.size() &&
         "The container must contain three elements as built.");
  assert(41 == value &&
         "The returned emplaced value must be equal to the expected value.");

  const std::multiset<int> expected_content{ 40, 41, 42 };
  const std::multiset<int> content(allouville_oak.begin(),
                                   allouville_oak.end());

  assert(expected_content == content &&
         "The container's content must meet expected content.");

  return 0;
}();

} // namespace
