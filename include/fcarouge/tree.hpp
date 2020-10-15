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

#include <iterator>
// std::input_iterator_tag

#include <memory>
// std::addressof std::allocator std::allocator_traits
// std::construct_at std::destroy_at

#include <utility>
// std::forward std::move

//! @namespace fcarouge Francois Carouge's projects namespace. Lowers the name
//! conflict probability in large projects. Use using-declarations or
//! namespace-alias-definition per your project guidelines.
namespace fcarouge
{
//! @brief A tree data structure for C++.
//!
//! @details The fcarouge::tree type is a hierarchical tree data structure.
//! The container is a non-linear non-associative unordered recursively
//! referenced collection of nodes, each containing a value. The design
//! tradeoffs are influenced by the Standard Template Library (STL) principles
//! and the C++ Core Guidelines. The container is a standard layout class type
//! which may help with memory and cross language communication. The iteration
//! order of the standard iterator is unspecified, except that each element is
//! visited only once.
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

  //! @brief The const pointer type of the contained data elements.
  using const_pointer =
      typename std::allocator_traits<AllocatorType>::const_pointer;

  //! @}

  private:
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

    //! @brief Find the nearest right sibling of itself or ancestor.
    //!
    //! @details Recursively walks the tree.
    //!
    //! @return The pointer to the nearest right sibling of itself or ancestor;
    //! or `nullptr` if such a node doesn't exist.
    [[nodiscard]] constexpr internal_node_type *next_ancestor_sibling() noexcept
    {
      if (right_sibling) {
        return right_sibling;
      }

      if (parent) {
        return parent->next_ancestor_sibling();
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

  //! @brief Type to identify and traverse the elements of the container.
  struct internal_iterator_type {
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

    //! @name Public Iterator Member Functions
    //! @{

    //! @brief Dereferences the iterator to obtain the stored value. The
    //! behavior is undefined if the iterator is invalid.
    //!
    //! @return Reference to the element if the iterator is dereferencable.
    [[nodiscard]] constexpr reference operator*() const noexcept
    {
      return node->data;
    }

    //! @brief Increments the iterator.
    //!
    //! @return Reference to the next iterator.
    constexpr internal_iterator_type &operator++() noexcept
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
    operator==(const internal_iterator_type &other) const noexcept = default;

    //! @name Public Member Variables
    //! @{

    //! @brief The pointer to the node.
    internal_node_type *node = nullptr;

    //! @}
  };

  //! @brief Type to identify and traverse the constant elements of the
  //! container.
  struct internal_const_iterator_type {
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

    //! @name Public Iterator Member Functions
    //! @{

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
    constexpr internal_const_iterator_type(
        const internal_iterator_type &iterator)
            : node{ iterator.node }
    {
    }

    //! @brief Dereferences the iterator to obtain the stored value. The
    //! behavior is undefined if the iterator is invalid.
    //!
    //! @return Reference to the element if the iterator is dereferencable.
    [[nodiscard]] constexpr reference operator*() const noexcept
    {
      return node->data;
    }

    //! @brief Increments the iterator.
    //!
    //! @return Reference to the next iterator.
    constexpr internal_const_iterator_type &operator++() noexcept
    {
      if (node->first_child) {
        node = node->first_child;
      } else {
        node = node->next_ancestor_sibling();
      }

      return *this;
    }

    //! @}

    //! @name Public Member Functions
    //! @{

    //! @brief Implicit node pointer to constant iterator conversion.
    //!
    //! @details Aggregate initialization is not available per implicit iterator
    //! conversion construction. The node pointer type is implicitely
    //! convertible to the constant iterator type to allow list initialization.
    constexpr internal_const_iterator_type(internal_node_type *node)
            : node{ node }
    {
    }

    //! @}

    [[nodiscard]] constexpr bool operator==(
        const internal_const_iterator_type &other) const noexcept = default;

    //! @name Public Member Variables
    //! @{

    //! @brief The pointer to the node.
    internal_node_type *node = nullptr;

    //! @}
  };

  public:
  //! @name Public Member Types
  //! @{

  //! @brief Type to identify and traverse the elements of the container.
  //!
  //! @details The iteration order of the standard iterator is unspecified,
  //! except that each element is visited only once.
  using iterator = internal_iterator_type;

  //! @brief Constant type to identify and traverse the elements of the
  //! container.
  //!
  //! @details The iteration order of the standard constant iterator is
  //! unspecified, except that each element is visited only once.
  using const_iterator = internal_const_iterator_type;

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
  constexpr explicit tree(const AllocatorType &allocator)
          : node_allocator{ allocator }
  {
  }

  //! @brief Copy constructor.
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
                                    other.get_allocator()) }
  {
  }

  //! @brief Allocator-extended copy constructor.
  //!
  //! @details Constructs the container with the copy of the contents of the
  //! `other` container.
  //!
  //! @param other Another container to be used as source to initialize the
  //! elements of the container with.
  //! @param allocator Allocator to use for all memory allocations of this
  //! container.
  //!
  //! @complexity Linear in size of the other container.
  constexpr tree(const tree &other, const AllocatorType &allocator);

  //! @brief Move constructor.
  //!
  //! @details Constructs the container with the contents of the `other`
  //! container using move semantics (i.e. the data in `other` container is
  //! moved from the other into this container). The allocator is obtained by
  //! move-construction from the allocator belonging to other.
  //!
  //! @param other Another container to be used as source to initialize the
  //! elements of the container with.
  //!
  //! @complexity Constant.
  constexpr tree(tree &&other) noexcept
          : node_allocator{ std::move(other.node_allocator) },
            root{ other.root }, last{ other.last }, node_count{
              other.node_count
            }
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
  constexpr tree(tree &&other, const AllocatorType &allocator) noexcept;

  //! @brief Constructs the container with by copying the value for its root.
  //!
  //! @param value The value to initialize elements of the container with.
  //!
  //! @complexity Constant.
  constexpr explicit tree(const_reference value)
          : root{ node_allocator.allocate(1) }, last{ root }, node_count{ 1 }
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
  constexpr tree(const_reference value, const AllocatorType &allocator);

  //! @brief Constructs the container by moving the value for its root.
  //!
  //! @param value The value to initialize elements of the container with.
  //!
  //! @complexity Constant.
  constexpr explicit tree(value_type &&value)
          : root{ node_allocator.allocate(1) }, last{ root }, node_count{ 1 }
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
            last{ root }, node_count{ 1 }
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
  //! of the other container.
  //!
  //! @param other Another container to be used as source to initialize the
  //! elements of the container with.
  //!
  //! @return The reference value of this implicit object container parameter,
  //! i.e. `*this`.
  //!
  //! @complexity Linear in the size of this and the other container.
  constexpr tree &operator=(const tree &other) noexcept;

  //! @brief Move assignment operator.
  //!
  //! @details Replaces the contents with those of the `other` container using
  //! move semantics (i.e. the data in `other` container is moved from the other
  //! into this container). The other container is in a valid but unspecified
  //! state afterwards. The allocator is obtained by move-construction from the
  //! allocator belonging to other. Self move assignement is valid, safe, and
  //! meet specifications.
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
  constexpr tree &operator=(tree &&other) noexcept(
      noexcept(this->node_allocator = std::move(other.node_allocator)))
  {
    if (this != std::addressof(other)) {
      node_allocator = std::move(other.node_allocator);
      root = other.root;
      last = other.last;
      node_count = other.node_count;
      other.root = nullptr;
    }
    return *this;
  }

  //! @brief Value copy assignment operator.
  //!
  //! @details Replaces the contents with a copy of the contents of the value
  //! for its root.
  //!
  //! @param value The value to initialize the container with.
  //!
  //! @return The reference value of this implicit object container parameter,
  //! i.e. `*this`.
  //!
  //! @complexity Linear in the size of this and the other container.
  constexpr tree &operator=(const_reference value) noexcept;

  //! @brief Value move assignment operator.
  //!
  //! @details Replaces the contents with those of the value using
  //! move semantics (i.e. the value data is moved into the root of this
  //! container). The value is in a valid but unspecified state afterwards.
  //!
  //! @param value The value to initialize the container with.
  //!
  //! @return The reference value of this implicit object container parameter,
  //! i.e. `*this`.
  //!
  //! @complexity Constant.
  constexpr tree &operator=(value_type &&value) noexcept;

  constexpr tree &assign(const tree &other) noexcept;

  constexpr tree &assign(tree &&other) noexcept;

  constexpr tree &assign(const_reference value) noexcept;

  constexpr tree &assign(value_type &&value) noexcept;

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
    return iterator{ root };
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
    return const_iterator{ root };
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
    return const_iterator{ root };
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
    return iterator{ nullptr };
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
    return const_iterator{ nullptr };
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
    return const_iterator{ nullptr };
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
  //! and end iterators for the largest container.
  //!
  //! @return Maximum number of elements.
  //!
  //! @complexity Constant.
  //!
  //! @note This value typically reflects the theoretical limit on the size of
  //! the container, at most `std:: numeric_limits<difference_type>:: max()`. At
  //! runtime, the size of the container may be limited to a value smaller
  //! than max_size() by the amount of RAM available.
  [[nodiscard]] constexpr size_type max_size() const noexcept;

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
  constexpr void clear() noexcept
  {
    axe(root);
    root = nullptr;
    last = nullptr;
    node_count = 0;
  }

  constexpr iterator insert(const_iterator position, const_reference value);

  constexpr iterator insert(const_iterator position, value_type &&value);

  template <class... ArgumentsType>
  constexpr reference emplace_front(ArgumentsType &&... arguments);

  //! @brief Inserts a new element into the container constructed in-place
  //! directly before the `position` iterator as the new left sibling.
  //!
  //! @details The element is constructed through
  //! `std::allocator_traits::construct`, which typically uses placement-new
  //! to construct the element in-place at a location provided by the
  //! container. The `arguments` are forwarded to the constructor as
  //! `std::forward<ArgumentsType>(arguments)...`. No iterators or references
  //! are invalidated. Inserts at the root position as the new root. Inserts
  //! before the beginning `begin()` position as the new root. Inserts before
  //! the ending `end()` position.
  //!
  //! @tparam ArgumentsType The argument types to forward to the constructor of
  //! the element.
  //!
  //! @param position The iterator before which the new element will be
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

    // Insert the new node...
    // ...before the position node...
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
      // ... as the sole, first, and last child of the previous last node.
      if (last) {
        std::construct_at(node, std::forward<ArgumentsType>(arguments)...,
                          nullptr, nullptr, nullptr, nullptr, last);
        last->first_child = node;
        last->last_child = node;
        last = node;
      }
      // ...as the sole, last, and root node.
      else {
        std::construct_at(node, std::forward<ArgumentsType>(arguments)...);
        root = node;
        last = node;
      }
    }

    ++node_count;
    return iterator{ node };
  }

  //! @brief Prune the specified element including its sub-tree.
  //!
  //! @details Remove the element at `position` and prune its associated
  //! sub-tree. References and iterators to the erased elements are invalidated.
  //! Other references and iterators are not affected. The iterator `position`
  //! must be valid and dereferenceable. Thus the `end()` iterator which is
  //! valid, but is not dereferenceable cannot be used as a value for
  //! `position`. The same is applicable for the `begin()` iterator on an empty
  //! container. The container's size is reduded by the number of elements
  //! removed, that is the node and all nodes in its sub-tree. If the erased
  //! node is the root, the tree is empty.
  //!
  //! @param position Iterator to the element to remove with its subtree.
  //!
  //! @return Iterator following the last removed element. If `position` refers
  //! to the last element, then the `end()` iterator is returned.
  constexpr iterator erase(iterator position)
  {
    // Identify the node following this subtree which will become the next node.
    iterator next{ position.node->next_ancestor_sibling() };

    // Orphan the node.
    if (position.node->parent) {
      if (position.node->parent->first_child == position.node) {
        position.node->parent->first_child = position.node->right_sibling;
      }
      if (position.node->parent->last_child == position.node) {
        position.node->parent->last_child = position.node->left_sibling;
      }
    }

    // Isolate the node from its siblings.
    if (position.node->left_sibling) {
      position.node->left_sibling->right_sibling = position.node->right_sibling;
      position.node->left_sibling = nullptr;
    }
    if (position.node->right_sibling) {
      position.node->right_sibling->left_sibling = position.node->left_sibling;
      position.node->right_sibling = nullptr;
    }

    if (position.node == root) {
      root = nullptr;
    }

    if (position.node == last) {
      last = nullptr;
    }

    prune(position.node);

    return next;
  }

  constexpr iterator erase(const_iterator position);

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
  //! @param position The parent node iterator for which the element will be
  //! inserted as the last child. The iterator may be the beginning `begin()` or
  //! ending `end()` iterator.
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
    return emplace_last_child(position, value);
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
  //! @param position The parent node iterator for which the element will be
  //! inserted as the last child. The iterator may be the beginning `begin()` or
  //! ending `end()` iterator.
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
    return emplace_last_child(position, std::move(value));
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
  //! @name Private Member Types
  //! @{

  //! Rebind the allocator for the container nodes.
  using internal_node_allocator_type = typename std::allocator_traits<
      AllocatorType>::template rebind_alloc<internal_node_type>;

  //! @}

  //! @name Private Modifier Member Functions
  //! @{

  //! @brief Prune the specified element including its sub-tree.
  //!
  //! @details Remove the element at `position` and prune its associated
  //! sub-tree. References and iterators to the erased elements are invalidated.
  //! Other references and iterators are not affected. The iterator `position`
  //! must be valid and dereferenceable. Thus the `end()` iterator which is
  //! valid, but is not dereferenceable cannot be used as a value for
  //! `position`. The same is applicable for the `begin()` iterator on an empty
  //! container. The container's size is reduded by the number of elements
  //! removed, that is the node and all nodes in its sub-tree. If the erased
  //! node is the root, the tree is empty.
  //!
  //! @param[in,out] node The element to erase pointer's reference, cleared to
  //! `nullptr` after destruction and deallocation of the node.
  constexpr void prune(internal_node_type *&node)
  {
    if (node) {
      prune(node->first_child);
      prune(node->right_sibling);

      std::destroy_at(node);
      node_allocator.deallocate(node, 1);

      --node_count;
    }
  }

  //! @brief Axe the specified element including its sub-tree.
  //!
  //! @details Remove the element at `position` and prune its associated
  //! sub-tree. References and iterators to the erased elements are invalidated.
  //! Other references and iterators are not affected. The iterator `position`
  //! must be valid and dereferenceable. Thus the `end()` iterator which is
  //! valid, but is not dereferenceable cannot be used as a value for
  //! `position`. The same is applicable for the `begin()` iterator on an empty
  //! container. The container's size is not maintained and no longer
  //! corresponds to the container content.
  //!
  //! @param[in,out] node The element to erase pointer's reference, cleared to
  //! `nullptr` after destruction and deallocation of the node.
  constexpr void axe(internal_node_type *&node)
  {
    if (node) {
      axe(node->first_child);
      axe(node->right_sibling);

      std::destroy_at(node);
      node_allocator.deallocate(node, 1);
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
  //! @param position The parent node iterator for which the element will be
  //! inserted as the last child. The iterator may be the beginning `begin()` or
  //! ending `end()` iterator.
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
  constexpr iterator emplace_last_child(const_iterator position,
                                        ArgumentsType &&... arguments)
  {
    // The allocated node is in-place construced and recorded in every
    // following statements.
    internal_node_type *node = node_allocator.allocate(1);

    // Insert the new node...
    // ...as the last child of the position node...
    if (internal_node_type *position_node = position.node) {
      std::construct_at(node, std::forward<ArgumentsType>(arguments)...,
                        nullptr, nullptr, position_node->last_child, nullptr,
                        position_node);
      position_node->last_child = node;
      // ...which was the last node...
      if (position_node == last) {
        last = node;
      }
      // ...with a left sibling node.
      if (node->left_sibling) {
        node->left_sibling->right_sibling = node;
        // ...which was the last node.
        if (node->left_sibling == last) {
          last = node;
        }
      }
      // ...without a left sibling node.
      else {
        position_node->first_child = node;
      }
    }
    // ...as the new last node...
    else {
      // ...as child of the previous last node.
      if (last) {
        std::construct_at(node, std::forward<ArgumentsType>(arguments)...,
                          nullptr, nullptr, nullptr, nullptr, last);
        last->first_child = node;
        last = node;
      }
      // ...as the sole, last, and root node.
      else {
        std::construct_at(node, std::forward<ArgumentsType>(arguments)...);
        root = node;
        last = node;
      }
    }

    ++node_count;

    return iterator{ node };
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
    // ...or as the sole, root, and last node in the container.
    else {
      last = node;
    }

    root = node;
    ++node_count;
  }

  //! @}

  //! @name Private Member Variables
  //! @{

  internal_node_allocator_type node_allocator{};

  //! @brief The root node of the container.
  internal_node_type *root = nullptr;

  //! @brief The last element in the container.
  internal_node_type *last = nullptr;

  //! @brief The number of elements in the container.
  size_type node_count = 0;

  //! @}
};

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
//! equivalent to `lhs <=> rhs;` otherwise, if comparing two const `E` lvalues
//! by `operator<` is well-formed and the result type satisfies
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

#endif // FCAROUGE_TREE_HPP
