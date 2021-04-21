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

#include <sstream>
// std::ostringstream

namespace
{
//! @brief Verify the human-interpretable representation of an empty tree
//! provided by the insertion operator.
[[maybe_unused]] auto empty = []() {
  fcarouge::tree_int gouy_yew;
  std::ostringstream oss;
  oss << gouy_yew;

  assert("" == oss.str() && "The human-interpretable representation of the "
                            "empty tree must match the required format.");

  return 0;
}();

//! @brief Verify the human-interpretable representation of a non-trivial tree
//! provided by the insertion operator.
[[maybe_unused]] auto complex = []() {
  fcarouge::tree_int gouy_yew(0);
  gouy_yew.push(gouy_yew.push(gouy_yew.push(gouy_yew.begin(), 1), 11), 111);
  gouy_yew.push(gouy_yew.begin(), 2);
  gouy_yew.push(gouy_yew.begin(), 3);
  gouy_yew.push(gouy_yew.begin(), 4);
  const auto it = gouy_yew.push(gouy_yew.begin(), 5);
  gouy_yew.emplace(gouy_yew.push(gouy_yew.push(it, 51), 512), 511);
  gouy_yew.emplace(gouy_yew.push(gouy_yew.push(it, 52), 522), 521);
  gouy_yew.emplace(gouy_yew.push(gouy_yew.push(it, 53), 532), 531);
  std::ostringstream oss;
  oss << gouy_yew;

  assert(
      R"(0
├── 1
│   └── 11
│       └── 111
├── 2
├── 3
├── 4
└── 5
    ├── 51
    │   ├── 511
    │   └── 512
    ├── 52
    │   ├── 521
    │   └── 522
    └── 53
        ├── 531
        └── 532
)" == oss.str() &&
      "The human-interpretable representation of the tree must match the "
      "required format.");

  gouy_yew.clear();
  oss.str("");
  oss.clear();
  oss << gouy_yew;

  assert("" == oss.str() && "The human-interpretable representation of the "
                            "cleared tree must match the required format.");

  return 0;
}();

} // namespace
