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
// std::is_empty_v std::true_type

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

  //! @brief Constructs a null-allocator.
  //!
  //! @details Since the null-allocator is stateless, the constructors have
  //! no visible effect.
  //!
  //! @complexity Constant.
  constexpr null_allocator() noexcept = default;

  //! @brief Copy constructs the null-allocator.
  //!
  //! @details Copy constructor. Since the null-allocator is stateless, the
  //! constructors have no visible effect.
  //!
  //! @complexity Constant.
  constexpr null_allocator(const null_allocator &other) noexcept
  {
    (void)other;
  }

  //! @brief Constructs the allocator from another allocator and element type.
  //!
  //! @details Conversion constructor. Since the null-allocator is stateless,
  //! the constructors have no visible effect.
  //!
  //! @complexity Constant.
  template <class OtherType>
  constexpr explicit null_allocator(
      const null_allocator<OtherType> &other) noexcept
  {
    (void)other;
  }

  //! @brief Copy assignment operator.
  //!
  //! @details Self copy assignement is valid, safe, and meets specifications.
  //!
  //! @return The reference value of this implicit object container parameter,
  //! i.e. `*this`.
  //!
  //! @complexity Constant.
  constexpr null_allocator &operator=(const null_allocator &other) = default;

  //! @brief Destructs the allocator.
  //!
  //! @details Since the null-allocator is stateless, the destructor has
  //! no visible effect.
  //!
  //! @complexity Constant.
  constexpr ~null_allocator() = default;

  //! @brief Allocates nothing, never.
  //!
  //! @param count The unused number of objects to allocate storage for.
  //!
  //! @details Always throws `std::bad_alloc`.
  //!
  //! @return Never returns the null pointer, not allocated.
  //!
  //! @complexity Constant.
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

static_assert(std::is_empty_v<null_allocator<int>>,
              "The null-allocator must be an empty type, to be stateless that "
              "is, a non-union class type with no non-static data members "
              "other than bit-fields of size zero, no virtual functions, no "
              "virtual base classes, and no non-empty base classes.");

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

  using void_pointer = typename std::pointer_traits<pointer>::rebind<void>;
  using const_void_pointer =
      typename std::pointer_traits<pointer>::rebind<const void>;
  using difference_type = allocator_type::difference_type;

  //! @brief The unsigned integer type to represent element counts.
  using size_type = allocator_type::size_type;

  using propagate_on_container_copy_assignment = std::false_type;
  using propagate_on_container_move_assignment = std::false_type;
  using propagate_on_container_swap = std::false_type;
  using is_always_equal = std::is_empty<allocator_type>::type;

  //! @}

  //! @name Public Member Alias Templates
  //! @{

  //! @brief The rebinded allocator type  for other element types.
  template <class OtherType>
  using rebind_alloc = fcarouge::null_allocator<OtherType>;

  template <class OtherType>
  using rebind_traits = std::allocator_traits<rebind_alloc<OtherType>>;

  //! @}

  //! @name Public Member Functions
  //! @{

  [[nodiscard]] static constexpr pointer allocate(allocator_type &allocator,
                                                  size_type count);
  [[nodiscard]] static constexpr pointer
  allocate(allocator_type &allocator, size_type count, const_void_pointer hint);
  static constexpr void deallocate(allocator_type &a, pointer p, size_type n);
  template <class OtherType, class... Args>
  static constexpr void construct(allocator_type &allocator,
                                  OtherType *other_pointer,
                                  Args &&... arguments);
  template <class OtherType>
  static constexpr void destroy(allocator_type &allocator,
                                OtherType *other_pointer);

  //! @brief Obtains the maximum theoretically possible allocation size.
  //!
  //! @param allocator The unused allocator to detect the maximum size of.
  //! Irrelevent since this allocator is stateless.
  //!
  //! @return Theoretical maximum allocation size, that is, exactly zero.
  //!
  //! @complexity Constant.
  static constexpr size_type max_size(const allocator_type &allocator) noexcept
  {
    (void)allocator;
    return 0;
  }

  //! @brief Obtains the copy-constructed version of the allocator.
  //!
  //! @param allocator The allocator used by a standard container passed as an
  //! argument to a container copy constructor.
  //!
  //! @return The allocator to use by the copy-constructed standard containers.
  //!
  //! @complexity Constant.
  static constexpr allocator_type
  select_on_container_copy_construction(const allocator_type &allocator)
  {
    return allocator;
  }

  //! @}
};
} // namespace std

#endif // FCAROUGE_NULL_ALLOCATOR_HPP
