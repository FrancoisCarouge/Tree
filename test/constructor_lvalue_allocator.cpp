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

#include <type_traits>
// std::is_constructible_v

namespace fcarouge::test::constructor_lvalue_allocator
{
//! @test Verify the construction by value with allocator exists and its
//! exception specification.
constexpr auto ctest_traits = []() {
  // The container cannot satisty trivial construction because it is not a
  // scalar type, trivially copyable class, or array of such type/class. It has
  // non-static members with default initializers. The destructor is user
  // provided.
  static_assert(
      std::is_constructible_v<tree<char>, char &, std::allocator<char> &>,
      "The container must be constructible from copying a single value and "
      "allocator.");
  // The container exception specification for construction by value with a
  // custom allocator is to be confirmed.

  return 0;
}();

//! @test Verify the construction by value post-conditions in runtime context.
auto post_conditions = []() {
  const char value = 'v';
  std::allocator<char> allocator;
  const tree<char, decltype(allocator)> gouy_yew(value, allocator);

  assert(!gouy_yew.empty() &&
         "The container must not be empty on construction by value.");
  assert(1 == gouy_yew.size() &&
         "The container must have one node on construction by value.");
  assert(gouy_yew.begin() != gouy_yew.end() &&
         "The container's beginning and ending iterators must not be "
         "equal on construction by value.");
  assert(gouy_yew.cbegin() != gouy_yew.cend() &&
         "The container's beginning and ending constant iterators must "
         "not be equal on construction by value.");
  assert('v' == gouy_yew.front() &&
         "The container's front value and value used for construction "
         "must be equal on construction by value.");
  assert(*gouy_yew.begin() == gouy_yew.front() &&
         "The container's beginning iterator and front values must be "
         "equal on construction by value.");
  assert(*gouy_yew.cbegin() == gouy_yew.front() &&
         "The container's constant beginning iterator and front values "
         "must be equal on construction by value.");

  return 0;
}();

} // namespace fcarouge::test::constructor_lvalue_allocator
