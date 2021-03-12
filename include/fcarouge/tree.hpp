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

#ifndef FCAROUGE_TREE_HPP
#define FCAROUGE_TREE_HPP

#include <cstddef>
// std::ptrdiff_t std::size_t

#include <cstdint>
// std::int_fast16_t std::int_fast32_t std::int_fast64_t std::int_fast8_t
// std::int_least16_t std::int_least32_t std::int_least64_t std::int_least8_t
// std::int16_t std::int32_t std::int64_t std::int8_t std::intmax_t
// std::intptr_t std::uint_fast16_t std::uint_fast32_t std::uint_fast64_t
// std::uint_fast8_t std::uint_least16_t std::uint_least32_t std::uint_least64_t
// std::uint_least8_t std::uint16_t std::uint32_t std::uint64_t std::uint8_t
// std::uintmax_t std::uintptr_t

#include <iterator>
// std::input_iterator_tag

#include <limits>
// std::numeric_limits

#include <memory>
// std::addressof std::allocator std::allocator_traits
// std::construct_at std::destroy_at

#include <ostream>
// std::basic_ostream

#include <string>
// std::basic_string std::string std::u16string std::u32string std::u8string
// std::wstring

#include <type_traits>
// std::is_same_v

#include <utility>
// std::forward std::move

//! @namespace fcarouge Francois Carouge's projects namespace. Lowers the name
//! conflict probability in large projects. Use using-declarations or
//! namespace-alias-definition per your project guidelines.
namespace fcarouge
{
//! @brief A tree data structure for C++.
//!
//! @details The `fcarouge::tree` type is a hierarchical tree data structure.
//! The container is:
//! - generic with respect to the type of stored values and allocator as
//! template parameters,
//! - non-linear compared to arrays, linked lists, stacks, and queues as a node
//! may lead to multiple nodes,
//! - non-associative compared to maps and sets as values are not keyed,
//! - unordered since internally, the elements are not sorted or maintained in
//! any particular order but externally, the insertion order is upheld,
//! - recursive in its facade exposing a recursively referenced collection of
//! nodes, each containing a value,
//! - standard layout class type which may help with memory and cross language
//! communication,
//! - unspecified iteration order except that each element is visited only once,
//! - implemented operations without recursive calls to guarantee a constant
//! stack usage limit,
//! - compile time evaluation compatible,
//! - employing generational C++ features advantageously up to C++20 standard,
//! - separating algorithmic from container concerns,
//! - influenced by the Standard Template Library (STL) principles and the C++
//! Core Guidelines in its design tradeoffs,
//! - intelligibly documented for the wider audience.
//!
//! @tparam Type The type of the contained data elements. The requirements that
//! are imposed on the elements depend on the actual operations performed on the
//! container. Generally, it is required that element type meets the
//! requirements of Erasable, but member functions impose stricter requirements.
//! This container (but not its members) can be instantiated with an incomplete
//! element type if the allocator satisfies the allocator completeness
//! requirements.
//! @tparam AllocatorType An allocator that is used to acquire/release memory
//! and to construct/destroy the elements in that memory. The type must meet the
//! requirements of Allocator. The behavior is undefined if
//! `Allocator::value_type` is not the same as `Type`.
template <class Type, class AllocatorType = std::allocator<Type>> class tree
{
  public:
  static_assert(std::is_same_v<Type, typename AllocatorType::value_type>,
                "The container's element value type and its allocator's value "
                "type must match per N4861 22.2.1 "
                "[container.requirements.general]/16 allocator_type.");

  //! @name Public Member Types
  //! @{

  //! @brief The type of the contained data elements.
  using value_type = Type;

  //! @brief The type of the allocator for all memory allocations of this
  //! container.
  using allocator_type = AllocatorType;

  //! @brief The unsigned integer type to represent element counts.
  using size_type = std::size_t;

  //! @brief Signed integer type to represent element distances.
  using difference_type = std::ptrdiff_t;

  //! @brief The reference type of the contained data elements.
  using reference = value_type &;

  //! @brief The constant reference type of the contained data elements.
  using const_reference = const value_type &;

  //! @brief The pointer type of the contained data elements.
  using pointer = typename std::allocator_traits<AllocatorType>::pointer;

  //! @brief The constant pointer type of the contained data elements.
  using const_pointer =
      typename std::allocator_traits<AllocatorType>::const_pointer;

  //! @}

  private:
  //! @name Private Member Types
  //! @{

  //! @brief Branch node data structure type.
  //!
  //! @details Internal implementation details of the node data structure type
  //! containing the element data.
  struct internal_node_type {
    //! @name Public Member Types
    //! @{

    //! @brief The type of the contained data elements.
    using value_type = tree::value_type;

    //! @}

    //! @name Public Search Member Functions
    //! @{

    //! @brief Finds the nearest right sibling of itself or ancestor.
    //!
    //! @details Recursively walks the tree.
    //!
    //! @return The pointer to the nearest right sibling of itself or ancestor;
    //! or `nullptr` if such a node doesn't exist.
    [[nodiscard]] constexpr internal_node_type *
    next_ancestor_sibling() const noexcept
    {
      const internal_node_type *current = this;
      while (current) {
        if (current->right_sibling) {
          return current->right_sibling;
        }
        current = current->parent;
      }

      return nullptr;
    }

    //! @}

    //! @name Public Member Variables
    //! @{

    value_type data;
    internal_node_type *first_child = nullptr;
    internal_node_type *last_child = nullptr;
    internal_node_type *left_sibling = nullptr;
    internal_node_type *right_sibling = nullptr;
    internal_node_type *parent = nullptr;

    //! @}
  };

  //! @brief Rebind the element type allocator to the internal container nodes
  //! allocator.
  using internal_node_allocator_type = typename std::allocator_traits<
      AllocatorType>::template rebind_alloc<internal_node_type>;

  //! @brief The node allocator traits access.
  using internal_node_allocator_traits =
      std::allocator_traits<internal_node_allocator_type>;

  //! @}

  public:
  //! @name Public Member Types
  //! @{

  //! @brief Type to identify and traverse the elements of the container.
  //!
  //! @details The iteration order of the standard iterator is unspecified,
  //! except that each element is visited only once.
  struct iterator {
    //! @name Public Member Types
    //! @{

    //! @brief The type of the contained data elements.
    using value_type = tree::value_type;

    //! @brief Signed integer type to represent element distances.
    using difference_type = tree::difference_type;

    //! @brief The reference type of the contained data elements.
    using reference = tree::reference;

    //! @brief The pointer type of the contained data elements.
    using pointer = tree::pointer;

    //! @brief The category of the iterator.
    using iterator_category = std::input_iterator_tag;

    //! @}

    //! @name Public Observer Member Functions
    //! @{

    //! @brief Dereferences the iterator to obtain the stored value. The
    //! behavior is undefined if the iterator is invalid.
    //!
    //! @return Reference to the element if the iterator is dereferencable.
    [[nodiscard]] constexpr reference operator*() const noexcept
    {
      return node->data;
    }

    //! @name Public Modifier Member Functions
    //! @{

    //! @brief Increments the iterator.
    //!
    //! @return Reference to the next iterator.
    constexpr iterator &operator++() noexcept
    {
      if (node->first_child) {
        node = node->first_child;
      } else {
        node = node->next_ancestor_sibling();
      }

      return *this;
    }

    //! @}

    [[nodiscard]] constexpr bool
    operator==(const iterator &other) const noexcept = default;

    //! @name Public Member Variables
    //! @{

    //! @brief The pointer to the node.
    internal_node_type *node = nullptr;

    //! @}
  };

  //! @brief Type to identify and traverse the constant elements of the
  //! container.
  //!
  //! @details The iteration order of the standard constant iterator is
  //! unspecified, except that each element is visited only once.
  struct const_iterator {
    //! @name Public Member Types
    //! @{

    //! @brief The type of the contained data elements.
    using value_type = tree::value_type;

    //! @brief Signed integer type to represent element distances.
    using difference_type = tree::difference_type;

    //! @brief The reference type of the contained data elements.
    using reference = tree::reference;

    //! @brief The pointer type of the contained data elements.
    using pointer = tree::pointer;

    //! @brief The category of the iterator.
    using iterator_category = std::input_iterator_tag;

    //! @}

    //! @name Public Member Functions
    //! @{

    //! @brief Default constructor needed for non-aggregate constant iterator.
    //!
    //! @details The default constructor is provided to allow simple default
    //! construction since the conversion constructor makes the constant
    //! iterator a non-aggregate type.
    constexpr const_iterator() noexcept = default;

    //! @brief Implicit iterator to constant iterator conversion.
    //!
    //! @details The regular, i.e. non-constant, iterator type is implicitely
    //! convertible to the constant iterator type per requirements. The
    //! conversion is performed through a (non-explicit) converting constructor.
    //! A conversion operator is not implemented to avoid disabling implicit
    //! move. Consequently the constant iterator is no longer an aggregate type
    //! hence disabling aggregate initialization.
    //!
    //! @note No conversion assignment operator is supported following the
    //! majority of Standard Template Library (STL) vendors implementation.
    constexpr const_iterator(const iterator &iterator) noexcept
            : node{ iterator.node }
    {
    }

    //! @brief Implicit node pointer to constant iterator conversion.
    //!
    //! @details Aggregate initialization is not available per implicit iterator
    //! conversion construction. The node pointer type is implicitely
    //! convertible to the constant iterator type to allow list initialization.
    constexpr const_iterator(internal_node_type *node) noexcept : node{ node }
    {
    }

    //! @}

    //! @name Public Observer Member Functions
    //! @{

    //! @brief Dereferences the iterator to obtain the stored value. The
    //! behavior is undefined if the iterator is invalid.
    //!
    //! @return Reference to the element if the iterator is dereferencable.
    [[nodiscard]] constexpr reference operator*() const noexcept
    {
      return node->data;
    }

    //! @}

    //! @name Public Modifier Member Functions
    //! @{

    //! @brief Increments the iterator.
    //!
    //! @return Reference to the next iterator.
    constexpr const_iterator &operator++() noexcept
    {
      if (node->first_child) {
        node = node->first_child;
      } else {
        node = node->next_ancestor_sibling();
      }

      return *this;
    }

    //! @}

    [[nodiscard]] constexpr bool
    operator==(const const_iterator &other) const noexcept = default;

    //! @name Public Member Variables
    //! @{

    //! @brief The pointer to the node.
    internal_node_type *node = nullptr;

    //! @}
  };

  //! @brief The node handle type of the container.
  //!
  //! @details Specialization of node handle.
  class node_type
  {
  };

  //! @brief The result type of inserting a `node_type` in the container.
  template <class IteratorType> struct insert_return_type {
    //! @brief The node handle type of the container.
    using node_type = tree::node_type;

    IteratorType position;
    bool inserted;
    node_type node;
  };

  //! @}

  //! @name Public Member Functions
  //! @{

  //! @brief Constructs an empty container with a default-constructed allocator.
  //!
  //! @complexity Constant.
  //!
  //! @exceptions Strong exception guarantees: no effect on exception. Same
  //! exceptions specification as the allocator `AllocatorType` default
  //! constructor, if any.
  constexpr tree() noexcept(noexcept(AllocatorType{})) = default;

  //! @brief Constructs an empty container with the given allocator.
  //!
  //! @param allocator Allocator to use for all memory allocations of this
  //! container.
  //!
  //! @complexity Constant.
  //!
  //! @exceptions Strong exception guarantees: no effect on exception. Same
  //! exceptions specification as the allocator `AllocatorType` copy
  //! constructor, if any.
  constexpr explicit tree(const AllocatorType &allocator) noexcept(
      noexcept(internal_node_allocator_type{ allocator }))
          : node_allocator{ allocator }
  {
  }

  //! @brief Copy constructs a container with a default-constructed allocator.
  //!
  //! @details Constructs the container with the copy of the contents of the
  //! `other` container.
  //!
  //! @param other Another container to be used as source to initialize the
  //! elements of the container with.
  //!
  //! @note Allocator is obtained as if by calling:
  //! `std::allocator_traits<AllocatorType>::
  //! select_on_container_copy_construction(other.get_allocator())`
  //!
  //! @complexity Linear in size of the other container.
  constexpr tree(const tree &other) noexcept
          : node_allocator{ std::allocator_traits<AllocatorType>::
                                select_on_container_copy_construction(
                                    other.node_allocator) },
            root{ copy(other.root) }, node_count{ other.node_count }
  {
  }

  //! @brief Copy constructs a container with an allocator.
  //!
  //! @details Allocator-extended copy constructor. Constructs the container
  //! with the copy of the contents of the `other` container.
  //!
  //! @param other Another container to be used as source to initialize the
  //! elements of the container with.
  //! @param allocator Allocator to use for all memory allocations of this
  //! container.
  //!
  //! @complexity Linear in size of the other container.
  constexpr tree(const tree &other, const AllocatorType &allocator)
          : node_allocator{ allocator }, root{ copy(other.root) }, node_count{
              other.node_count
            }
  {
  }

  //! @brief Move constructs a container.
  //!
  //! @details Move constructor. Constructs the container with the contents of
  //! the `other` container using move semantics (i.e. the data in `other`
  //! container is moved from the other into this container). The allocator is
  //! obtained by move-construction from the allocator belonging to other.
  //!
  //! @param other Another container to be used as source to initialize the
  //! elements of the container with.
  //!
  //! @complexity Constant.
  constexpr tree(tree &&other) noexcept
          : node_allocator{ std::move(other.node_allocator) },
            root{ other.root }, node_count{ other.node_count }
  {
    other.root = nullptr;
  }

  //! @brief Allocator-extended move constructor.
  //!
  //! @details Constructs the container with the contents of the other using
  //! move semantics (i.e. the data in `other` container is moved from the other
  //! into this container). Using the provided allocator for the new container,
  //! moving the contents from other; if `allocator != other.get_allocator()`,
  //! this results in an element-wise move.
  //!
  //! @param other Another container to be used as source to initialize the
  //! elements of the container with.
  //! @param allocator Allocator to use for all memory allocations of this
  //! container.
  //!
  //! @complexity Constant.
  constexpr tree(tree &&other, const AllocatorType &allocator) noexcept
          : node_allocator{ allocator }, node_count{ other.node_count }
  {
    if (allocator != other.node_allocator) {
      root = copy(other.root);
    } else {
      root = other.root;
      other.root = nullptr;
    }
  }

  //! @brief Constructs the container with by copying the value for its root.
  //!
  //! @param value The value to initialize elements of the container with.
  //!
  //! @complexity Constant.
  constexpr explicit tree(const_reference value)
          : root{ node_allocator.allocate(1) }, node_count{ 1 }
  {
    std::construct_at(root, value);
  }

  //! @brief Constructs the container with by copying the value for its root.
  //!
  //! @param value The value to initialize elements of the container with.
  //! @param allocator Allocator to use for all memory allocations of this
  //! container.
  //!
  //! @complexity Constant.
  constexpr tree(const_reference value, const AllocatorType &allocator)
          : node_allocator{ allocator }, root{ node_allocator.allocate(1) },
            node_count{ 1 }
  {
    std::construct_at(root, value);
  }

  //! @brief Constructs the container by moving the value for its root.
  //!
  //! @param value The value to initialize elements of the container with.
  //!
  //! @complexity Constant.
  constexpr explicit tree(value_type &&value)
          : root{ node_allocator.allocate(1) }, node_count{ 1 }
  {
    std::construct_at(root, std::move(value));
  }

  //! @brief Constructs the container by moving the value for its root.
  //!
  //! @param value The value to initialize elements of the container with.
  //! @param allocator Allocator to use for all memory allocations of this
  //! container.
  //!
  //! @complexity Constant.
  constexpr tree(value_type &&value, const AllocatorType &allocator)
          : node_allocator{ allocator }, root{ node_allocator.allocate(1) },
            node_count{ 1 }
  {
    std::construct_at(root, std::move(value));
  }

  //! @brief Destructs the container.
  //!
  //! @details The destructors of the elements are called and the used
  //! storage is deallocated.
  //!
  //! @note If the elements are pointers, the pointed-to objects are not
  //! destroyed.
  //!
  //! @complexity Linear in the size of the container.
  //!
  //! @exceptions The exception specification needs to be confirmed.
  constexpr ~tree() noexcept
  {
    axe(root);
  }

  //! @brief Copy assignment operator.
  //!
  //! @details Destroys or copy-assigns the contents with a copy of the contents
  //! of the other container. Self copy assignement is valid, safe, and
  //! meets specifications.
  //!
  //! @param other Another container to be used as source to initialize the
  //! elements of the container with.
  //!
  //! @return The reference value of this implicit object container parameter,
  //! i.e. `*this`.
  //!
  //! @complexity Linear in the size of this and the other container.
  tree &operator=(const tree &other)
  {
    if (this != std::addressof(other)) {
      axe(root);
      node_allocator = std::allocator_traits<AllocatorType>::
          select_on_container_copy_construction(other.node_allocator);
      root = copy(other.root);
      node_count = other.node_count;
    }
    return *this;
  }

  //! @brief Move assignment operator.
  //!
  //! @details Replaces the contents of the container with those of the `other`
  //! container using move semantics (i.e. the data in `other` container is
  //! moved from the other into this container). The other container is in a
  //! valid but unspecified state afterwards. The allocator is obtained by
  //! move-construction from the allocator belonging to other. Self move
  //! assignement is valid, safe, and meets specifications.
  //!
  //! @param other Another container to be used as source to initialize the
  //! elements of the container with.
  //!
  //! @return The reference value of this implicit object container parameter,
  //! i.e. `*this`.
  //!
  //! @complexity Constant.
  //!
  //! @exceptions Same exceptions specification as the allocator `AllocatorType`
  //! move assignment operator, if any.
  constexpr tree &operator=(tree &&other) noexcept
  {
    if (this != std::addressof(other)) {
      axe(root);
      node_allocator = std::move(other.node_allocator);
      root = other.root;
      node_count = other.node_count;
      other.root = nullptr;
    }
    return *this;
  }

  //! @brief Value copy assignment operator.
  //!
  //! @details Replaces the contents of the container with a copy of the
  //! contents of the value for its root.
  //!
  //! @param value The value to initialize the container with.
  //!
  //! @return The reference value of this implicit object container parameter,
  //! i.e. `*this`.
  //!
  //! @complexity Linear in the size of this container.
  constexpr tree &operator=(const_reference value)
  {
    axe(root);
    root = node_allocator.allocate(1);
    std::construct_at(root, value);
    node_count = 1;
    return *this;
  }

  //! @brief Value move assignment operator.
  //!
  //! @details Replaces the contents of the container with those of the value
  //! using move semantics (i.e. the value data is moved into the root of this
  //! container). The value is in a valid but unspecified state afterwards.
  //!
  //! @param value The value to initialize the container with.
  //!
  //! @return The reference value of this implicit object container parameter,
  //! i.e. `*this`.
  //!
  //! @complexity Linear in the size of this container.
  constexpr tree &operator=(value_type &&value)
  {
    axe(root);
    root = node_allocator.allocate(1);
    std::construct_at(root, std::move(value));
    node_count = 1;
    return *this;
  }

  //! @brief Copy assignment.
  //!
  //! @details Destroys or copy-assigns the contents with a copy of the contents
  //! of the other container. Self copy assignement is valid, safe, and
  //! meets specifications.
  //!
  //! @param other Another container to be used as source to initialize the
  //! elements of the container with.
  //!
  //! @return The reference value of this implicit object container parameter,
  //! i.e. `*this`.
  //!
  //! @complexity Linear in the size of this and the other container.
  constexpr tree &assign(const tree &other) noexcept
  {
    if (this != std::addressof(other)) {
      axe(root);
      node_allocator = std::allocator_traits<AllocatorType>::
          select_on_container_copy_construction(other.node_allocator);
      root = copy(other.root);
      node_count = other.node_count;
    }
    return *this;
  }

  //! @brief Move assignment.
  //!
  //! @details Replaces the contents of the container with those of the `other`
  //! container using move semantics (i.e. the data in `other` container is
  //! moved from the other into this container). The other container is in a
  //! valid but unspecified state afterwards. The allocator is obtained by
  //! move-construction from the allocator belonging to other. Self move
  //! assignement is valid, safe, and meets specifications.
  //!
  //! @param other Another container to be used as source to initialize the
  //! elements of the container with.
  //!
  //! @return The reference value of this implicit object container parameter,
  //! i.e. `*this`.
  //!
  //! @complexity Constant.
  //!
  //! @exceptions Same exceptions specification as the allocator `AllocatorType`
  //! move assignment operator, if any.
  constexpr tree &assign(tree &&other) noexcept
  {
    if (this != std::addressof(other)) {
      axe(root);
      node_allocator = std::move(other.node_allocator);
      root = other.root;
      node_count = other.node_count;
      other.root = nullptr;
    }
    return *this;
  }

  //! @brief Value copy assignment.
  //!
  //! @details Replaces the contents of the container with a copy of the
  //! contents of the value for its root.
  //!
  //! @param value The value to initialize the container with.
  //!
  //! @return The reference value of this implicit object container parameter,
  //! i.e. `*this`.
  //!
  //! @complexity Linear in the size of this container.
  constexpr tree &assign(const_reference value) noexcept
  {
    axe(root);
    root = node_allocator.allocate(1);
    std::construct_at(root, value);
    node_count = 1;
    return *this;
  }

  //! @brief Value move assignment.
  //!
  //! @details Replaces the contents of the container with those of the value
  //! using move semantics (i.e. the value data is moved into the root of this
  //! container). The value is in a valid but unspecified state afterwards.
  //!
  //! @param value The value to initialize the container with.
  //!
  //! @return The reference value of this implicit object container parameter,
  //! i.e. `*this`.
  //!
  //! @complexity Linear in the size of this container.
  constexpr tree &assign(value_type &&value) noexcept
  {
    axe(root);
    root = node_allocator.allocate(1);
    std::construct_at(root, std::move(value));
    node_count = 1;
    return *this;
  }

  //! @brief Returns the allocator associated with the container.
  //!
  //! @return The associated allocator.
  //!
  //! @complexity Constant.
  [[nodiscard]] constexpr allocator_type get_allocator() const noexcept
  {
    return node_allocator;
  }

  //! @}

  //! @name Public Element Access Member Functions
  //! @{

  //! @brief Returns a reference to the first element in the container.
  //!
  //! @details Calling front on an empty container causes undefined behavior.
  //!
  //! @return Reference to the first element.
  //!
  //! @complexity Constant.
  //!
  //! @note For a non-empty container `c`, the expression `c.front()` is
  //! equivalent to `*c.begin()`.
  [[nodiscard]] constexpr reference front()
  {
    return root->data;
  }

  //! @brief Returns a constant reference to the first element in the
  //! container.
  //!
  //! @details Calling front on an empty container causes undefined behavior.
  //!
  //! @return Constant reference to the first element.
  //!
  //! @complexity Constant.
  //!
  //! @note For a non-empty container `c`, the expression `c.front()` is
  //! equivalent to `*c.begin()`.
  [[nodiscard]] constexpr const_reference front() const
  {
    return root->data;
  }

  //! @}

  //! @name Public Iterator Member Functions
  //! @{

  //! @brief Returns an iterator to the first element of the container.
  //!
  //! @details If the container is empty, the returned iterator will be equal to
  //! `end()`.
  //!
  //! @return Iterator to the first element.
  //!
  //! @complexity Constant.
  [[nodiscard]] constexpr iterator begin() noexcept
  {
    return { root };
  }

  //! @brief Returns a constant iterator to the first element of the container.
  //!
  //! @details If the container is empty, the returned constant iterator will be
  //! equal to `end()`.
  //!
  //! @return Constant iterator to the first element.
  //!
  //! @complexity Constant.
  [[nodiscard]] constexpr const_iterator begin() const noexcept
  {
    return { root };
  }

  //! @brief Returns a constant iterator to the first element of the container.
  //!
  //! @details If the container is empty, the returned constant iterator will be
  //! equal to `end()`.
  //!
  //! @return Constant iterator to the first element.
  //!
  //! @complexity Constant.
  [[nodiscard]] constexpr const_iterator cbegin() const noexcept
  {
    return { root };
  }

  //! @brief Returns an iterator to the element following the last element of
  //! the container.
  //!
  //! @details This element acts as a placeholder; attempting to access it
  //! results in undefined behavior. If the container is empty, the returned
  //! constant iterator will be equal to `begin()`.
  //!
  //! @return Iterator to the element following the last element.
  //!
  //! @complexity Constant.
  [[nodiscard]] constexpr iterator end() noexcept
  {
    return {};
  }

  //! @brief Returns a constant iterator to the element following the last
  //! element of the container.
  //!
  //! @details This element acts as a placeholder; attempting to access it
  //! results in undefined behavior. If the container is empty, the returned
  //! constant iterator will be equal to `begin()`.
  //!
  //! @return Constant iterator to the element following the last element.
  //!
  //! @complexity Constant.
  [[nodiscard]] constexpr const_iterator end() const noexcept
  {
    return {};
  }

  //! @brief Returns a constant iterator to the element following the last
  //! element of the container.
  //!
  //! @details This element acts as a placeholder; attempting to access it
  //! results in undefined behavior. If the container is empty, the returned
  //! constant iterator will be equal to `begin()`.
  //!
  //! @return Constant iterator to the element following the last element.
  //!
  //! @complexity Constant.
  [[nodiscard]] constexpr const_iterator cend() const noexcept
  {
    return {};
  }

  //! @}

  //! @name Public Capacity Member Functions
  //! @{

  //! @brief Checks if the container has no elements.
  //!
  //! @details Whether the beginning iterator equals the ending iterator.
  //!
  //! @return true if the container is empty, false otherwise.
  //!
  //! @complexity Constant.
  [[nodiscard]] constexpr bool empty() const noexcept
  {
    return node_count == 0;
  }

  //! @brief Returns the number of elements in the container.
  //!
  //! @details The absolute distance between the beginning and end iterators.
  //!
  //! @return The number of elements in the container.
  //!
  //! @complexity Constant.
  [[nodiscard]] constexpr size_type size() const noexcept
  {
    return node_count;
  }

  //! @brief Returns the maximum number of elements the container is able to
  //! hold.
  //!
  //! @details The maximum number of elements depends on the system or library
  //! implementation limitations. The absolute distance between the beginning
  //! and end iterators for the largest container or the maximum number of
  //! element nodes theoretically allocated, whichever is smaller.
  //!
  //! @return Maximum number of elements.
  //!
  //! @complexity Constant.
  //!
  //! @note This value typically reflects the theoretical limit on the size of
  //! the container, at most `std:: numeric_limits<difference_type>:: max()`, or
  //! at runtime, the size of the container may be limited to a value smaller
  //! than `max_size()` by the amount of memory (usualy RAM) available.
  //! The minima is selected without using and importing the minimum `std::min`
  //! operation from the `<algorithm>` library to reduce coupling.
  [[nodiscard]] constexpr size_type max_size() const noexcept
  {
    return internal_node_allocator_traits::max_size(node_allocator) <
                   static_cast<size_type>(
                       std::numeric_limits<difference_type>::max())
               ? internal_node_allocator_traits::max_size(node_allocator)
               : static_cast<size_type>(
                     std::numeric_limits<difference_type>::max());
  }

  //! @}

  //! @name Public Modifier Member Functions
  //! @{

  //! @brief Erases all elements from the container.
  //!
  //! @details After this call, the size member function calls returns zero.
  //! Invalidates any references, pointers, or iterators referring to
  //! contained elements. Any past-the-end iterator remains valid.
  //!
  //! @complexity Linear in size of this container, i.e., the number of
  //! elements.
  //!
  //! @benchmark
  //! @image{inline} html "benchmark/clear.svg"
  constexpr void clear() noexcept
  {
    axe(root);
    root = nullptr;
    node_count = 0;
  }

  //! @brief Inserts a new element into the container copied
  //! directly before the `position` iterator as the new left sibling.
  //!
  //! @details The value is copied at a location element provided by the
  //! container. No iterators or references are invalidated. Inserts at the root
  //! position as the new root. Inserts before the beginning `begin()` position
  //! as the new root. Inserts before the ending `end()` position.
  //!
  //! @param position The constant iterator before which the new element will be
  //! constructed. The iterator may be the beginning `begin()` or ending `end()`
  //! iterator.
  //! @param value The value to copy in the the element node.
  //!
  //! @return The iterator pointing to the inserted element.
  //!
  //! @complexity Constant.
  constexpr iterator insert(const_iterator position, const_reference value)
  {
    // The allocated node is in-place construced and recorded in every
    // following statements.
    internal_node_type *node = node_allocator.allocate(1);

    // Insert the new node...
    // ...before the position node...
    if (internal_node_type *position_node = position.node) {
      // ...as the new left child...
      if (position_node->parent) {
        std::construct_at(node, value, nullptr, nullptr,
                          position_node->left_sibling, position_node,
                          position_node->parent);
        position_node->left_sibling = node;
        // ...with a left sibling node.
        if (internal_node_type *left_node = node->left_sibling) {
          left_node->right_sibling = node;
        }
        // ...without a left sibling node.
        else {
          position_node->parent->first_child = node;
        }
      }
      // ...as the new root.
      else {
        std::construct_at(node, value, position_node, position_node);
        position_node->parent = node;
        root = node;
      }
    }
    // ...as the new last node...
    else {
      // ... as the last child of the root node.
      if (root) {
        std::construct_at(node, value, nullptr, nullptr, root->last_child,
                          nullptr, root);
        if (!root->first_child) {
          root->first_child = node;
        }
        if (root->last_child) {
          root->last_child->right_sibling = node;
        }
        root->last_child = node;
      }
      // ...as the sole, and root node.
      else {
        std::construct_at(node, value);
        root = node;
      }
    }

    ++node_count;
    return { node };
  }

  //! @brief Inserts a new element into the container moved
  //! directly before the `position` iterator as the new left sibling.
  //!
  //! @details The value is moved at a location element provided by the
  //! container. No iterators or references are invalidated. Inserts at the root
  //! position as the new root. Inserts before the beginning `begin()` position
  //! as the new root. Inserts before the ending `end()` position.
  //!
  //! @param position The constant iterator before which the new element will be
  //! constructed. The iterator may be the beginning `begin()` or ending `end()`
  //! iterator.
  //! @param value The value to move in the the element node.
  //!
  //! @return The iterator pointing to the inserted element.
  //!
  //! @complexity Constant.
  constexpr iterator insert(const_iterator position, value_type &&value)
  {
    // The allocated node is in-place construced and recorded in every
    // following statements.
    internal_node_type *node = node_allocator.allocate(1);

    // Insert the new node...
    // ...before the position node...
    if (internal_node_type *position_node = position.node) {
      // ...as the new left child...
      if (position_node->parent) {
        std::construct_at(node, std::move(value), nullptr, nullptr,
                          position_node->left_sibling, position_node,
                          position_node->parent);
        position_node->left_sibling = node;
        // ...with a left sibling node.
        if (internal_node_type *left_node = node->left_sibling) {
          left_node->right_sibling = node;
        }
        // ...without a left sibling node.
        else {
          position_node->parent->first_child = node;
        }
      }
      // ...as the new root.
      else {
        std::construct_at(node, std::move(value), position_node, position_node);
        position_node->parent = node;
        root = node;
      }
    }
    // ...as the new last node...
    else {
      // ... as the last child of the root node.
      if (root) {
        std::construct_at(node, std::move(value), nullptr, nullptr,
                          root->last_child, nullptr, root);
        if (!root->first_child) {
          root->first_child = node;
        }
        if (root->last_child) {
          root->last_child->right_sibling = node;
        }
        root->last_child = node;
      }
      // ...as the sole, and root node.
      else {
        std::construct_at(node, std::move(value));
        root = node;
      }
    }

    ++node_count;
    return { node };
  }

  template <class InputIteratorType>
  constexpr iterator insert(const_iterator position, InputIteratorType first,
                            InputIteratorType last);

  constexpr iterator insert(const_iterator position,
                            std::initializer_list<Type> initializers);

  //! @brief Inserts a new element into the container constructed in-place to
  //! the beginning of the container.
  //!
  //! @details The element is constructed through `std::construct_at`
  //! equivalenent to placement-new to construct the element in-place, usable in
  //! evaluation of constant expressions, at a location provided by the
  //! container. The `arguments` are forwarded to the constructor as
  //! `std::forward<ArgumentsType>(arguments)...`. No iterators or references
  //! are invalidated. Inserts at the root position as the new root.
  //!
  //! @tparam ArgumentsType The argument types to forward to the constructor of
  //! the element.
  //!
  //! @param arguments The arguments to forward to the constructor of the
  //! element.
  //!
  //! @return Reference to the inserted element.
  //!
  //! @complexity Constant.
  //!
  //! @benchmark
  //! @image{inline} html "benchmark/emplace_front_cumulative.svg"
  //! @image{inline} html "benchmark/emplace_front_incremental.svg"
  template <class... ArgumentsType>
  constexpr reference emplace_front(ArgumentsType &&... arguments)
  {
    // The allocated node is in-place construced and recorded in every
    // following statements.
    internal_node_type *node = node_allocator.allocate(1);

    // Insert the new node...
    std::construct_at(node, std::forward<ArgumentsType>(arguments)..., root,
                      root, nullptr, nullptr, nullptr);
    // ...as the new root node.
    if (root) {
      root->parent = node;
    }

    root = node;
    ++node_count;
    return node->data;
  }

  //! @brief Inserts a new element into the container constructed in-place
  //! directly before the `position` iterator as the new left sibling.
  //!
  //! @details The element is constructed through `std::construct_at`
  //! equivalenent to placement-new to construct the element in-place, usable in
  //! evaluation of constant expressions, at a location provided by the
  //! container. The `arguments` are forwarded to the constructor as
  //! `std::forward<ArgumentsType>(arguments)...`. No iterators or references
  //! are invalidated. Inserts at the root position as the new root. Inserts
  //! before the beginning `begin()` position as the new root. Inserts before
  //! the ending `end()` position.
  //!
  //! @tparam ArgumentsType The argument types to forward to the constructor of
  //! the element.
  //!
  //! @param position The constant iterator before which the new element will be
  //! constructed. The iterator may be the beginning `begin()` or ending `end()`
  //! iterator.
  //! @param arguments The arguments to forward to the constructor of the
  //! element.
  //!
  //! @return The iterator pointing to the inserted element.
  //!
  //! @complexity Constant.
  template <class... ArgumentsType>
  constexpr iterator emplace(const_iterator position,
                             ArgumentsType &&... arguments)
  {
    // The allocated node is in-place construced and recorded in every
    // following statements.
    internal_node_type *node = node_allocator.allocate(1);

    // Insert the new node before the position node...
    if (internal_node_type *position_node = position.node) {
      // ...as the new left child...
      if (position_node->parent) {
        std::construct_at(node, std::forward<ArgumentsType>(arguments)...,
                          nullptr, nullptr, position_node->left_sibling,
                          position_node, position_node->parent);
        position_node->left_sibling = node;
        // ...with a left sibling node.
        if (internal_node_type *left_node = node->left_sibling) {
          left_node->right_sibling = node;
        }
        // ...without a left sibling node.
        else {
          position_node->parent->first_child = node;
        }
      }
      // ...as the new root.
      else {
        std::construct_at(node, std::forward<ArgumentsType>(arguments)...,
                          position_node, position_node);
        position_node->parent = node;
        root = node;
      }
    }
    // ...as the new last node...
    else {
      // ... as the last child of the root node.
      if (root) {
        std::construct_at(node, std::forward<ArgumentsType>(arguments)...,
                          nullptr, nullptr, root->last_child, nullptr, root);
        if (!root->first_child) {
          root->first_child = node;
        }
        if (root->last_child) {
          root->last_child->right_sibling = node;
        }
        root->last_child = node;
      }
      // ...as the sole, and root node.
      else {
        std::construct_at(node, std::forward<ArgumentsType>(arguments)...);
        root = node;
      }
    }

    ++node_count;
    return { node };
  }

  //! @brief Removes the specified element including its sub-tree.
  //!
  //! @details Removes the element at `position` and its associated
  //! sub-tree. References and iterators to the erased elements are invalidated.
  //! Other references and iterators are not affected. The iterator `position`
  //! must be valid and dereferenceable. Thus the `end()` iterator which is
  //! valid, but is not dereferenceable cannot be used as a value for
  //! `position`. The same is applicable for the `begin()` iterator on an empty
  //! container. The container's size is reduded by the number of elements
  //! removed, that is the node and all nodes in its sub-tree. If the erased
  //! node is the root, the tree is empty.
  //!
  //! @param position The iterator to the element to remove with its subtree.
  //!
  //! @return Iterator following the last removed element. If `position` refers
  //! to the last element, then the `end()` iterator is returned.
  constexpr iterator erase(iterator position)
  {
    // Identify the node following this subtree which will become the next node,
    // separate the subtree out of the tree, and recursively erase the subtree.
    internal_node_type *next{ position.node->next_ancestor_sibling() };
    cleave(position.node);
    prune(position.node);

    return { next };
  }

  //! @brief Removes the specified element including its sub-tree.
  //!
  //! @details Removes the element at `position` and its associated
  //! sub-tree. References and iterators to the erased elements are invalidated.
  //! Other references and iterators are not affected. The iterator `position`
  //! must be valid and dereferenceable. Thus the `end()` iterator which is
  //! valid, but is not dereferenceable cannot be used as a value for
  //! `position`. The same is applicable for the `begin()` iterator on an empty
  //! container. The container's size is reduded by the number of elements
  //! removed, that is the node and all nodes in its sub-tree. If the erased
  //! node is the root, the tree is empty.
  //!
  //! @param position The constant iterator to the element to remove with its
  //! subtree.
  //!
  //! @return Iterator following the last removed element. If `position` refers
  //! to the last element, then the `end()` iterator is returned.
  constexpr iterator erase(const_iterator position)
  {
    // Identify the node following this subtree which will become the next node,
    // separate the subtree out of the tree, and recursively erase the subtree.
    internal_node_type *next{ position.node->next_ancestor_sibling() };
    cleave(position.node);
    prune(position.node);

    return { next };
  }

  //! @brief Inserts the given element value into the container directly after
  //! the last child of the `position` iterator as the new last child.
  //!
  //! @details No iterators or references are invalidated. The new element is
  //! initialized as a copy of `value`. `Type` must meet the CopyInsertable
  //! requirement to use this overload. Inserts after the beginning `begin()`
  //! position as the last child of the root if present, or as the root if the
  //! container is empty. Inserts after the ending `end()` position as the sole
  //! child of the last node if present, or as the root if the container is
  //! empty.
  //!
  //! @param position The parent node constant iterator for which the element
  //! will be inserted as the last child. The iterator may be the beginning
  //! `begin()` or ending `end()` iterator.
  //! @param value The data of the element to insert.
  //!
  //! @return The iterator pointing to the inserted element.
  //!
  //! @exceptions Strong exception guarantees: no effect on
  //! exception. The `Allocator::allocate()` allocation or the element copy/move
  //! constructor/assignment may throw.
  //! If `Type`'s move constructor is not `noexcept` and `Type` is not
  //! CopyInsertable into `*this`, the container will use the throwing move
  //! constructor. If it throws, the guarantee is waived and the effects are
  //! unspecified.
  //!
  //! @note This `push` modifier method definition is not represented in
  //! the Standard Template Library (STL) containers. The presence of the
  //! modifier is justified from the non-linear nature of the container in
  //! addition to the consistency claim with `insert` and `emplace` modifier
  //! method definitions.
  constexpr iterator push(const_iterator position, const_reference value)
  {
    return { emplace_last_child(position.node, value) };
  }

  //! @brief Inserts the given element value into the container directly after
  //! the last child of the `position` iterator as the new last child.
  //!
  //! @details No iterators or references are invalidated. The new element is
  //! initialized with a move of `value`. `Type` must meet the MoveInsertable
  //! requirement to use this overload. Inserts after the beginning `begin()`
  //! position as the last child of the root if present, or as the root if the
  //! container is empty. Inserts after the ending `end()` position as the sole
  //! child of the last node if present, or as the root if the container is
  //! empty.
  //!
  //! @param position The parent node constant iterator for which the element
  //! will be inserted as the last child. The iterator may be the beginning
  //! `begin()` or ending `end()` iterator.
  //! @param value The data of the element to insert.
  //!
  //! @return The iterator pointing to the inserted element.
  //!
  //! @exceptions Strong exception guarantees: no effect on
  //! exception. The `Allocator::allocate()` allocation or the element copy/move
  //! constructor/assignment may throw.
  //!
  //! @note This `push` modifier method definition is not represented in
  //! the Standard Template Library (STL) containers. The presence of the
  //! modifier is justified from the non-linear nature of the container in
  //! addition to the consistency claim with `insert` and `emplace` modifier
  //! method definitions.
  constexpr iterator push(const_iterator position, value_type &&value)
  {
    return { emplace_last_child(position.node, std::move(value)) };
  }

  //! @brief Prepends the given element to the beginning of the container.
  //!
  //! @details Prepends the given element as the new root. If the container is
  //! not empty the root becomes the sole child of the prepended element. No
  //! iterators or references are invalidated. The new element is initialized as
  //! a copy of `value`. `Type` must meet the CopyInsertable requirement to use
  //! this overload.
  //!
  //! @param value The data of the element to prepend.
  //!
  //! @complexity Constant.
  //!
  //! @exceptions Strong exception guarantees: no effect on
  //! exception. The `Allocator::allocate()` allocation or the element copy/move
  //! constructor/assignment may throw.
  //! If `Type`'s move constructor is not `noexcept` and `Type` is not
  //! CopyInsertable into `*this`, the container will use the throwing move
  //! constructor. If it throws, the guarantee is waived and the effects are
  //! unspecified.
  constexpr void push_front(const_reference value)
  {
    emplace_root(value);
  }

  //! @brief Prepends the given element to the beginning of the container.
  //!
  //! @details Prepends the given element as the new root. If the container is
  //! not empty the root becomes the sole child of the prepended element. No
  //! iterators or references are invalidated. The new element is initialized
  //! with a move of `value`. `Type` must meet the MoveInsertable requirement to
  //! use this overload.
  //!
  //! @param value The data of the element to prepend.
  //!
  //! @complexity Constant.
  //!
  //! @exceptions Strong exception guarantees: no effect on
  //! exception. The `Allocator::allocate()` allocation or the element copy/move
  //! constructor/assignment may throw.
  constexpr void push_front(value_type &&value)
  {
    emplace_root(std::move(value));
  }

  //! @brief Exchanges the contents of this container with those of the
  //! `other` container.
  //!
  //! @details Does not invoke any move, copy, or swap operations on
  //! individual elements. All iterators and references remain valid. The
  //! `Compare` objects must be Swappable, and they are exchanged using
  //! unqualified call to non-member swap. If `std::
  //! allocator_traits<allocator_type>:: propagate_on_container_swap:: value`
  //! is `true`, then the allocators are exchanged using an unqualified call
  //! to non-member swap. Otherwise, they are not swapped (and if
  //! `get_allocator()
  //! != other.get_allocator()`, the behavior is undefined).
  //!
  //! @param other The container to exchange the contents with.
  //!
  //! @complexity Constant.
  //!
  //! @note Iterators and references referring to an element in a container
  //! before the swap refers to the same element in the other container
  //! afterwards.
  void swap(tree &other); // noexcept(/* see below */);

  //! @}

  private:
  //! @name Private Modifier Member Functions
  //! @{

  //! @brief Isolates the specified element including its sub-tree.
  //!
  //! @details Orphans the node from its parent and disolves its sibling
  //! relationships. The container's size is not maintained and no longer
  //! corresponds to the container content. Cleaving the root or last node has
  //! the expected effects on the tree.
  //!
  //! @param node The pointer to the element to cleave.
  constexpr void cleave(internal_node_type *node)
  {
    if (node == root) {
      root = nullptr;
    }
    if (node->parent) {
      if (node->parent->first_child == node) {
        node->parent->first_child = node->right_sibling;
      }
      if (node->parent->last_child == node) {
        node->parent->last_child = node->left_sibling;
      }
    }
    if (node->left_sibling) {
      node->left_sibling->right_sibling = node->right_sibling;
      node->left_sibling = nullptr;
    }
    if (node->right_sibling) {
      node->right_sibling->left_sibling = node->left_sibling;
      node->right_sibling = nullptr;
    }
  }

  //! @brief Recursively erases the specified element including its sub-tree.
  //!
  //! @details Removes the `node` element and prunes its associated
  //! sub-tree. References and iterators to the erased elements are invalidated.
  //! Other references and iterators are not affected. The container's size is
  //! reduded by the number of elements removed, that is the node and all nodes
  //! in its sub-tree. If the erased node is the root, the tree is empty.
  //!
  //! @param node The pointer to the element to erase.
  constexpr void prune(internal_node_type *node)
  {
    while (internal_node_type *current = node) {
      if (current->last_child) {
        if (current->right_sibling) {
          current->last_child->right_sibling = current->right_sibling;
        }
        node = current->first_child;
      } else if (current->right_sibling) {
        node = current->right_sibling;
      } else {
        node = nullptr;
      }

      std::destroy_at(current);
      node_allocator.deallocate(current, 1);

      --node_count;
    }
  }

  //! @brief Axes the specified element including its sub-tree.
  //!
  //! @details Removes the `node` element and removes its associated
  //! sub-tree. References and iterators to the erased elements are invalidated.
  //! Other references and iterators are not affected. The container's size is
  //! not maintained and no longer corresponds to the container content.
  //!
  //! @param node The pointer to the element to erase.
  constexpr void axe(internal_node_type *node)
  {
    while (internal_node_type *current = node) {
      if (current->last_child) {
        if (current->right_sibling) {
          current->last_child->right_sibling = current->right_sibling;
        }
        node = current->first_child;
      } else if (current->right_sibling) {
        node = current->right_sibling;
      } else {
        node = nullptr;
      }

      std::destroy_at(current);
      node_allocator.deallocate(current, 1);
    }
  }

  //! @brief Inserts the given element value into the container directly after
  //! the last child of the `position` iterator as the new last child.
  //!
  //! @details No iterators or references are invalidated. The new element is
  //! in-place constructed and moved, or copied. Inserts after the beginning
  //! `begin()` position as the last child of the root if present, or as the
  //! root if the container is empty. Inserts after the ending `end()` position
  //! as the sole child of the last node if present, or as the root if the
  //! container is empty.
  //!
  //! @tparam ArgumentsType The argument types to forward to the constructor of
  //! the element.
  //!
  //! @param parent The parent node for which the element will be
  //! inserted as the last child. Emplacing a node without a parent places the
  //! node at the end.
  //! @param arguments The construction data of the element to insert.
  //!
  //! @return The iterator pointing to the inserted element.
  //!
  //! @exceptions Strong exception guarantees: no effect on
  //! exception. The `Allocator::allocate()` allocation or the element copy/move
  //! constructor/assignment may throw.
  //! If `Type`'s move constructor is not `noexcept` and `Type` is not
  //! CopyInsertable into `*this`, the container will use the throwing move
  //! constructor. If it throws, the guarantee is waived and the effects are
  //! unspecified.
  template <class... ArgumentsType>
  constexpr internal_node_type *
  emplace_last_child(internal_node_type *parent, ArgumentsType &&... arguments)
  {
    // The allocated child node is in-place construced and recorded in every
    // following statements.
    internal_node_type *child = node_allocator.allocate(1);

    // Insert the new node...
    // ...as the last child of the position node...
    if (parent) {
      std::construct_at(child, std::forward<ArgumentsType>(arguments)...,
                        nullptr, nullptr, parent->last_child, nullptr, parent);
      parent->last_child = child;

      // ...with a left sibling node.
      if (child->left_sibling) {
        child->left_sibling->right_sibling = child;
      }
      // ...without a left sibling node.
      else {
        parent->first_child = child;
        // ...whose parent was the last node...
      }
    }
    // ...as the new last node...
    else {
      // ... as the last child of the root node.
      if (root) {
        std::construct_at(child, std::forward<ArgumentsType>(arguments)...,
                          nullptr, nullptr, root->last_child, nullptr, root);
        if (!root->first_child) {
          root->first_child = child;
        }
        if (root->last_child) {
          root->last_child->right_sibling = child;
        }
        root->last_child = child;
      }
      // ...as the sole, and root node.
      else {
        std::construct_at(child, std::forward<ArgumentsType>(arguments)...);
        root = child;
      }
    }

    ++node_count;

    return child;
  }

  //! @brief Prepends the given element to the beginning of the container.
  //!
  //! @details Prepends the given element as the new root. If the container is
  //! not empty the root becomes the sole child of the prepended element. No
  //! iterators or references are invalidated. The new element is in-place
  //! constructed and moved, or copied.
  //!
  //! @tparam ArgumentsType The argument types to forward to the constructor of
  //! the element.
  //!
  //! @param arguments The construction data of the element to insert.
  //!
  //! @complexity Constant.
  //!
  //! @exceptions Strong exception guarantees: no effect on
  //! exception. The `Allocator::allocate()` allocation or the element copy/move
  //! constructor/assignment may throw.
  template <class... ArgumentsType>
  constexpr void emplace_root(ArgumentsType &&... arguments)
  {
    // The allocated node is in-place construced and recorded in every
    // following statements.
    internal_node_type *node = node_allocator.allocate(1);

    // Insert the new node and prepare it to be the new root...
    std::construct_at(node, std::forward<ArgumentsType>(arguments)..., root,
                      root);

    // ... by displacing the previous root.
    if (root) {
      root->parent = node;
    }
    root = node;

    ++node_count;
  }

  //! @brief Copies the node, its subtrees, and right siblings recursively.
  //!
  //! @details Constructs a new node from the `other_node` element value.
  //! Attaches the newly created child to its parent, if any. Attaches the newly
  //! created right sibling to its left sibling, if any.
  //!
  //! @param other_node The other tree node to copy.
  //!
  //! @complexity Linear in the size of the number of nodes copied.
  internal_node_type *copy(internal_node_type *other_node)
  {
    // If there is another node to copy...
    if (other_node) {
      // ...allocate and in-place construct the first node with this container's
      // allocator and the other node data value...
      internal_node_type *first = node_allocator.allocate(1);
      std::construct_at(first, other_node->data, nullptr, nullptr, nullptr,
                        nullptr, nullptr);

      // ...walk the other tree to copy and track the tree copied...
      internal_node_type *next_other = other_node->first_child;
      internal_node_type *next_parent = first;
      internal_node_type *next_left_sibling = nullptr;

      // ...for every node to copy...
      while (next_other) {
        // ...allocate and in-place construct a node with this container's
        // allocator, the other node data value, and any left sibling or parent
        // pointers...
        internal_node_type *node = node_allocator.allocate(1);
        std::construct_at(node, next_other->data, nullptr, nullptr,
                          next_left_sibling, nullptr, next_parent);

        // ...reference any parent and left sibling to the new node...
        next_parent->last_child = node;
        if (next_left_sibling) {
          next_left_sibling->right_sibling = node;
        } else {
          next_parent->first_child = node;
        }

        // ...walk to the next other tree node to copy and walk and track the
        // copied tree alongside...
        next_parent = node;
        next_left_sibling = nullptr;
        if (next_other->first_child) {
          next_other = next_other->first_child;
        } else {
          // ...going back to the next ancestor sibling and tracking as
          // necessary.
          while (next_other) {
            if (next_other->right_sibling) {
              next_other = next_other->right_sibling;
              break;
            }
            next_other = next_other->parent;
            next_parent = next_parent->parent;
            next_left_sibling = next_parent->last_child;
          }
        }
      };

      return first;
    }

    return nullptr;
  }

  //! @}

  //! @name Private Member Variables
  //! @{

  internal_node_allocator_type node_allocator{};

  //! @brief The root node of the container.
  internal_node_type *root = nullptr;

  //! @brief The number of elements in the container.
  size_type node_count = 0;

  //! @}
};

//! @name Type Aliases
//! @{

template <class AllocatorType = std::allocator<bool>>
using tree_bool = tree<bool, AllocatorType>;
template <class AllocatorType = std::allocator<char>>
using tree_char = tree<char, AllocatorType>;
template <class AllocatorType = std::allocator<signed char>>
using tree_schar = tree<signed char, AllocatorType>;
template <class AllocatorType = std::allocator<unsigned char>>
using tree_uchar = tree<unsigned char, AllocatorType>;
template <class AllocatorType = std::allocator<int>>
using tree_int = tree<int, AllocatorType>;
template <class AllocatorType = std::allocator<unsigned int>>
using tree_uint = tree<unsigned int, AllocatorType>;
template <class AllocatorType = std::allocator<char8_t>>
using tree_char8_t = tree<char8_t, AllocatorType>;
template <class AllocatorType = std::allocator<char16_t>>
using tree_char16_t = tree<char16_t, AllocatorType>;
template <class AllocatorType = std::allocator<char32_t>>
using tree_char32_t = tree<char32_t, AllocatorType>;
template <class AllocatorType = std::allocator<wchar_t>>
using tree_wchar_t = tree<wchar_t, AllocatorType>;
template <class AllocatorType = std::allocator<std::int8_t>>
using tree_int8_t = tree<std::int8_t, AllocatorType>;
template <class AllocatorType = std::allocator<std::uint8_t>>
using tree_uint8_t = tree<std::uint8_t, AllocatorType>;
template <class AllocatorType = std::allocator<std::int16_t>>
using tree_int16_t = tree<std::int16_t, AllocatorType>;
template <class AllocatorType = std::allocator<std::uint16_t>>
using tree_uint16_t = tree<std::uint16_t, AllocatorType>;
template <class AllocatorType = std::allocator<std::int32_t>>
using tree_int32_t = tree<std::int32_t, AllocatorType>;
template <class AllocatorType = std::allocator<std::uint32_t>>
using tree_uint32_t = tree<std::uint32_t, AllocatorType>;
template <class AllocatorType = std::allocator<std::int64_t>>
using tree_int64_t = tree<std::int64_t, AllocatorType>;
template <class AllocatorType = std::allocator<std::uint64_t>>
using tree_uint64_t = tree<std::uint64_t, AllocatorType>;
template <class AllocatorType = std::allocator<std::int_least8_t>>
using tree_int_least8_t = tree<std::int_least8_t, AllocatorType>;
template <class AllocatorType = std::allocator<std::uint_least8_t>>
using tree_uint_least8_t = tree<std::uint_least8_t, AllocatorType>;
template <class AllocatorType = std::allocator<std::int_least16_t>>
using tree_int_least16_t = tree<std::int_least16_t, AllocatorType>;
template <class AllocatorType = std::allocator<std::uint_least16_t>>
using tree_uint_least16_t = tree<std::uint_least16_t, AllocatorType>;
template <class AllocatorType = std::allocator<std::int_least32_t>>
using tree_int_least32_t = tree<std::int_least32_t, AllocatorType>;
template <class AllocatorType = std::allocator<std::uint_least32_t>>
using tree_uint_least32_t = tree<std::uint_least32_t, AllocatorType>;
template <class AllocatorType = std::allocator<std::int_least64_t>>
using tree_int_least64_t = tree<std::int_least64_t, AllocatorType>;
template <class AllocatorType = std::allocator<std::uint_least64_t>>
using tree_uint_least64_t = tree<std::uint_least64_t, AllocatorType>;
template <class AllocatorType = std::allocator<std::int_fast8_t>>
using tree_int_fast8_t = tree<std::int_fast8_t, AllocatorType>;
template <class AllocatorType = std::allocator<std::uint_fast8_t>>
using tree_uint_fast8_t = tree<std::uint_fast8_t, AllocatorType>;
template <class AllocatorType = std::allocator<std::int_fast16_t>>
using tree_int_fast16_t = tree<std::int_fast16_t, AllocatorType>;
template <class AllocatorType = std::allocator<std::uint_fast16_t>>
using tree_uint_fast16_t = tree<std::uint_fast16_t, AllocatorType>;
template <class AllocatorType = std::allocator<std::int_fast32_t>>
using tree_int_fast32_t = tree<std::int_fast32_t, AllocatorType>;
template <class AllocatorType = std::allocator<std::uint_fast32_t>>
using tree_uint_fast32_t = tree<std::uint_fast32_t, AllocatorType>;
template <class AllocatorType = std::allocator<std::int_fast64_t>>
using tree_int_fast64_t = tree<std::int_fast64_t, AllocatorType>;
template <class AllocatorType = std::allocator<std::uint_fast64_t>>
using tree_uint_fast64_t = tree<std::uint_fast64_t, AllocatorType>;
template <class AllocatorType = std::allocator<std::intptr_t>>
using tree_intptr_t = tree<std::intptr_t, AllocatorType>;
template <class AllocatorType = std::allocator<std::uintptr_t>>
using tree_uintptr_t = tree<std::uintptr_t, AllocatorType>;
template <class AllocatorType = std::allocator<std::size_t>>
using tree_size_t = tree<std::size_t, AllocatorType>;
template <class AllocatorType = std::allocator<std::ptrdiff_t>>
using tree_ptrdiff_t = tree<std::ptrdiff_t, AllocatorType>;
template <class AllocatorType = std::allocator<std::intmax_t>>
using tree_intmax_t = tree<std::intmax_t, AllocatorType>;
template <class AllocatorType = std::allocator<std::uintmax_t>>
using tree_uintmax_t = tree<std::uintmax_t, AllocatorType>;
template <class AllocatorType = std::allocator<std::string>>
using tree_string = tree<std::string, AllocatorType>;
template <class AllocatorType = std::allocator<std::u8string>>
using tree_u8string = tree<std::u8string, AllocatorType>;
template <class AllocatorType = std::allocator<std::u16string>>
using tree_u16string = tree<std::u16string, AllocatorType>;
template <class AllocatorType = std::allocator<std::u32string>>
using tree_u32string = tree<std::u32string, AllocatorType>;
template <class AllocatorType = std::allocator<std::wstring>>
using tree_wstring = tree<std::wstring, AllocatorType>;

//! @}

} // namespace fcarouge

//! @brief Compares the contents of two containers.
//!
//! @details Checks if the contents of `lhs` and `rhs` are equal, that is, they
//! have the same number of elements and each element in `lhs` compares equal
//! with the element in `rhs` at the same position. `Type` must meet the
//! requirements of EqualityComparable in order to use operator.
//!
//! @param lhs Tree whose contents to compare.
//! @param rhs Tree whose contents to compare.
//!
//! @return `true` if the contents of the vectors are equal, `false` otherwise.
//!
//! @complexity Linear in the size of the container. Constant if the size of the
//! compared containers are different, linear otherwise.
template <class Type, class AllocatorType>
[[nodiscard]] constexpr bool
operator==(const fcarouge::tree<Type, AllocatorType> &lhs,
           const fcarouge::tree<Type, AllocatorType> &rhs)
{
  return lhs.size() == rhs.size();
}

//! @brief Compares the contents of two containers.
//!
//! @details Compares the contents of `lhs` and `rhs` lexicographically. The
//! comparison is performed as if by calling
//! `std::lexicographical_compare_three_way` on two containers with a function
//! object performing synthesized three-way comparison. The return type is the
//! same as the result type of synthesized three-way comparison. Given two
//! `const E` lvalues `lhs` and `rhs` as left hand operand and right hand
//! operand respectively (where `E` is `Type`), synthesized three-way comparison
//! is defined as: if `std::three_way_comparable_with<E, E>` is satisfied,
//! equivalent to `lhs <=> rhs;` otherwise, if comparing two constant `E`
//! lvalues by `operator<` is well-formed and the result type satisfies
//! boolean-testable, equivalent to `lhs < rhs ? std::weak_ordering::less : rhs
//! < lhs ? std::weak_ordering::greater : std::weak_ordering::equivalent`
//! otherwise, synthesized three-way comparison is not defined, and
//! `operator<=>` does not participate in overload resolution. The behavior of
//! `operator<=>` is undefined if `three_way_comparable_with` or
//! boolean-testable is satisfied but not modeled, or `operator<` is used but
//! `E` and `<` do not establish total order.
//!
//! @param lhs Tree whose contents to compare.
//! @param rhs Tree whose contents to compare.
//!
//! @return `std::strong_ordering::less` if the contents of the `lhs` are
//! lexicographically less than the contents of `rhs`;
//! `std::strong_ordering::greater` if the contents of the `lhs` are
//! lexicographically greater than the contents of `rhs`;
//! `std::partial_ordering::unordered` if the first pair of non-equivalent
//! elements in `lhs` and `rhs` are unordered; `std::strong::equal` otherwise.
//!
//! @complexity Linear in the size of the container.
template <class Type, class AllocatorType>
[[nodiscard]] constexpr auto
operator<=>(const fcarouge::tree<Type, AllocatorType> &lhs,
            const fcarouge::tree<Type, AllocatorType> &rhs);

//! @brief Inserts a human-interpretable representation of a tree into a
//! character stream.
//!
//! @details The insertion operator writes the tree to the character stream as
//! if by repeatedly writing the node value using the string
//! FormattedOutputFunction corresponding to the value type conversion for that
//! stream character type, traits, and currently-imbued locale. The tree is
//! written to the stream in the order of the nodes. The values are indented
//! according to the depth of their nodes. The tree topology is symbolized via
//! the `├──`, `└──`, and `│` characters.
//!
//! @tparam CharType The type of the character of the stream.
//! @tparam Traits The character type operations specification class.
//! @tparam Type The type of the contained data in the tree elements.
//! @tparam AllocatorType The type of the allocator for the nodes of the tree
//! elements.
//!
//! @param output_stream The character stream to write to.
//! @param tree The tree to be written.
//!
//! @return The character stream `output_stream` that was operated on.
template <class CharType, class Traits, class Type, class AllocatorType>
std::basic_ostream<CharType, Traits> &
operator<<(std::basic_ostream<CharType, Traits> &output_stream,
           const fcarouge::tree<Type, AllocatorType> &tree)
{
  // If there is a root...
  if (const auto *root = tree.begin().node) {
    // ...insert the root's representation in the stream...
    output_stream << root->data;
    output_stream.put(output_stream.widen('\n'));

    // ...by using a character queue to contain the indented topology, growing,
    // shrinking, while walking the tree...
    using margin_allocator_type = typename std::allocator_traits<
        AllocatorType>::template rebind_alloc<char>;
    std::basic_string<CharType, Traits, margin_allocator_type> margin{ "    " };

    auto pop4_utf8 = [&margin]() {
      for (auto character_count = 4; character_count--;) {
        if (!margin.empty()) {
          constexpr unsigned char utf8_mask = 0xC0u;
          constexpr unsigned char utf8_point = 0x80u;
          while (!((static_cast<unsigned char>(margin.back()) & utf8_mask) !=
                   utf8_point)) {
            margin.pop_back();
          }
          margin.pop_back();
        }
      }
    };

    const auto *next = root->first_child;

    // ...for every node to insert its representation...
    while (const auto *current = next) {
      pop4_utf8();
      if (current->right_sibling) {
        margin.append("├── ");
      } else {
        margin.append("└── ");
      }
      // ...insert the node's representation in the stream...
      output_stream << margin.c_str() << current->data;
      output_stream.put(output_stream.widen('\n'));
      // ...move onto the next node...
      if (current->first_child) {
        pop4_utf8();
        if (current->right_sibling) {
          margin.append("│       ");
        } else {
          margin.append("        ");
        }
        next = current->first_child;
      } else if (current->right_sibling) {
        next = current->right_sibling;
      } else {
        // ...going back to the next ancestor sibling and poping characters from
        // the topology margin as necessary.
        while (next) {
          if (next->right_sibling) {
            next = next->right_sibling;
            break;
          }
          pop4_utf8();
          next = next->parent;
        }
      }
    };
  }

  return output_stream;
}

#endif // FCAROUGE_TREE_HPP
