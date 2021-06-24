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
//! @brief Verify the equality operation on empty containers.
[[maybe_unused]] constexpr auto empty = []() {
  constexpr fcarouge::tree_int gouy_yew;
  constexpr fcarouge::tree_int auffay_linden;

  static_assert(gouy_yew == gouy_yew);
  static_assert(gouy_yew == auffay_linden);

  return 0;
}();

//! @brief Verify the equality operation on single element containers.
[[maybe_unused]] auto single_element = []() {
  fcarouge::tree_int gouy_yew(42);
  fcarouge::tree_int auffay_linden(42);
  fcarouge::tree_int bunodiere_beech(43);

  assert(gouy_yew == gouy_yew);
  assert(gouy_yew == auffay_linden);
  assert(gouy_yew != bunodiere_beech);

  return 0;
}();

//! @brief Verify the equality operation on non-trivial containers.
[[maybe_unused]] auto complex = []() {
  fcarouge::tree_int gouy_yew(0);
  gouy_yew.push(gouy_yew.push(gouy_yew.push(gouy_yew.begin(), 1), 11), 111);
  gouy_yew.push(gouy_yew.begin(), 2);
  gouy_yew.push(gouy_yew.begin(), 3);
  gouy_yew.push(gouy_yew.begin(), 4);
  const auto itg = gouy_yew.push(gouy_yew.begin(), 5);
  gouy_yew.emplace(gouy_yew.push(gouy_yew.push(itg, 51), 512), 511);
  gouy_yew.emplace(gouy_yew.push(gouy_yew.push(itg, 52), 522), 521);
  gouy_yew.emplace(gouy_yew.push(gouy_yew.push(itg, 53), 532), 531);
  fcarouge::tree_int auffay_linden(0);
  auffay_linden.push(
      auffay_linden.push(auffay_linden.push(auffay_linden.begin(), 1), 11),
      111);
  auffay_linden.push(auffay_linden.begin(), 2);
  auffay_linden.push(auffay_linden.begin(), 3);
  auffay_linden.push(auffay_linden.begin(), 4);
  const auto ita = auffay_linden.push(auffay_linden.begin(), 5);
  auffay_linden.emplace(auffay_linden.push(auffay_linden.push(ita, 51), 512),
                        511);
  auffay_linden.emplace(auffay_linden.push(auffay_linden.push(ita, 52), 522),
                        521);
  auffay_linden.emplace(auffay_linden.push(auffay_linden.push(ita, 53), 532),
                        531);
  fcarouge::tree_int bunodiere_beech(0);
  bunodiere_beech.push(
      bunodiere_beech.push(bunodiere_beech.push(bunodiere_beech.begin(), 1),
                           11),
      111);
  bunodiere_beech.push(bunodiere_beech.begin(), 2);
  bunodiere_beech.push(bunodiere_beech.begin(), 3);
  bunodiere_beech.push(bunodiere_beech.begin(), 4);
  const auto itb = bunodiere_beech.push(bunodiere_beech.begin(), 5);
  bunodiere_beech.emplace(
      bunodiere_beech.push(bunodiere_beech.push(itb, 51), 512), 511);
  bunodiere_beech.emplace(
      bunodiere_beech.push(bunodiere_beech.push(itb, 52), 522), 521);
  bunodiere_beech.emplace(
      bunodiere_beech.push(bunodiere_beech.push(itb, 53), 532), 530);

  assert(gouy_yew == gouy_yew);
  assert(gouy_yew == auffay_linden);
  assert(gouy_yew != bunodiere_beech);

  return 0;
}();

} // namespace
