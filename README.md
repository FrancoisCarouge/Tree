# Tree for C++

Tree data structure for C++: non-linear non-associative unordered recursively referenced collection of nodes, each containing a value.

## Information Tree

| Information Leaf | Value |
| --- | --- |
| Code | [![Code Repository](https://img.shields.io/badge/Repository-GitHub%20%F0%9F%94%97-brightgreen)](https://github.com/FrancoisCarouge/Tree) |
| Documentation | [![Doxygen Documentation](https://img.shields.io/badge/Documentation-GitHub%20Pages%20%F0%9F%94%97-brightgreen)](https://francoiscarouge.github.io/Tree/) |
| Licensing | [![MIT License](https://img.shields.io/badge/License-MIT%20%F0%9F%94%97-brightgreen)](https://raw.githubusercontent.com/francoiscarouge/tree/develop/LICENSE.txt) |
| Tests Coverage | [![Coverage Status](https://coveralls.io/repos/github/FrancoisCarouge/Tree/badge.svg?branch=develop)](https://coveralls.io/github/FrancoisCarouge/Tree?branch=develop) |
| Continuous Integration | [![Test Code Style: ClangFormat](https://github.com/FrancoisCarouge/Tree/workflows/Test%20Code%20Style:%20ClangFormat/badge.svg)](https://github.com/FrancoisCarouge/Tree/actions?query=workflow%3A%22Test+Code+Style%3A+ClangFormat%22+branch%3Adevelop) <br>[![Test Documentation: Doxygen](https://github.com/FrancoisCarouge/Tree/workflows/Test%20Documentation:%20Doxygen/badge.svg)](https://github.com/FrancoisCarouge/Tree/actions?query=workflow%3A%22Test+Documentation%3A+Doxygen%22+branch%3Adevelop) <br>[![Test Static Analysis: ClangTidy](https://github.com/FrancoisCarouge/Tree/workflows/Test%20Static%20Analysis:%20ClangTidy/badge.svg)](https://github.com/FrancoisCarouge/Tree/actions?query=workflow%3A%22Test+Static+Analysis%3A+ClangTidy%22+branch%3Adevelop) <br>[![Test Static Analysis: CppCheck](https://github.com/FrancoisCarouge/Tree/workflows/Test%20Static%20Analysis:%20CppCheck/badge.svg)](https://github.com/FrancoisCarouge/Tree/actions?query=workflow%3A%22Test+Static+Analysis%3A+CppCheck%22+branch%3Adevelop) <br>[![Test: Ubuntu 20.04 GCC 10](https://github.com/FrancoisCarouge/Tree/workflows/Test:%20Ubuntu%2020.04%20GCC%2010/badge.svg)](https://github.com/FrancoisCarouge/Tree/actions?query=workflow%3A%22Test%3A+Ubuntu+20.04+GCC+10%22+branch%3Adevelop) <br>[![Test Memory: Valgrind](https://github.com/FrancoisCarouge/Tree/workflows/Test%20Memory:%20Valgrind/badge.svg)](https://github.com/FrancoisCarouge/Tree/actions?query=workflow%3A%22Test+Memory%3A+Valgrind%22+branch%3Adevelop) <br>[![Test Address: AddressSanitizer](https://github.com/FrancoisCarouge/Tree/workflows/Test%20Address:%20AddressSanitizer/badge.svg)](https://github.com/FrancoisCarouge/Tree/actions?query=workflow%3A%22Test+Address%3A+AddressSanitizer%22+branch%3Adevelop) <br>[![Deploy Documentation: Doxygen GitHub Pages](https://github.com/FrancoisCarouge/Tree/workflows/Deploy%20Documentation:%20Doxygen%20GitHub%20Pages/badge.svg)](https://github.com/FrancoisCarouge/Tree/actions?query=workflow%3A%22Deploy+Documentation%3A+Doxygen+GitHub+Pages%22) <br>[![Deploy Code Coverage: Coveralls](https://github.com/FrancoisCarouge/Tree/workflows/Deploy%20Code%20Coverage:%20Coveralls/badge.svg)](https://github.com/FrancoisCarouge/Tree/actions?query=workflow%3A%22Deploy+Code+Coverage%3A+Coveralls%22) <br>[![FOSSA Status](https://app.fossa.com/api/projects/git%2Bgithub.com%2FFrancoisCarouge%2FTree.svg?type=shield)](https://app.fossa.com/projects/git%2Bgithub.com%2FFrancoisCarouge%2FTree?ref=badge_shield) |
| Report and Participate | [![GitHub Issues](https://img.shields.io/github/issues-raw/francoiscarouge/tree)](https://github.com/francoiscarouge/tree/issues) |
| Best Practices | [![CII Best Practices](https://bestpractices.coreinfrastructure.org/projects/4221/badge)](https://bestpractices.coreinfrastructure.org/projects/4221) |
| Support Open Free Software | [![Sponsor](https://img.shields.io/badge/Sponsor-%EF%BC%84%EF%BC%84%EF%BC%84%20%F0%9F%94%97-brightgreen)](http://paypal.me/francoiscarouge) |

## Sometimes all you need is this tree...

- to represent, store, walk, manipulate, and search some hierarchical information with the purpose of deciding, routing, sorting, or composing results.

### ...but often you really don't!

- when one of the standard associative containers do better: `std::unordered_map`, `std::unordered_set`, `std::unordered_multimap`, `std::unordered_multiset`, or
- when one of the standard sorted associative containers do better: `std::map`, `std::set`, `std::multi_map`, `std::multi_set`, or
- when one of the many algorithms, parsers do better, or
- when one of the [100+](https://en.wikipedia.org/wiki/Category:Trees_(data_structures)) other trees do better: binary, ternary, m-ary, k-ary, red-black, k-d, B, B+ trees!

### Design Tradeoffs

The selected design tradeoffs are:
- the Standard Template Library (STL) principles, and by extension, their tradeoffs, and
- the C++ Core Guidelines, and
- the C++20 support, and
- precise, detailed, and intelligible documentation for the wider audience.

## Class fcarouge::tree

Defined in header [fcarouge/tree.hpp](include/fcarouge/tree.hpp)

```
template <
    class Type,
    class AllocatorType = std::allocator<Type>
> class tree
```

The `fcarouge::tree` type is a hierarchical tree data structure. The container is a non-linear non-associative unordered recursively referenced collection of nodes, each containing a value. The design tradeoffs are influenced by the Standard Template Library (STL) principles and the C++ Core Guidelines. The container is a standard layout class type which may help with memory and cross language communication. The iteration order of the standard iterator is unspecified, except that each element is visited only once.

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
| `difference_type` | Signed integer type to represent element distances. |
| `reference` | The reference type of the contained data elements. |
| `const_reference` | The constant reference type of the contained data elements. |
| `pointer` | The pointer type of the contained data elements. |
| `const_pointer` | The const pointer type of the contained data elements. |
| `iterator` | Type to identify and traverse the elements of the container. |
| `const_iterator` | Constant type to identify and traverse the elements of the container. |

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

### Example

![Hello, World! Tree](https://francoiscarouge.github.io/Tree/dot_inline_dotgraph_1.png)

```cpp
// Support the tree container in this program by including its definition.
#include "fcarouge/tree.hpp"

// For convenience in this example, consider not using in production.
using namespace fcarouge;

int main(int, char **)
{
  // Declare a "greeting" variable as a tree of strings type.
  tree<std::string> greeting;

  // Push at the front of the tree a root element with string value "Hello, ".
  greeting.push_front("Hello, ");

  // Push in an element with value "Wo" as a child of the beginning, root node.
  greeting.push(greeting.begin(), "Wo");

  // Push in another element with value "d!" and keep its iterator "i".
  const tree<std::string>::iterator i = greeting.push(greeting.begin(), "d!");

  // Insert a left sibling of iterator "i", child of the root, with value "rl".
  greeting.emplace(i, "rl");

  return 0;
}
```

## File include/fcarouge/tree.hpp

### Includes

| Include | Definition |
| --- | --- |
| `<cstddef>` | Standard size and pointer difference types support. |
| `<iterator>` | Standard input iterator tag support. |
| `<memory>` | Standard construction, allocation, and addressing support. |
| `<utility>` | Standard moving and forwarding resources support. |

### Namespaces

| Namespace | Definition |
| --- | --- |
| `fcarouge` | François Carouge's projects namespace. |

### Classes

| Class | Definition |
| --- | --- |
| `tree` | Non-linear non-associative unordered recursively referenced collection of nodes, each containing a value. |

## License

<img align="right" src="http://opensource.org/trademarks/opensource/OSI-Approved-License-100x137.png">

Tree for C++ is licensed under the [MIT License](http://opensource.org/licenses/MIT):

Copyright &copy; 2020 François Carouge

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
