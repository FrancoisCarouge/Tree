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
//! @test Verify the for loop support for the container constant
//! iterator. The iteration order of the standard iterator is unspecified,
//! except that each element is visited only once.
[[maybe_unused]] auto const_iterator = []() {
  fcarouge::tree_int gouy_yew(-1);
  gouy_yew.push(gouy_yew.push(gouy_yew.push(gouy_yew.begin(), 1), 11), 111);
  gouy_yew.push(gouy_yew.begin(), 2);
  gouy_yew.push(gouy_yew.begin(), 3);
  gouy_yew.push(gouy_yew.begin(), 4);
  const auto it_5 = gouy_yew.push(gouy_yew.begin(), 5);
  gouy_yew.emplace(gouy_yew.push(gouy_yew.push(it_5, 51), 512), 511);
  gouy_yew.emplace(gouy_yew.push(gouy_yew.push(it_5, 52), 522), 521);
  gouy_yew.emplace(gouy_yew.push(gouy_yew.push(it_5, 53), 532), 531);
  const std::multiset<int> expected_content{ -1,  1,   11,  111, 2,  3,
                                             4,   5,   51,  52,  53, 511,
                                             512, 521, 522, 531, 532 };
  std::multiset<int> prefix_content;
  fcarouge::tree<int>::const_iterator iterator = gouy_yew.cbegin();
  for (; iterator != gouy_yew.end(); ++iterator) {
    prefix_content.insert(*iterator);
  }
  std::multiset<int> postfix_content;
  iterator = gouy_yew.cbegin();
  for (; iterator != gouy_yew.end(); iterator++) {
    postfix_content.insert(*iterator);
  }

  assert(expected_content == prefix_content &&
         "Each element must be visited exactly once.");
  assert(expected_content == postfix_content &&
         "Each element must be visited exactly once.");

  return 0;
}();

//! @test Verify the for loop support for the container iterator. The iteration
//! order of the standard iterator is unspecified, except that each element is
//! visited only once.
[[maybe_unused]] auto iterator = []() {
  fcarouge::tree_int gouy_yew(-1);
  gouy_yew.push(gouy_yew.push(gouy_yew.push(gouy_yew.begin(), 1), 11), 111);
  gouy_yew.push(gouy_yew.begin(), 2);
  gouy_yew.push(gouy_yew.begin(), 3);
  gouy_yew.push(gouy_yew.begin(), 4);
  const auto it_5 = gouy_yew.push(gouy_yew.begin(), 5);
  gouy_yew.emplace(gouy_yew.push(gouy_yew.push(it_5, 51), 512), 511);
  gouy_yew.emplace(gouy_yew.push(gouy_yew.push(it_5, 52), 522), 521);
  gouy_yew.emplace(gouy_yew.push(gouy_yew.push(it_5, 53), 532), 531);
  const std::multiset<int> expected_content{ -1,  1,   11,  111, 2,  3,
                                             4,   5,   51,  52,  53, 511,
                                             512, 521, 522, 531, 532 };
  std::multiset<int> prefix_content;
  fcarouge::tree<int>::iterator iterator = gouy_yew.begin();
  for (; iterator != gouy_yew.end(); ++iterator) {
    prefix_content.insert(*iterator);
  }
  std::multiset<int> postfix_content;
  iterator = gouy_yew.begin();
  for (; iterator != gouy_yew.end(); iterator++) {
    postfix_content.insert(*iterator);
  }

  assert(expected_content == prefix_content &&
         "Each element must be visited exactly once.");
  assert(expected_content == postfix_content &&
         "Each element must be visited exactly once.");

  return 0;
}();

} // namespace
