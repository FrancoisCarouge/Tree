Tree for C++
============

Tree data structure for C++: non-linear non-associative unordered recursively referenced collection of nodes, each containing a value.

## Information Tree

| Leaf | Value |
| --- | --- |
| Code | [![Code Repository](https://img.shields.io/badge/Repository-GitHub%20%F0%9F%94%97-brightgreen)](https://github.com/FrancoisCarouge/Tree) |
| Documentation | [![Doxygen Documentation](https://img.shields.io/badge/Documentation-GitHub%20Pages%20%F0%9F%94%97-brightgreen)](https://francoiscarouge.github.io/Tree/) |
| Licensing | [![MIT License](https://img.shields.io/badge/License-MIT%20%F0%9F%94%97-brightgreen)](https://raw.githubusercontent.com/francoiscarouge/tree/develop/LICENSE.txt) |
| Tests Coverage | [![Coverage Status](https://coveralls.io/repos/github/FrancoisCarouge/Tree/badge.svg?branch=develop)](https://coveralls.io/github/FrancoisCarouge/Tree?branch=develop) |
| Continuous Integration | [![Test Code Style: ClangFormat](https://github.com/FrancoisCarouge/Tree/workflows/Test%20Code%20Style:%20ClangFormat/badge.svg)](https://github.com/FrancoisCarouge/Tree/actions?query=workflow%3A%22Test+Code+Style%3A+ClangFormat%22+branch%3Adevelop) <br> [![Test Documentation: Doxygen](https://github.com/FrancoisCarouge/Tree/workflows/Test%20Documentation:%20Doxygen/badge.svg)](https://github.com/FrancoisCarouge/Tree/actions?query=workflow%3A%22Test+Documentation%3A+Doxygen%22+branch%3Adevelop) <br> [![Test Static Analysis: CppCheck](https://github.com/FrancoisCarouge/Tree/workflows/Test%20Static%20Analysis:%20CppCheck/badge.svg)](https://github.com/FrancoisCarouge/Tree/actions?query=workflow%3A%22Test+Static+Analysis%3A+CppCheck%22+branch%3Adevelop) <br> [![Test: Ubuntu 20.04 GCC 10](https://github.com/FrancoisCarouge/Tree/workflows/Test:%20Ubuntu%2020.04%20GCC%2010/badge.svg)](https://github.com/FrancoisCarouge/Tree/actions?query=workflow%3A%22Test%3A+Ubuntu+20.04+GCC+10%22+branch%3Adevelop) <br> [![Test Memory: Valgrind](https://github.com/FrancoisCarouge/Tree/workflows/Test%20Memory:%20Valgrind/badge.svg)](https://github.com/FrancoisCarouge/Tree/actions?query=workflow%3A%22Test+Memory%3A+Valgrind%22+branch%3Adevelop) <br> [![Test Address: AddressSanitizer](https://github.com/FrancoisCarouge/Tree/workflows/Test%20Address:%20AddressSanitizer/badge.svg)](https://github.com/FrancoisCarouge/Tree/actions?query=workflow%3A%22Test+Address%3A+AddressSanitizer%22+branch%3Adevelop) <br> [![Deploy Documentation: Doxygen GitHub Pages](https://github.com/FrancoisCarouge/Tree/workflows/Deploy%20Documentation:%20Doxygen%20GitHub%20Pages/badge.svg)](https://github.com/FrancoisCarouge/Tree/actions?query=workflow%3A%22Deploy+Documentation%3A+Doxygen+GitHub+Pages%22) <br> [![Deploy Code Coverage: Coveralls](https://github.com/FrancoisCarouge/Tree/workflows/Deploy%20Code%20Coverage:%20Coveralls/badge.svg)](https://github.com/FrancoisCarouge/Tree/actions?query=workflow%3A%22Deploy+Code+Coverage%3A+Coveralls%22) <br> [![FOSSA Status](https://app.fossa.com/api/projects/git%2Bgithub.com%2FFrancoisCarouge%2FTree.svg?type=shield)](https://app.fossa.com/projects/git%2Bgithub.com%2FFrancoisCarouge%2FTree?ref=badge_shield) |
| Report and Participate | [![GitHub Issues](https://img.shields.io/github/issues-raw/francoiscarouge/tree)](https://github.com/francoiscarouge/tree/issues) |
| Best Practices | [![CII Best Practices](https://bestpractices.coreinfrastructure.org/projects/4221/badge)](https://bestpractices.coreinfrastructure.org/projects/4221) |
| Support Open Free Software | [![Sponsor](https://img.shields.io/badge/Sponsor-%EF%BC%84%EF%BC%84%EF%BC%84%20%F0%9F%94%97-brightgreen)](http://paypal.me/francoiscarouge) |

## Hello, World!

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

## Sometimes all you need is this tree...

- to represent, store, walk, manipulate, and search some hierarchical information with the purpose of deciding, routing, sorting, or composing results.

## ...but often you really don't!

- when one of the standard associative containers do better: `std::unordered_map`, `std::unordered_set`, `std::unordered_multimap`, `std::unordered_multiset`, or
- when one of the standard sorted associative containers do better: `std::map`, `std::set`, `std::multi_map`, `std::multi_set`, or
- when one of the [100+](https://en.wikipedia.org/wiki/Category:Trees_(data_structures)) other trees do better: binary, ternary, m-ary, k-ary, red-black, k-d, B, B+ trees, or
- when one of the many algorithms do better: parsers, ...

## License

<img align="right" src="http://opensource.org/trademarks/opensource/OSI-Approved-License-100x137.png">

Tree for C++ is licensed under the [MIT License](http://opensource.org/licenses/MIT):

Copyright &copy; 2020 François Carouge

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
