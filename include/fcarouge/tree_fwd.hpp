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
//! @brief Forward companion header for the tree container library types.
//!
//! @details The header forward declares the container types and includes its
//! minimum necessary standard library dependencies. Optionally use this header
//! when one or more of the library type declarations are required but not their
//! definitions. For instance, in project headers to help in reducing
//! dependencies and compilation times, while the container header would only be
//! used in the project sources.

#ifndef FCAROUGE_TREE_FWD_HPP
#define FCAROUGE_TREE_FWD_HPP

#include <cstdint>
// std::int_fast16_t std::int_fast32_t std::int_fast64_t std::int_fast8_t
// std::int_least16_t std::int_least32_t std::int_least64_t std::int_least8_t
// std::int16_t std::int32_t std::int64_t std::int8_t std::intmax_t
// std::intptr_t std::uint_fast16_t std::uint_fast32_t std::uint_fast64_t
// std::uint_fast8_t std::uint_least16_t std::uint_least32_t std::uint_least64_t
// std::uint_least8_t std::uint16_t std::uint32_t std::uint64_t std::uint8_t
// std::uintmax_t std::uintptr_t

#include <memory>
// std::allocator

#include <string>
// std::string std::u16string std::u32string std::u8string std::wstring

//! @namespace fcarouge Francois Carouge's projects namespace. Lowers the name
//! conflict probability in large projects. Use using-declarations or
//! namespace-alias-definition per your project guidelines.
namespace fcarouge
{
//! @name Forward Type Declarations
//! @{

template <typename Type, typename AllocatorType = std::allocator<Type>>
class tree;

//! @}

//! @name Type Aliases
//! @{

template <typename AllocatorType = std::allocator<bool>>
using tree_bool = tree<bool, AllocatorType>;
template <typename AllocatorType = std::allocator<char>>
using tree_char = tree<char, AllocatorType>;
template <typename AllocatorType = std::allocator<signed char>>
using tree_schar = tree<signed char, AllocatorType>;
template <typename AllocatorType = std::allocator<unsigned char>>
using tree_uchar = tree<unsigned char, AllocatorType>;
template <typename AllocatorType = std::allocator<int>>
using tree_int = tree<int, AllocatorType>;
template <typename AllocatorType = std::allocator<unsigned int>>
using tree_uint = tree<unsigned int, AllocatorType>;
template <typename AllocatorType = std::allocator<char8_t>>
using tree_char8_t = tree<char8_t, AllocatorType>;
template <typename AllocatorType = std::allocator<char16_t>>
using tree_char16_t = tree<char16_t, AllocatorType>;
template <typename AllocatorType = std::allocator<char32_t>>
using tree_char32_t = tree<char32_t, AllocatorType>;
template <typename AllocatorType = std::allocator<wchar_t>>
using tree_wchar_t = tree<wchar_t, AllocatorType>;
template <typename AllocatorType = std::allocator<std::int8_t>>
using tree_int8_t = tree<std::int8_t, AllocatorType>;
template <typename AllocatorType = std::allocator<std::uint8_t>>
using tree_uint8_t = tree<std::uint8_t, AllocatorType>;
template <typename AllocatorType = std::allocator<std::int16_t>>
using tree_int16_t = tree<std::int16_t, AllocatorType>;
template <typename AllocatorType = std::allocator<std::uint16_t>>
using tree_uint16_t = tree<std::uint16_t, AllocatorType>;
template <typename AllocatorType = std::allocator<std::int32_t>>
using tree_int32_t = tree<std::int32_t, AllocatorType>;
template <typename AllocatorType = std::allocator<std::uint32_t>>
using tree_uint32_t = tree<std::uint32_t, AllocatorType>;
template <typename AllocatorType = std::allocator<std::int64_t>>
using tree_int64_t = tree<std::int64_t, AllocatorType>;
template <typename AllocatorType = std::allocator<std::uint64_t>>
using tree_uint64_t = tree<std::uint64_t, AllocatorType>;
template <typename AllocatorType = std::allocator<std::int_least8_t>>
using tree_int_least8_t = tree<std::int_least8_t, AllocatorType>;
template <typename AllocatorType = std::allocator<std::uint_least8_t>>
using tree_uint_least8_t = tree<std::uint_least8_t, AllocatorType>;
template <typename AllocatorType = std::allocator<std::int_least16_t>>
using tree_int_least16_t = tree<std::int_least16_t, AllocatorType>;
template <typename AllocatorType = std::allocator<std::uint_least16_t>>
using tree_uint_least16_t = tree<std::uint_least16_t, AllocatorType>;
template <typename AllocatorType = std::allocator<std::int_least32_t>>
using tree_int_least32_t = tree<std::int_least32_t, AllocatorType>;
template <typename AllocatorType = std::allocator<std::uint_least32_t>>
using tree_uint_least32_t = tree<std::uint_least32_t, AllocatorType>;
template <typename AllocatorType = std::allocator<std::int_least64_t>>
using tree_int_least64_t = tree<std::int_least64_t, AllocatorType>;
template <typename AllocatorType = std::allocator<std::uint_least64_t>>
using tree_uint_least64_t = tree<std::uint_least64_t, AllocatorType>;
template <typename AllocatorType = std::allocator<std::int_fast8_t>>
using tree_int_fast8_t = tree<std::int_fast8_t, AllocatorType>;
template <typename AllocatorType = std::allocator<std::uint_fast8_t>>
using tree_uint_fast8_t = tree<std::uint_fast8_t, AllocatorType>;
template <typename AllocatorType = std::allocator<std::int_fast16_t>>
using tree_int_fast16_t = tree<std::int_fast16_t, AllocatorType>;
template <typename AllocatorType = std::allocator<std::uint_fast16_t>>
using tree_uint_fast16_t = tree<std::uint_fast16_t, AllocatorType>;
template <typename AllocatorType = std::allocator<std::int_fast32_t>>
using tree_int_fast32_t = tree<std::int_fast32_t, AllocatorType>;
template <typename AllocatorType = std::allocator<std::uint_fast32_t>>
using tree_uint_fast32_t = tree<std::uint_fast32_t, AllocatorType>;
template <typename AllocatorType = std::allocator<std::int_fast64_t>>
using tree_int_fast64_t = tree<std::int_fast64_t, AllocatorType>;
template <typename AllocatorType = std::allocator<std::uint_fast64_t>>
using tree_uint_fast64_t = tree<std::uint_fast64_t, AllocatorType>;
template <typename AllocatorType = std::allocator<std::intptr_t>>
using tree_intptr_t = tree<std::intptr_t, AllocatorType>;
template <typename AllocatorType = std::allocator<std::uintptr_t>>
using tree_uintptr_t = tree<std::uintptr_t, AllocatorType>;
template <typename AllocatorType = std::allocator<std::size_t>>
using tree_size_t = tree<std::size_t, AllocatorType>;
template <typename AllocatorType = std::allocator<std::ptrdiff_t>>
using tree_ptrdiff_t = tree<std::ptrdiff_t, AllocatorType>;
template <typename AllocatorType = std::allocator<std::intmax_t>>
using tree_intmax_t = tree<std::intmax_t, AllocatorType>;
template <typename AllocatorType = std::allocator<std::uintmax_t>>
using tree_uintmax_t = tree<std::uintmax_t, AllocatorType>;
template <typename AllocatorType = std::allocator<std::string>>
using tree_string = tree<std::string, AllocatorType>;
template <typename AllocatorType = std::allocator<std::u8string>>
using tree_u8string = tree<std::u8string, AllocatorType>;
template <typename AllocatorType = std::allocator<std::u16string>>
using tree_u16string = tree<std::u16string, AllocatorType>;
template <typename AllocatorType = std::allocator<std::u32string>>
using tree_u32string = tree<std::u32string, AllocatorType>;
template <typename AllocatorType = std::allocator<std::wstring>>
using tree_wstring = tree<std::wstring, AllocatorType>;

//! @}

} // namespace fcarouge

#endif // FCAROUGE_TREE_FWD_HPP
