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

#include <type_traits>
// std::is_default_constructible_v std::is_nothrow_default_constructible_v

namespace fcarouge::test::constructor_default
{
//! @test Validate the default construction exists and its exception
//! specification.
constexpr auto ctest_traits = []() {
  static_assert(
      std::is_default_constructible_v<tree<char>>,
      "The container must satisfy the DefaultConstructible requirement.");

  static_assert(
      std::is_nothrow_default_constructible_v<tree<char>>,
      "The container must satisfy the non-throwing "
      "DefaultConstructible requirement with the default standard allocator.");

  return 0;
}();

//! @test Validate the default construction post-conditions in constexpr
//! context.
constexpr auto ctest_post_conditions = []() {
  constexpr tree<char> allouville_oak;

  static_assert(allouville_oak.empty(),
                "The container must be empty on default construction.");
  static_assert(0 == allouville_oak.size(),
                "The container must have zero node on default construction.");
  static_assert(
      allouville_oak.begin() == allouville_oak.end(),
      "The container's beginning and ending iterators must be equal on "
      "default construction.");
  static_assert(
      allouville_oak.cbegin() == allouville_oak.cend(),
      "The container's beginning and ending constant iterators must be "
      "equal on default construction.");

  return 0;
}();

//! @test Validate the default construction post-conditions in runtime context.
auto test_post_conditions = []() {
  tree<char> gouy_yew;

  assert(gouy_yew.empty() &&
         "The container must be empty on default construction.");
  assert(0 == gouy_yew.size() &&
         "The container must have zero node on default construction.");
  assert(gouy_yew.begin() == gouy_yew.end() &&
         "The container's beginning and ending iterators must be equal on "
         "default construction.");
  assert(gouy_yew.cbegin() == gouy_yew.cend() &&
         "The container's beginning and ending constant iterators must be "
         "equal on "
         "default construction.");

  return 0;
}();

} // namespace fcarouge::test::constructor_default
