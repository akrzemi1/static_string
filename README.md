# static_string
A C++11 single-header library for representing and concatenating constexpr string literals.

## Usage
You use this library if you want to build a relatively short string whose contents you know at compile time, and you want to make sure no [static initialization order fiasco](https://isocpp.org/wiki/faq/ctors#static-init-order) ever occurs.

```c++
#include <iostream>
#include "static_string.hpp"
namespace sstr = ak__toolkit::static_str;

constexpr auto SERVICE_NAME = sstr::literal("SRVC1");
// SERVICE_NAME has type sstr::string_literal<5>
// string_literal is a reference to a C-like string literal, but with different interface
// length of the literal is part of the type

constexpr auto MESSAGE = "service " + SERVICE_NAME " ready";
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

## installation
It is a C++11 header-only library.

## License
Distributed under the [Boost Software License, Version 1.0](http://www.boost.org/LICENSE_1_0.txt).
