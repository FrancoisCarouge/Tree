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

#include "null_allocator.hpp"
// fcarouge::null_allocator

#include <cassert>
// assert

#include <limits>
// std::numeric_limits

#include <memory>
// std::allocator std::allocator_traits

namespace fcarouge::test::max_size
{
//! @test Verify the maximum number of elements the container is able to hold
//! with the standard allocator in constexpr context.
constexpr auto ctest_default = []() {
  constexpr tree<int> allouville_oak;

  static_assert(
      std::numeric_limits<decltype(allouville_oak)::difference_type>::max() >=
          allouville_oak.max_size(),
      "The container cannot support more elements than the absolute "
      "distance between the beginning and end iterators for the "
      "largest container with the standard default allocator.");

  static_assert(
      std::allocator_traits<decltype(allouville_oak.get_allocator())>::max_size(
          allouville_oak.get_allocator()) >= allouville_oak.max_size(),
      "The container cannot support more elements than the maximum "
      "number of element nodes, containing values and bookeeping "
      "support, theoretically allocated.");

  static_assert(0 < allouville_oak.max_size(),
                "The container must support some elements with the standard "
                "default allocator.");

  return 0;
}();

//! @test Verify the maximum number of elements the container is able to hold
//! with the standard allocator.
auto test_default = []() {
  const tree<int> allouville_oak;

  assert(
      std::numeric_limits<decltype(allouville_oak)::difference_type>::max() >=
          allouville_oak.max_size() &&
      "The container cannot support more elements than the absolute "
      "distance between the beginning and end iterators for the "
      "largest container with the standard default allocator.");

  assert(
      std::allocator_traits<decltype(allouville_oak.get_allocator())>::max_size(
          allouville_oak.get_allocator()) >= allouville_oak.max_size() &&
      "The container cannot support more elements than the maximum "
      "number of element nodes, containing values and bookeeping "
      "support, theoretically allocated.");

  assert(0 < allouville_oak.max_size() &&
         "The container must support some elements with the standard default "
         "allocator.");

  return 0;
}();

//! @test Verify the maximum number of elements the container is able to hold
//! with a null allocator in constexpr context.
constexpr auto ctest_null = []() {
  constexpr tree<int, null_allocator<int>> allouville_oak;

  static_assert(0 == allouville_oak.max_size(),
                "The cannot cannot support any element when used with an "
                "allocator with null capacity.");

  return 0;
}();

//! @test Verify the maximum number of elements the container is able to hold
//! with a null allocator.
auto test_constructor_null = []() {
  const tree<int, null_allocator<int>> allouville_oak;

  assert(0 == allouville_oak.max_size() &&
         "The cannot cannot support any element when used with an allocator "
         "with null capacity.");

  return 0;
}();

} // namespace fcarouge::test::max_size
