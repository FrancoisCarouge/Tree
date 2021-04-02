# Tree for C++

Tree data structure for C++: generic non-linear non-associative unordered recursively referenced collection of nodes, each containing a value.

- [Tree for C++](#tree-for-c)
  - [Information Tree](#information-tree)
  - [Use Cases](#use-cases)
  - [Example](#example)
  - [File include/fcarouge/tree.hpp](#file-includefcarougetreehpp)
    - [Includes](#includes)
    - [Namespaces](#namespaces)
    - [Classes](#classes)
  - [File include/fcarouge/tree_fwd.hpp](#file-includefcarougetree_fwdhpp)
    - [Type Aliases](#type-aliases)
  - [File include/fcarouge/tree_algorithm.hpp](#file-includefcarougetree_algorithmhpp)
    - [Observing Operations](#observing-operations)
  - [Class fcarouge::tree](#class-fcarougetree)
    - [Template Parameters](#template-parameters)
    - [Member Types](#member-types)
    - [Member Functions](#member-functions)
      - [Element Access](#element-access)
      - [Iterators](#iterators)
      - [Capacity](#capacity)
      - [Modifiers](#modifiers)
  - [Hard Lessons Learned](#hard-lessons-learned)
  - [License](#license)

## Information Tree

| Information Leaf | Value |
| --- | --- |
| Code | [![Code Repository](https://img.shields.io/badge/Repository-GitHub%20%F0%9F%94%97-brightgreen)](https://github.com/FrancoisCarouge/Tree) |
| Documentation | [![Doxygen Documentation](https://img.shields.io/badge/Documentation-GitHub%20Pages%20%F0%9F%94%97-brightgreen)](https://francoiscarouge.github.io/Tree/) |
| Licensing | [![MIT License](https://img.shields.io/badge/License-MIT%20%F0%9F%94%97-brightgreen)](https://raw.githubusercontent.com/francoiscarouge/tree/develop/LICENSE.txt) |
| Tests Coverage | [![Coverage Status](https://coveralls.io/repos/github/FrancoisCarouge/Tree/badge.svg?branch=develop)](https://coveralls.io/github/FrancoisCarouge/Tree?branch=develop) |
| Continuous Integration | [![Test Code Style: ClangFormat](https://github.com/FrancoisCarouge/Tree/workflows/Test%20Code%20Style:%20ClangFormat/badge.svg)](https://github.com/FrancoisCarouge/Tree/actions?query=workflow%3A%22Test+Code+Style%3A+ClangFormat%22+branch%3Adevelop) <br>[![Test Documentation: Doxygen](https://github.com/FrancoisCarouge/Tree/workflows/Test%20Documentation:%20Doxygen/badge.svg)](https://github.com/FrancoisCarouge/Tree/actions?query=workflow%3A%22Test+Documentation%3A+Doxygen%22+branch%3Adevelop) <br>[![Test Static Analysis: ClangTidy](https://github.com/FrancoisCarouge/Tree/workflows/Test%20Static%20Analysis:%20ClangTidy/badge.svg)](https://github.com/FrancoisCarouge/Tree/actions?query=workflow%3A%22Test+Static+Analysis%3A+ClangTidy%22+branch%3Adevelop) <br>[![Test Static Analysis: CppCheck](https://github.com/FrancoisCarouge/Tree/workflows/Test%20Static%20Analysis:%20CppCheck/badge.svg)](https://github.com/FrancoisCarouge/Tree/actions?query=workflow%3A%22Test+Static+Analysis%3A+CppCheck%22+branch%3Adevelop) <br>[![Test: Ubuntu 20.04 GCC 10](https://github.com/FrancoisCarouge/Tree/workflows/Test:%20Ubuntu%2020.04%20GCC%2010/badge.svg)](https://github.com/FrancoisCarouge/Tree/actions?query=workflow%3A%22Test%3A+Ubuntu+20.04+GCC+10%22+branch%3Adevelop) <br>[![Test Memory: Valgrind](https://github.com/FrancoisCarouge/Tree/workflows/Test%20Memory:%20Valgrind/badge.svg)](https://github.com/FrancoisCarouge/Tree/actions?query=workflow%3A%22Test+Memory%3A+Valgrind%22+branch%3Adevelop) <br>[![Test Address: Sanitizer](https://github.com/FrancoisCarouge/Tree/workflows/Test%20Address:%20Sanitizer/badge.svg)](https://github.com/FrancoisCarouge/Tree/actions?query=workflow%3A%22Test+Address%3A+Sanitizer%22+branch%3Adevelop) <br>[![Test Leak: Sanitizer](https://github.com/FrancoisCarouge/Tree/workflows/Test%20Leak:%20Sanitizer/badge.svg)](https://github.com/FrancoisCarouge/Tree/actions?query=workflow%3A%22Test+Leak%3A+Sanitizer%22+branch%3Adevelop) <br>[![Test Thread: Sanitizer](https://github.com/FrancoisCarouge/Tree/workflows/Test%20Thread:%20Sanitizer/badge.svg)](https://github.com/FrancoisCarouge/Tree/actions?query=workflow%3A%22Test+Thread%3A+Sanitizer%22+branch%3Adevelop) <br>[![Test Undefined Behavior: Sanitizer](https://github.com/FrancoisCarouge/Tree/workflows/Test%20Undefined%20Behavior:%20Sanitizer/badge.svg)](https://github.com/FrancoisCarouge/Tree/actions?query=workflow%3A%22Test+Undefined+Behavior%3A+Sanitizer%22+branch%3Adevelop) <br>[![Deploy Documentation: Doxygen GitHub Pages](https://github.com/FrancoisCarouge/Tree/workflows/Deploy%20Documentation:%20Doxygen%20GitHub%20Pages/badge.svg)](https://github.com/FrancoisCarouge/Tree/actions?query=workflow%3A%22Deploy+Documentation%3A+Doxygen+GitHub+Pages%22) <br>[![Deploy Code Coverage: Coveralls](https://github.com/FrancoisCarouge/Tree/workflows/Deploy%20Code%20Coverage:%20Coveralls/badge.svg)](https://github.com/FrancoisCarouge/Tree/actions?query=workflow%3A%22Deploy+Code+Coverage%3A+Coveralls%22) <br>[![FOSSA Status](https://app.fossa.com/api/projects/git%2Bgithub.com%2FFrancoisCarouge%2FTree.svg?type=shield)](https://app.fossa.com/projects/git%2Bgithub.com%2FFrancoisCarouge%2FTree?ref=badge_shield) |
| Report and Participate | [![GitHub Issues](https://img.shields.io/github/issues-raw/francoiscarouge/tree)](https://github.com/francoiscarouge/tree/issues) |
| Best Practices | [![CII Best Practices](https://bestpractices.coreinfrastructure.org/projects/4221/badge)](https://bestpractices.coreinfrastructure.org/projects/4221) |
| Support Open Free Software | [![Sponsor](https://img.shields.io/badge/Sponsor-%EF%BC%84%EF%BC%84%EF%BC%84%20%F0%9F%94%97-brightgreen)](http://paypal.me/francoiscarouge) |

## Use Cases

**Sometimes all you need is this tree...**

- to represent, store, walk, manipulate, and search some **hierarchical** information with the purpose of deciding, routing, sorting, or composing results,

**...but often you really don't!**

- when one of the standard associative containers do better: `std::unordered_map`, `std::unordered_set`, `std::unordered_multimap`, `std::unordered_multiset`, or
- when one of the standard sorted associative containers do better: `std::map`, `std::set`, `std::multi_map`, `std::multi_set`, or
- when one of the many algorithms, parsers do better, or
- when one of the [100+](https://en.wikipedia.org/wiki/Category:Trees_(data_structures)) other trees do better: binary, ternary, m-ary, k-ary, red-black, k-d, B, B+ trees!

## Example

`main.cpp`
```cpp
#include "fcarouge/tree.hpp"
// fcarouge::tree

#include <iostream>
// std::cout std::endl

int main(int, char **)
{
  // Declare a "greeting" variable as a tree of aliased standard strings.
  fcarouge::tree_string greeting;

  // Push at the front of the tree a root element with string value "Hello".
  const auto root = greeting.emplace(greeting.begin(), "Hello");

  // Push in an element with value "," as a child of the sole node.
  greeting.push(root, ",");

  // Push in another element with value "!" and keep its iterator "bang".
  const auto bang = greeting.push(root, "!");

  // Insert a left sibling of iterator "bang" with value "World".
  greeting.emplace(bang, "World");

  // Print out the contents of the container.
  std::cout << greeting << std::endl;

  return 0;
}
```

Output:
```
Hello
├── ,
├── World
└── !
```

## File include/fcarouge/tree.hpp

### Includes

| Include | Definition |
| --- | --- |
| `<cstddef>` | Standard size and pointer difference types support. |
| `<cstdint>` | Standard fixed width integer types support. |
| `<iterator>` | Standard input iterator tag support. |
| `<limits>` | Standard fundamental numeric types properties support. |
| `<memory>` | Standard construction, allocation, and addressing support. |
| `<ostream>` | Standard output stream support. |
| `<string>` | Standard string support. |
| `<type_traits>` | Standard type traits support. |
| `<utility>` | Standard moving and forwarding resources support. |

### Namespaces

| Namespace | Definition |
| --- | --- |
| `fcarouge` | François Carouge's projects namespace. |

### Classes

| Class | Definition |
| --- | --- |
| `tree` | Generic non-linear non-associative unordered recursively referenced collection of nodes, each containing a value. |

## File include/fcarouge/tree_fwd.hpp

Minimal forward declaration header.

- forward declares the `tree` class, and
- defines its common type aliases, and
- includes its minimum necessary standard library dependencies.

### Type Aliases

Type aliases are provided for a variety of fundamental and standard types, in the `fcarouge` namespace, without specialization of the allocator type, as follows:

| Alias | Definition |
| --- | --- |
| `tree_bool` | `tree<bool>` |
| `tree_char` | `tree<char>` |
| `tree_schar` | `tree<signed char>` |
| `tree_uchar` | `tree<unsigned char>` |
| `tree_int` | `tree<int>` |
| `tree_uint` | `tree<unsigned int>` |
| `tree_char8_t` | `tree<char8_t>` |
| `tree_char16_t` | `tree<char16_t>` |
| `tree_char32_t` | `tree<char32_t>` |
| `tree_wchar_t` | `tree<wchar_t>` |
| `tree_int8_t` | `tree<std::int8_t>` |
| `tree_uint8_t` | `tree<std::uint8_t>` |
| `tree_int16_t` | `tree<std::int16_t>` |
| `tree_uint16_t` | `tree<std::uint16_t>` |
| `tree_int32_t` | `tree<std::int32_t>` |
| `tree_uint32_t` | `tree<std::uint32_t>` |
| `tree_int64_t` | `tree<std::int64_t>` |
| `tree_uint64_t` | `tree<std::uint64_t>` |
| `tree_int_least8_t` | `tree<std::int_least8_t>` |
| `tree_uint_least8_t` | `tree<std::uint_least8_t>` |
| `tree_int_least16_t` | `tree<std::int_least16_t>` |
| `tree_uint_least16_t` | `tree<std::uint_least16_t>` |
| `tree_int_least32_t` | `tree<std::int_least32_t>` |
| `tree_uint_least32_t` | `tree<std::uint_least32_t>` |
| `tree_int_least64_t` | `tree<std::int_least64_t>` |
| `tree_uint_least64_t` | `tree<std::uint_least64_t>` |
| `tree_int_fast8_t` | `tree<std::int_fast8_t>` |
| `tree_uint_fast8_t` | `tree<std::uint_fast8_t>` |
| `tree_int_fast16_t` | `tree<std::int_fast16_t>` |
| `tree_uint_fast16_t` | `tree<std::uint_fast16_t>` |
| `tree_int_fast32_t` | `tree<std::int_fast32_t>` |
| `tree_uint_fast32_t` | `tree<std::uint_fast32_t>` |
| `tree_int_fast64_t` | `tree<std::int_fast64_t>` |
| `tree_uint_fast64_t` | `tree<std::uint_fast64_t>` |
| `tree_intptr_t` | `tree<std::intptr_t>` |
| `tree_uintptr_t` | `tree<std::uintptr_t>` |
| `tree_size_t` | `tree<std::size_t>` |
| `tree_ptrdiff_t` | `tree<std::ptrdiff_t>` |
| `tree_intmax_t` | `tree<std::intmax_t>` |
| `tree_uintmax_t` | `tree<std::uintmax_t>` |
| `tree_string` | `tree<std::string>` |
| `tree_u8string` | `tree<std::u8string>` |
| `tree_u16string` | `tree<std::u16string>` |
| `tree_u32string` | `tree<std::u32string>` |
| `tree_wstring` | `tree<std::wstring>` |

## File include/fcarouge/tree_algorithm.hpp

### Observing Operations

| Observing Operation | Definition |
| --- | --- |
| `depth` | Depth of the path from the root, top element to the iterated node. |

## Class fcarouge::tree

Defined in header [fcarouge/tree.hpp](include/fcarouge/tree.hpp)

```
template <
    class Type,
    class AllocatorType = std::allocator<Type>
> class tree
```

The `fcarouge::tree` type is a hierarchical tree data structure. The container is:
- generic with respect to the type of stored values and allocator as template parameters,
- non-linear compared to arrays, linked lists, stacks, and queues as a node may lead to multiple nodes,
- non-associative compared to maps and sets as values are not keyed,
- unordered since internally, the elements are not sorted or maintained in any particular order but externally, the insertion order is upheld,
- recursive in its facade exposing a recursively referenced collection of nodes, each containing a value,
- standard layout class type which may help with memory and cross language communication,
- unspecified iteration order except that each element is visited only once,
- implemented operations without recursive calls to guarantee a constant stack usage limit,
- compile time evaluation compatible,
- employing generational C++ features advantageously up to C++20 standard,
- separating algorithmic from container concerns,
- influenced by the Standard Template Library (STL) principles and the C++ Core Guidelines in its design tradeoffs,
- intelligibly documented for the wider audience.

### Template Parameters

| Template Parameter | Definition |
| --- | --- |
| `Type` | The type of the contained data elements. |
| `AllocatorType` | An allocator that is used to acquire/release memory and to construct/destroy the elements in that memory. |

### Member Types

| Member Type | Definition |
| --- | --- |
| `value_type` | The type of the contained data elements. |
| `allocator_type` | The type of the allocator for all memory allocations of this container. |
| `size_type` | The unsigned integer type to represent element counts. |
| `difference_type` | The signed integer type to represent element distances. |
| `reference` | The reference type of the contained data elements. |
| `const_reference` | The constant reference type of the contained data elements. |
| `pointer` | The pointer type of the contained data elements. |
| `const_pointer` | The constant pointer type of the contained data elements. |
| `iterator` | The type to identify and traverse the elements of the container. |
| `const_iterator` | The constant type to identify and traverse the elements of the container. |

### Member Functions

| Member Function | Definition |
| --- | --- |
| `(constructor)` | Constructs the container. |
| `(destructor)` | Destructs the container. |
| `operator=` | Assigns values to the container. |
| `assign` | Assigns values to the container. |
| `get_allocator` | Returns the allocator associated with the container. |

#### Element Access

| Element Access | Definition |
| --- | --- |
| `front` | Returns a reference to the first element in the container. |

#### Iterators

| Iterator | Definition |
| --- | --- |
| `begin` <br>`cbegin` | Returns an iterator to the first element of the container. |
| `end` <br>`cend` | Returns an iterator to the element following the last element of the container. |

#### Capacity

| Capacity | Definition |
| --- | --- |
| `empty` | Checks if the container has no elements. |
| `size` | Returns the number of elements in the container. |
| `max_size` | Returns the maximum number of elements the container is able to hold. |

#### Modifiers

| Modifier | Definition |
| --- | --- |
| `clear` | Erases all elements from the container. |
| `insert` | Inserts a new element into the container directly before the position iterator as the new left sibling. |
| `emplace_front` | Inserts a new element into the container constructed in-place directly before the root beginning. |
| `emplace` | Inserts a new element into the container constructed in-place directly before the position iterator as the new left sibling. |
| `erase` | Prunes the specified element including its sub-tree. |
| `push` | Inserts the given element value into the container directly after the last child of the position iterator as the new last child. |
| `push_front` | Prepends the given element to the beginning of the container. |
| `swap` | Exchanges the contents of this container with those of the other container. |

## Hard Lessons Learned

- Recursive code **will** run out of stack space. No matter the architecture, for a generic data structure that cannot guarantee depth by design. Refactor to iterative code.

## License

<img align="right" src="http://opensource.org/trademarks/opensource/OSI-Approved-License-100x137.png">

Tree for C++ is licensed under the [MIT License](http://opensource.org/licenses/MIT):

Copyright &copy; 2020 François Carouge

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
