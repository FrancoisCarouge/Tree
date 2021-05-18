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

//! @file
//! @brief Tree iterators header.
//!
//! @details The header contains the non-member iterators defined and
//! applicable to the tree container.

#ifndef FCAROUGE_TREE_ITERATOR_HPP
#define FCAROUGE_TREE_ITERATOR_HPP

#include <iterator>
// std::bidirectional_iterator_tag

#include <memory>
// std::pointer_traits

#include <type_traits>
// std::remove_pointer_t

#include "tree_iterator_fwd.hpp"

#include "tree_fwd.hpp"

//! @namespace fcarouge Francois Carouge's projects namespace. Lowers the name
//! conflict probability in large projects. Use using-declarations or
//! namespace-alias-definition per your project guidelines.
namespace fcarouge
{
//! @brief A pre-order depth-first tree traversal iterator.
//!
//! @details Type to identify and traverse the elements of the container. The
//! iteration order is specified as a pre-order depth-first traversal. Each
//! element is visited only once. The traversal is topologically sorted.
//! -# Current node data.
//! -# Traverse the left-most child node and data.
//! -# Traverse the next child node and data.
//!
//! @tparam Iterator The underlying tree member iterator type-constraint
//! template parameter providing constness and conversion support.
template <TreeMemberIterator Iterator>
struct depth_first_pre_order_iterator_type {
  //! @name Public Member Types
  //! @{

  //! @brief The type of the contained data elements.
  using value_type = typename Iterator::value_type;

  //! @brief Signed integer type to represent element distances.
  using difference_type = typename Iterator::difference_type;

  //! @brief The reference type of the contained data elements.
  using reference = typename Iterator::reference;

  //! @brief The pointer type of the contained data elements.
  using pointer = typename Iterator::pointer;

  //! @brief The LegacyBidirectionalIterator requirements category of the
  //! iterator.
  using iterator_category = std::bidirectional_iterator_tag;

  //! @}

  //! @name Public Observer Member Functions
  //! @{

  //! @brief Accesses the stored element data.
  //!
  //! @details Indirection operator. Dereferences the iterator to obtain the
  //! container's stored value. The behavior is undefined if the iterator is
  //! invalid.
  //!
  //! @return Reference to the element if the iterator is dereferencable.
  [[nodiscard]] constexpr reference operator*() const noexcept
  {
    return node->data;
  }

  //! @brief Points to the stored element.
  //!
  //! @details Member access operator. Dereferenceable pointer or pointer-like
  //! object of the container's stored value from this iterator. The behavior
  //! is undefined if the iterator is invalid.
  //!
  //! @return Pointer to the container's stored value iterator.
  [[nodiscard]] constexpr pointer operator->() const noexcept
  {
    return std::pointer_traits<pointer>::pointer_to(node->data);
  }

  //! @}

  //! @name Public Modifier Member Functions
  //! @{

  //! @brief Prefix increments the iterator.
  //!
  //! @return Reference to the next iterator.
  constexpr depth_first_pre_order_iterator_type &operator++() noexcept
  {
    if (node->first_child) {
      node = node->first_child;
    } else {
      node = node->next_ancestor_sibling();
    }

    return *this;
  }

  //! @brief Postfix increments the iterator.
  //!
  //! @return Next iterator.
  [[nodiscard]] constexpr depth_first_pre_order_iterator_type
  operator++(int) const noexcept
  {
    depth_first_pre_order_iterator_type temporary_iterator = *this;
    if (node->first_child) {
      node = node->first_child;
    } else {
      node = node->next_ancestor_sibling();
    }

    return temporary_iterator;
  }

  //! @brief Prefix decrements the iterator.
  //!
  //! @return Reference to the previous iterator.
  constexpr depth_first_pre_order_iterator_type &operator--() noexcept
  {
    if (node->left_sibling) {
      node = node->left_sibling;
    } else {
      node = node->parent;
    }

    return *this;
  }

  //! @brief Postfix decrements the iterator.
  //!
  //! @return Previous iterator.
  [[nodiscard]] constexpr depth_first_pre_order_iterator_type
  operator--(int) const noexcept
  {
    depth_first_pre_order_iterator_type temporary_iterator = *this;
    if (node->left_sibling) {
      node = node->left_sibling;
    } else {
      node = node->parent;
    }

    return temporary_iterator;
  }

  //! @}

  //! @name Public Conversion Function
  //! @{

  //! @brief Converts to tree non-constant container iterators.
  //!
  //! @details Allows conversion accross tree non-constant container
  //! iterators.
  //!
  //! @tparam OtherIterator The tree non-constant container iterator
  //! type-constraint template parameter to convert this iterator to.
  //!
  //! @return The converted tree non-constant container iterator.
  template <TreeIterator OtherIterator>
  operator OtherIterator() const &requires TreeNonConstIterator<Iterator>
  {
    return OtherIterator{ node };
  }

  //! @brief Converts to tree constant container iterators.
  //!
  //! @details Allows conversion to constant container iterators.
  //!
  //! @tparam OtherIterator The tree constant container iterator
  //! type-constraint template parameter to convert this iterator to.
  //!
  //! @return The converted tree constant container iterator.
  template <TreeConstIterator OtherIterator>
  operator OtherIterator() const &requires TreeConstIterator<Iterator>
  {
    return OtherIterator{ node };
  }

  //! @}

  //! @name Public Comparison Function
  //! @{

  //! @brief Compares the iterators.
  //!
  //! @details Checks if the iterators point to the same element.
  //!
  //! @param other The iterator to evaluate.
  //!
  //! @return `true` if the iterators point to the same element, `false`
  //! otherwise.
  //!
  //! @complexity Constant.
  [[nodiscard]] constexpr bool operator==(
      const depth_first_pre_order_iterator_type<Iterator> &other) const noexcept
  {
    return node == other.node;
  }

  //! @}

  //! @name Internal Implementation Member Types
  //! @{

  //! @brief The internal node data structure type containing the element data.
  using internal_node_type = std::remove_pointer_t<decltype(Iterator::node)>;

  //! @}

  //! @name Internal Implementation Member Variables
  //! @{

  //! @brief The internal pointer to the node represented by the iterator.
  internal_node_type *node = nullptr;

  //! @}
};

//! @name Deduction Guides
//! @{

depth_first_pre_order_iterator_type(TreeMemberIterator auto position)
    -> depth_first_pre_order_iterator_type<decltype(position)>;

//! @}
} // namespace fcarouge

//! @name Non-Member Functions
//! @{

//! @brief Compares the iterators.
//!
//! @details Checks if the iterators point to the same element.
//!
//! @param lhs The iterator to compare.
//! @param rhs The other iterator to compare.
//!
//! @return `true` if the iterators point to the same element, `false`
//! otherwise.
//!
//! @complexity Constant.
[[nodiscard]] constexpr bool operator==(const fcarouge::TreeIterator auto &lhs,
                                        const fcarouge::TreeIterator auto &rhs)
{
  return lhs.node == rhs.node;
}

//! @}

#endif // FCAROUGE_TREE_ITERATOR_HPP
