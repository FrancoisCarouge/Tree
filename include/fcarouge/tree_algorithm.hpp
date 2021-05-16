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
//! @brief Tree algorithms header.
//!
//! @details The header contains the non-member algorithms defined and
//! applicable to the tree container.

#ifndef FCAROUGE_TREE_ALGORITHM_HPP
#define FCAROUGE_TREE_ALGORITHM_HPP

#include <iterator>
// std::iterator_traits

#include "tree_iterator_fwd.hpp"

//! @namespace fcarouge Francois Carouge's projects namespace. Lowers the name
//! conflict probability in large projects. Use using-declarations or
//! namespace-alias-definition per your project guidelines.
namespace fcarouge
{
//! @name Observing Operations
//! @{

//! @brief Depth of the path from the root, top element to the iterated node.
//!
//! @details Returns the number of nodes from the root, or top node, to the
//! currently iterated node, i.e. the current depth of the hierarchy. The root
//! node has depth of `0`, its children have depth `1`, etc... The behavior is
//! undefined if `*this` is the end iterator.
//!
//! @param position The iterator to the element for which to obtain the depth.
//! The iterator may be the beginning `begin()` or ending `end()` iterator.
//!
//! @return Current depth of the iterator.
//!
//! @complexity Linear in depth that is, at worst linear in size of the other
//! container.
[[nodiscard]] constexpr auto depth(TreeIterator auto position) ->
    typename std::iterator_traits<decltype(position)>::difference_type
{
  auto depth = 0;
  const auto *ancestor = position.node;
  while ((ancestor = ancestor->parent)) {
    ++depth;
  }

  return depth;
}

//! @}
} // namespace fcarouge

#endif // FCAROUGE_TREE_ALGORITHM_HPP
