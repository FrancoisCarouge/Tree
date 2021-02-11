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
//! @test Verify the post-conditions on obtaining the allocator associated
//! with the container in constant expressions.
[[maybe_unused]] constexpr auto compile = []() {
  constexpr fcarouge::tree<int> allouville_oak;
  constexpr fcarouge::tree<int>::allocator_type allocator =
      allouville_oak.get_allocator();
  constexpr std::allocator<int> expected_allocator;

  static_assert(expected_allocator == allocator &&
                "The default container allocator must be equal to the standard "
                "allocator.");

  return 0;
}();

//! @test Verify the post-conditions on obtaining the allocator associated
//! with the container.
[[maybe_unused]] auto run = []() {
  const fcarouge::tree<int> allouville_oak;
  const fcarouge::tree<int>::allocator_type allocator =
      allouville_oak.get_allocator();
  const std::allocator<int> expected_allocator;

  assert(expected_allocator == allocator &&
         "The default container allocator must be equal to the standard "
         "allocator.");

  return 0;
}();

} // namespace
