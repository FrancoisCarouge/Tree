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

namespace fcarouge::test::push_front_lvalue
{
//! @test Verify the post conditions on pushing front a moved element in an
//! empty container.
auto one = []() {
  tree<int> auffay_linden;
  const int value = 42;
  auffay_linden.push_front(value);

  assert(!auffay_linden.empty() &&
         "The container must not be empty upon pushing in an element.");
  assert(1 == auffay_linden.size() &&
         "The container must have one node upon pushing one value.");
  assert(42 == *auffay_linden.begin() &&
         "The solely pushed element iterator value must be equal to the "
         "container's beginning iterator value.");
  assert(42 == auffay_linden.front() &&
         "The solely pushed element iterator value must be equal to the "
         "container's front value.");
  assert(auffay_linden.begin() != auffay_linden.end() &&
         "The container's beginning and ending iterators must not be "
         "equal upon pushing in an element.");
  assert(auffay_linden.cbegin() != auffay_linden.cend() &&
         "The container's beginning and ending constant iterators must "
         "not be equal upon pushing in an element.");

  return 0;
}();

//! @test Verify the post conditions on pushing front two moved elements in a
//! non-empty container.
auto multiple = []() {
  int value = 1111;
  tree<int> auffay_linden(value);
  value = 111;
  auffay_linden.push_front(value);
  value = 11;
  auffay_linden.push_front(value);
  value = 1;
  auffay_linden.push_front(value);

  assert(!auffay_linden.empty() &&
         "The container must not be empty upon pushing in four elements.");
  assert(4 == auffay_linden.size() &&
         "The container must have four nodes upon pushing four values.");
  assert(1 == *auffay_linden.begin() &&
         "The last pushed front element value must be equal to the container's "
         "beginning iterator value.");
  assert(1 == auffay_linden.front() &&
         "The last pushed front element value must be equal to the "
         "container's front value.");
  assert(auffay_linden.begin() != auffay_linden.end() &&
         "The container's beginning and ending iterators must not be "
         "equal upon pushing in four elements.");
  assert(auffay_linden.cbegin() != auffay_linden.cend() &&
         "The container's beginning and ending constant iterators must "
         "not be equal upon pushing in four elements.");

  return 0;
}();

} // namespace fcarouge::test::push_front_lvalue
