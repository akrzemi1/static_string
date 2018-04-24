# static_string
A C++11 single-header library for representing and concatenating constexpr string literals. 

## Usage
You use this library if you want to build a relatively short string whose contents you know at compile time, and you want to make sure no [static initialization order fiasco](https://isocpp.org/wiki/faq/ctors#static-init-order) ever occurs.

```c++
#include <iostream>
#include "static_string.hpp"
namespace sstr = ak_toolkit::static_str;

constexpr auto SERVICE_NAME = sstr::literal("SRVC1");
// SERVICE_NAME has type sstr::string_literal<5>
// string_literal is a reference to a C-like string literal, but with different interface
// length of the literal is part of the type

constexpr auto MESSAGE = "service " + SERVICE_NAME + " ready";
// MESSAGE has type sstr::array_string<8 + 5 + 6>
// array_string is an array that stores the null-terminated literal
// length of the array (excluding the trailing zero) is part of the type

int main()
{
  std::cout << MESSAGE << std::endl;
  // outputs: "service SRVC1 ready"
  
  const char * msg = MESSAGE; // conversion to const char *
  std::cout << msg << std::endl;
  // outputs: "service SRVC1 ready"
}
```

You can also take a part of a string literal starting at a given offset:

```c++
constexpr auto FILENAME = sstr::offset_literal<4>("dir/filename");
// FILENAME has type sstr::array_string<8>

int test()
{
  std::cout << FILENAME << std::endl;
  // outputs: "filename"
}
```

Or:

```c++
constexpr auto fpath = sstr::literal("path/fname");
constexpr auto fname = sstr::suffix(fpath, 5);
// decltype(fname) is sstr::string_literal_suffix<10>
// fname.size() == 5

constexpr auto full_fname = fname + ".txt";
// decltype(fname) is sstr::array_string_suffix<10 + 4>
// fname.size() == 9

  std::cout << full_fname << std::endl;
  // outputs: "fname.txt"
```

For more information see [this blog post](https://akrzemi1.wordpress.com/2017/06/28/compile-time-string-concatenation/).

## installation
It is a C++11 header-only library.

## License
Distributed under the [Boost Software License, Version 1.0](http://www.boost.org/LICENSE_1_0.txt).
