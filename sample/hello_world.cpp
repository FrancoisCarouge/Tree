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

#include <iostream>
// std::cout std::endl

namespace
{
//! @brief Traditional hello world demonstration.
//!
//! @details Simplified introduction container example.
//!
//! @dot
//! digraph "hello" {
//!   node [shape=circle fontsize="10"];
//!   "Hello" -> {",", "World", "!"}
//! }
//! @enddot
[[maybe_unused]] auto simple = []() {
  // Declare a "greeting" variable as a tree of aliased standard strings.
  fcarouge::tree_string greeting;

  // Push at the front of the tree a root element with string value "Hello".
  const auto root = greeting.emplace(greeting.begin(), "Hello");

  // Push in an element with value "," as a child of the sole node.
  greeting.push(root, ",");

  // Push in another element with value "!" and keep its iterator "bang".
  const auto bang = greeting.push(root, "!");

  // Insert a left sibling of iterator "bang" with value "World".
  greeting.emplace(bang, "World");

  // Print out the contents of the container.
  std::cout << greeting << std::endl;

  return 0;
}();

} // namespace
