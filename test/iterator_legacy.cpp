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
// std::is_copy_assignable_v std::is_copy_constructible_v std::is_destructible_v
// std::is_integral_v std::is_member_function_pointer_v
// std::is_move_assignable_v std::is_move_constructible_v
// std::is_nothrow_copy_assignable_v std::is_nothrow_copy_constructible_v
// std::is_nothrow_destructible_v std::is_nothrow_move_assignable_v
// std::is_nothrow_move_constructible_v std::is_nothrow_swappable_v
// std::is_same_v std::is_signed_v std::is_swappable_v
// std::is_trivially_copy_assignable_v std::is_trivially_copy_constructible_v
// std::is_trivially_destructible_v std::is_trivially_move_assignable_v
// std::is_trivially_move_constructible_v

namespace fcarouge::test::iterator_legacy
{
//! @test Verify the iterator meets the LegacyIterator requirements.
constexpr auto ctest_traits = []() {
  static_assert(
      std::is_move_constructible_v<tree<char>::iterator>,
      "The container iterator type member must satisfy the LegacyIterator "
      "requirement. The LegacyIterator requirement must satisfy the "
      "CopyConstructible requirement. The CopyConstructible requirement must "
      "satisfy the MoveConstructible requirement.");
  static_assert(
      std::is_trivially_move_constructible_v<tree<char>::iterator>,
      "The container iterator type member must satisfy the LegacyIterator "
      "requirement. The LegacyIterator requirement must satisfy the "
      "CopyConstructible requirement. The CopyConstructible requirement must "
      "satisfy the MoveConstructible requirement.");
  static_assert(
      std::is_nothrow_move_constructible_v<tree<char>::iterator>,
      "The container iterator type member must satisfy the LegacyIterator "
      "requirement. The LegacyIterator requirement must satisfy the "
      "CopyConstructible requirement. The CopyConstructible requirement must "
      "satisfy the MoveConstructible requirement.");
  static_assert(std::is_copy_constructible_v<tree<char>::iterator>,
                "The container iterator type member must satisfy the "
                "LegacyIterator requirement. The LegacyIterator requirement "
                "must satisfy the CopyConstructible requirement.");
  static_assert(std::is_trivially_copy_constructible_v<tree<char>::iterator>,
                "The container iterator type member must satisfy the "
                "LegacyIterator requirement. The LegacyIterator requirement "
                "must satisfy the CopyConstructible requirement.");
  static_assert(std::is_nothrow_copy_constructible_v<tree<char>::iterator>,
                "The container iterator type member must satisfy the "
                "LegacyIterator requirement. The LegacyIterator requirement "
                "must satisfy the CopyConstructible requirement.");
  static_assert(
      std::is_move_assignable_v<tree<char>::iterator>,
      "The container iterator type member must satisfy the LegacyIterator "
      "requirement. The LegacyIterator requirement must satisfy the "
      "CopyAssignable requirement. The CopyAssignable requirement must satisfy "
      "the MoveAssignable requirement.");
  static_assert(
      std::is_trivially_move_assignable_v<tree<char>::iterator>,
      "The container iterator type member must satisfy the LegacyIterator "
      "requirement. The LegacyIterator requirement must satisfy the "
      "CopyAssignable requirement. The CopyAssignable requirement must satisfy "
      "the MoveAssignable requirement.");
  static_assert(
      std::is_nothrow_move_assignable_v<tree<char>::iterator>,
      "The container iterator type member must satisfy the LegacyIterator "
      "requirement. The LegacyIterator requirement must satisfy the "
      "CopyAssignable requirement. The CopyAssignable requirement must satisfy "
      "the MoveAssignable requirement.");
  static_assert(std::is_copy_assignable_v<tree<char>::iterator>,
                "The container iterator type member must satisfy the "
                "LegacyIterator requirement. The LegacyIterator requirement "
                "must satisfy the CopyAssignable requirement.");
  static_assert(std::is_trivially_copy_assignable_v<tree<char>::iterator>,
                "The container iterator type member must satisfy the "
                "LegacyIterator requirement. The LegacyIterator requirement "
                "must satisfy the CopyAssignable requirement.");
  static_assert(std::is_nothrow_copy_assignable_v<tree<char>::iterator>,
                "The container iterator type member must satisfy the "
                "LegacyIterator requirement. The LegacyIterator requirement "
                "must satisfy the CopyAssignable requirement.");
  static_assert(std::is_destructible_v<tree<char>::iterator>,
                "The container iterator type member must satisfy the "
                "LegacyIterator requirement. The LegacyIterator requirement "
                "must satisfy the Destructible requirement.");
  static_assert(std::is_trivially_destructible_v<tree<char>::iterator>,
                "The container iterator type member must satisfy the "
                "LegacyIterator requirement. The LegacyIterator requirement "
                "must satisfy the Destructible requirement.");
  static_assert(std::is_nothrow_destructible_v<tree<char>::iterator>,
                "The container iterator type member must satisfy the "
                "LegacyIterator requirement. The LegacyIterator requirement "
                "must satisfy the Destructible requirement.");
  static_assert(std::is_swappable_v<tree<char>::iterator>,
                "The container iterator type member must satisfy the "
                "LegacyIterator requirement. The LegacyIterator requirement "
                "must satisfy the Swappable requirement.");
  static_assert(std::is_nothrow_swappable_v<tree<char>::iterator>,
                "The container iterator type member must satisfy the "
                "LegacyIterator requirement. The LegacyIterator requirement "
                "must satisfy the Swappable requirement.");
  static_assert(std::is_same_v<char, tree<char>::iterator::value_type>,
                "The container iterator type member must satisfy the "
                "LegacyIterator requirement. The LegacyIterator requirement "
                "has member typedef `value_type`.");
  static_assert(std::is_integral_v<tree<char>::iterator::difference_type>,
                "The container iterator type member must satisfy the "
                "LegacyIterator requirement. The LegacyIterator requirement "
                "has member typedef `difference_type`. The difference type "
                "member must be of integral type.");
  static_assert(
      std::is_signed_v<tree<char>::iterator::difference_type>,
      "The container iterator type member must satisfy the LegacyIterator "
      "requirement. The LegacyIterator requirement has member typedef "
      "`difference_type`. The difference type member must be of signed type.");
  static_assert(std::is_same_v<tree<char>::difference_type,
                               tree<char>::iterator::difference_type>,
                "The container iterator difference type member must be the "
                "same as the container difference type.");
  static_assert(std::is_same_v<char &, tree<char>::iterator::reference>,
                "The container iterator type member must satisfy the "
                "LegacyIterator requirement. The LegacyIterator requirement "
                "has member typedef `reference`.");
  static_assert(std::is_same_v<char *, tree<char>::iterator::pointer>,
                "The container iterator type member must satisfy the "
                "LegacyIterator requirement. The LegacyIterator requirement "
                "has member typedef `pointer`.");
  static_assert(std::is_same_v<std::input_iterator_tag,
                               tree<char>::iterator::iterator_category>,
                "The container iterator type member must satisfy the "
                "LegacyIterator requirement. The LegacyIterator requirement "
                "has member typedefs `iterator_category`.");
  static_assert(
      std::is_member_function_pointer_v<decltype(
          &tree<char>::iterator::operator*)>,
      "The container iterator type member must satisfy the LegacyIterator "
      "requirement. The LegacyIterator requirement lvalue is dereferenceable.");
  static_assert(
      std::is_member_function_pointer_v<decltype(
          &tree<char>::iterator::operator++)>,
      "The container iterator type member must satisfy the LegacyIterator "
      "requirement. The LegacyIterator requirement lvalue is incrementable.");

  return 0;
}();

//! @test Verify the post conditions of incrementing a valid beggining iterator
//! followed by a valid node.
auto increment = []() {
  tree<int> allouville_oak(42);
  allouville_oak.push(allouville_oak.begin(), 43);
  tree<int>::iterator iterator = ++allouville_oak.begin();

  assert(43 == *iterator && "The incremented beginning iterator's value must "
                            "be equal to the pushed element value.");

  ++iterator;

  assert(
      iterator == allouville_oak.end() &&
      "The incremented element iterator must be equal to the ending iterator.");
  assert(
      iterator == allouville_oak.cend() &&
      "The incremented element iterator must be equal to the ending constant "
      "iterator.");

  return 0;
}();

} // namespace fcarouge::test::iterator_legacy
