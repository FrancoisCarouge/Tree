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
//! @brief Forward companion header for the tree container's iterator types.
//!
//! @details The header forward declares the container's iterator types and
//! includes its minimum necessary standard library dependencies. Optionally use
//! this header when one or more of the library iterator type declarations are
//! required but not their definitions. For instance, in project headers to help
//! in reducing dependencies and compilation times, while the iterator header
//! would only be used in the project sources.

#ifndef FCAROUGE_TREE_ITERATOR_FWD_HPP
#define FCAROUGE_TREE_ITERATOR_FWD_HPP

#include "tree_fwd.hpp"

//! @namespace fcarouge Francois Carouge's projects namespace. Lowers the name
//! conflict probability in large projects. Use using-declarations or
//! namespace-alias-definition per your project guidelines.
namespace fcarouge
{
//! @name Forward Type Declarations
//! @{

//! @}

//! @name Concepts
//! @{

//! @brief Tree constant container iterators concept.
//!
//! @details Supports cv-qualifiers and references.
//!
//! @tparam ConstIterator The type template parameter to check for tree constant
//! container iterator constaints.
template <typename ConstIterator>
concept TreeConstIterator = TreeMemberConstIterator<ConstIterator>;

//! @brief Tree non-constant container iterators concept.
//!
//! @details Supports cv-qualifiers and references.
//!
//! @tparam ConstIterator The type template parameter to check for tree
//! non-constant container iterator constaints.
template <typename NonConstIterator>
concept TreeNonConstIterator = TreeMemberNonConstIterator<NonConstIterator>;

//! @brief Tree iterators concept.
//!
//! @details All tree iterators are included. Supports cv-qualifiers and
//! references.
//!
//! @tparam Iterator The type template parameter to check for tree container
//! iterator constaints.
template <typename Iterator>
concept TreeIterator =
    TreeConstIterator<Iterator> || TreeNonConstIterator<Iterator> ||
    TreeMemberIterator<Iterator>;

//! @}
} // namespace fcarouge

#endif // FCAROUGE_TREE_ITERATOR_FWD_HPP
