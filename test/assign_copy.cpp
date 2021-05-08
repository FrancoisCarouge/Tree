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

namespace
{
//! @test Verify copy assigning an empty tree to an empty tree.
[[maybe_unused]] auto empty = []() {
  fcarouge::tree<int> auffay_linden;
  fcarouge::tree<int> bunodiere_beech;
  bunodiere_beech.assign(auffay_linden);

  assert(0 == bunodiere_beech.size() &&
         "The container must contain zero node.");
  assert(bunodiere_beech.empty() && "The container must be empty.");
  assert(bunodiere_beech.begin() == bunodiere_beech.end() &&
         "The container's beginning and ending iterators must be equal.");
  assert(bunodiere_beech.cbegin() == bunodiere_beech.cend() &&
         "The container's beginning and ending constant container iterators "
         "must be equal.");

  return 0;
}();

//! @test Verify copy assigning a one element to a one element tree.
[[maybe_unused]] auto one = []() {
  fcarouge::tree<int> auffay_linden(42);
  fcarouge::tree<int> bunodiere_beech(24);
  bunodiere_beech.assign(auffay_linden);

  assert(1 == bunodiere_beech.size() && "The container must contain one node.");
  assert(!bunodiere_beech.empty() && "The container must not be empty.");
  assert(42 == bunodiere_beech.front() &&
         "The container's front value and value used for construction "
         "must be equal on copy assignment.");

  return 0;
}();

//! @test Verify copy assigning a complex tree to a complex tree with identical
//! topology.
[[maybe_unused]] auto all_replace_all = []() {
  fcarouge::tree<int> auffay_linden(42);
  auffay_linden.push(auffay_linden.begin(), 420);
  auffay_linden.push(auffay_linden.begin(), 421);
  auffay_linden.push(auffay_linden.begin(), 422);
  fcarouge::tree<int> bunodiere_beech(24);
  bunodiere_beech.push(bunodiere_beech.begin(), 240);
  bunodiere_beech.push(bunodiere_beech.begin(), 241);
  bunodiere_beech.push(bunodiere_beech.begin(), 242);
  bunodiere_beech.assign(auffay_linden);

  assert(!bunodiere_beech.empty() && "The container must not be empty.");
  assert(4 == bunodiere_beech.size() &&
         "The container must contain four nodes.");
  assert(42 == bunodiere_beech.front() &&
         "The container's front value and value used for construction "
         "must be equal on copy assignment.");

  return 0;
}();

//! @test Verify copy assigning a complex tree to an empty tree.
[[maybe_unused]] auto none_replace_all = []() {
  fcarouge::tree<int> auffay_linden(42);
  auffay_linden.push(auffay_linden.begin(), 420);
  auffay_linden.push(auffay_linden.begin(), 421);
  auffay_linden.push(auffay_linden.begin(), 422);
  fcarouge::tree<int> bunodiere_beech;
  bunodiere_beech.assign(auffay_linden);

  assert(!bunodiere_beech.empty() && "The container must not be empty.");
  assert(4 == bunodiere_beech.size() &&
         "The container must contain four nodes.");
  assert(42 == bunodiere_beech.front() &&
         "The container's front value and value used for construction "
         "must be equal on copy assignment.");

  return 0;
}();

//! @test Verify copy assigning an empty tree to a complex tree.
[[maybe_unused]] auto all_replace_none = []() {
  fcarouge::tree<int> auffay_linden;
  fcarouge::tree<int> bunodiere_beech(24);
  bunodiere_beech.push(bunodiere_beech.begin(), 240);
  bunodiere_beech.push(bunodiere_beech.begin(), 241);
  bunodiere_beech.push(bunodiere_beech.begin(), 242);
  bunodiere_beech.assign(auffay_linden);

  assert(0 == bunodiere_beech.size() &&
         "The container must contain zero node.");
  assert(bunodiere_beech.empty() && "The container must be empty.");
  assert(bunodiere_beech.begin() == bunodiere_beech.end() &&
         "The container's beginning and ending iterators must be equal.");
  assert(bunodiere_beech.cbegin() == bunodiere_beech.cend() &&
         "The container's beginning and ending constant container iterators "
         "must be equal.");

  return 0;
}();

//! @test Verify self copy assigning.
[[maybe_unused]] auto self = []() {
  fcarouge::tree<int> bunodiere_beech(42);
  bunodiere_beech.push(bunodiere_beech.begin(), 420);
  bunodiere_beech.push(bunodiere_beech.begin(), 421);
  bunodiere_beech.push(bunodiere_beech.begin(), 422);
  bunodiere_beech.assign(bunodiere_beech);

  assert(!bunodiere_beech.empty() && "The container must not be empty.");
  assert(4 == bunodiere_beech.size() &&
         "The container must contain four nodes.");
  assert(42 == bunodiere_beech.front() &&
         "The container's front value and value used for construction "
         "must be equal on copy assignment.");

  return 0;
}();

} // namespace
