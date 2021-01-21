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

#include <type_traits>
// std::is_destructible_v std::is_nothrow_destructible_v

namespace fcarouge::test::destructor
{
//! @test Verify the destruction exists and its exception specification.
constexpr auto ctest_traits = []() {
  // The container cannot satisty trivial destruction because it is not a
  // scalar type, trivially copyable class, or array of such type/class. It has
  // non-static members with default initializers. The destructor is user
  // provided.
  static_assert(std::is_destructible_v<tree<char>>,
                "The container must satisfy the Destructible requirement.");
  static_assert(
      std::is_nothrow_destructible_v<tree<char>>,
      "The container must satisfy the non-throwing Destructible requirement.");

  return 0;
}();

//! @test Verify the basic destruction post-conditions in constexpr context.
constexpr auto ctest_post_conditions = []() {
  constexpr tree<char> allouville_oak;

  return 0;
}();

//! @test Verify the basic destruction post-conditions in runtime context.
auto test_post_conditions = []() {
  const tree<char> gouy_yew;

  return 0;
}();

} // namespace fcarouge::test::destructor
