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
// fcarouge::tree::iterator fcarouge::tree::const_iterator

#include <type_traits>
// std::is_aggregate_v std::is_copy_constructible_v
// std::is_trivially_copy_constructible_v std::is_convertible_v

namespace
{
//! @test Verify basic traits for the container default `iterator` type.
[[maybe_unused]] constexpr auto traits = []() {
  static_assert(std::is_aggregate_v<fcarouge::tree<char>::iterator>,
                "The container's iterator type is an aggregate type by "
                "design choice.");
  static_assert(std::is_copy_constructible_v<fcarouge::tree<char>::iterator>,
                "The container's iterator type must be copy constructible.");
  static_assert(
      std::is_trivially_copy_constructible_v<fcarouge::tree<char>::iterator>,
      "The container's iterator type must be trivially copy constructible.");
  static_assert(
      std::is_convertible_v<fcarouge::tree<char>::iterator,
                            fcarouge::tree<char>::const_iterator>,
      "The container's iterator type must be implicitely convertible to its "
      "constant equivalent type.");
  static_assert(!std::is_convertible_v<fcarouge::tree<char>::const_iterator,
                                       fcarouge::tree<char>::iterator>,
                "The container's constant iterator type cannot be implicitely "
                "convertible to its non-constant equivalent type.");

  return 0;
}();

} // namespace
