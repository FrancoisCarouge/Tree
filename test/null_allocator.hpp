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

#ifndef FCAROUGE_NULL_ALLOCATOR_HPP
#define FCAROUGE_NULL_ALLOCATOR_HPP

#include <cstddef>
// std::size_t std::ptrdiff_t

#include <limits>
// std::numeric_limits

#include <memory>
// std::allocator std::allocator_traits std::pointer_traits

#include <new>
// std::bad_alloc

#include <type_traits>
// std::true_type

//! @namespace fcarouge Francois Carouge's projects namespace. Lowers the name
//! conflict probability in large projects. Use using-declarations or
//! namespace-alias-definition per your project guidelines.
namespace fcarouge
{
//! @brief Stateless perfectly fallible null allocator.
//!
//! @details The `fcarouge::null_allocator` does not yet satisfies allocator
//! completeness requirements. The allocator supports compile time evaluation of
//! its operations.
template <class Type> class null_allocator
{
  public:
  //! @name Public Member Types
  //! @{

  //! @brief The type of the allocated data elements.
  using value_type = Type;

  //! @brief The unsigned integer type to represent element counts.
  using size_type = std::size_t;

  //! @brief Signed integer type to represent element distances.
  using difference_type = std::ptrdiff_t;

  //! @brief Move-assignment will replace the allocator.
  using propagate_on_container_move_assignment = std::true_type;

  //! @}

  //! @name Public Member Functions
  //! @{

  //! @brief Constructs the allocator.
  //!
  //! @complexity Constant.
  //!
  //! @details Since the default allocator is stateless, the constructors have
  //! no visible effect.
  constexpr null_allocator() noexcept = default;

  //! @brief Constructs the allocator from another allocator and element type.
  //!
  //! @complexity Constant.
  //!
  //! @details Since the default allocator is stateless, the constructors have
  //! no visible effect.
  template <class OtherType>
  constexpr null_allocator(const null_allocator<OtherType> &other) noexcept
  {
  }

  //! @brief Allocates nothing, never.
  //!
  //! @param count The unused number of objects to allocate storage for.
  //!
  //! @details Always throws `std::bad_alloc`.
  //!
  //! @complexity Constant.
  //!
  //! @return Never returns the null pointer, not allocated.
  [[nodiscard]] constexpr Type *allocate(std::size_t count)
  {
    (void)count;
    std::bad_alloc no_memory;
    throw no_memory;
    return nullptr;
  }

  //! @brief Deallocates nothing, never.
  //!
  //! @complexity Constant.
  constexpr void deallocate(Type *, std::size_t)
  {
    return;
  }

  //! @}
};

} // namespace fcarouge

namespace std
{
//! @brief Null allocator specialization of the access to allocators properties.
//!
//! @details User-provided specialization of `std::allocator_traits` for the
//! `fcarouge::null_allocator` allocator.
template <class Type> struct allocator_traits<fcarouge::null_allocator<Type>> {
  public:
  //! @name Public Member Types
  //! @{

  //! @brief The type of the allocator for memory allocations.
  using allocator_type = fcarouge::null_allocator<Type>;

  //! @brief The type of the allocated data elements.
  using value_type = allocator_type::value_type;

  //! @brief The pointer type of the allocated data elements.
  using pointer = value_type *;

  //! @brief The constant pointer type of the allocated data elements.
  using const_pointer =
      typename std::pointer_traits<pointer>::rebind<const value_type>;

  //! @brief The unsigned integer type to represent element counts.
  using size_type = allocator_type::size_type;

  //! @brief The rebinded allocator type  for other element types.
  template <class OtherType>
  using rebind_alloc = fcarouge::null_allocator<OtherType>;

  //! @}

  //! @name Public Member Functions
  //! @{

  //! @brief Obtains the maximum theoretically possible allocation size.
  //!
  //! @param allocator The unused allocator to detect the maximum size of.
  //! Irrelevent since this allocator is stateless.
  //!
  //! @complexity Constant.
  //!
  //! @return Theoretical maximum allocation size, that is, exactly zero.
  static constexpr size_type max_size(const allocator_type &allocator) noexcept
  {
    (void)allocator;
    return 0;
  }

  //! @}
};
} // namespace std

#endif // FCAROUGE_NULL_ALLOCATOR_HPP
