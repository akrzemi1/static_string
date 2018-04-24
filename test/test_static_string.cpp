#include <ak_toolkit/static_string.hpp>
#include <sstream>
#include <cassert>
#include <type_traits>

namespace sstr = ak_toolkit::static_str;

namespace test_concatenation
{
  #if __cplusplus >= 201703L
  constexpr sstr::string CD = sstr::literal("CD");
  constexpr sstr::string NAME = "AB" + CD + sstr::literal("EF") + "GH";
  #else
  constexpr auto CD = sstr::literal("CD");
  constexpr auto NAME = "AB" + CD + sstr::literal("EF") + "GH";
  #endif

  static_assert(std::is_same<decltype(CD), const sstr::string_literal<2>>::value, "***");
  static_assert(std::is_same<decltype(NAME), const sstr::array_string<8>>::value, "***");
  static_assert(NAME.size() == 8, "***");
  static_assert(NAME[0] == 'A', "***");
  
  void run ()
  {
    std::ostringstream os;
    os << NAME;
    assert(os.str() == "ABCDEFGH");
  }
}

namespace test_concatenating_empty_string
{
  constexpr auto CD = sstr::literal("CD");
  constexpr auto CD_ = CD + "";
  static_assert(CD_.size() == CD.size(), "***");
}

namespace test_offset_literal
{
  constexpr auto CD = sstr::offset_literal<3>("AB_CD");
  static_assert(std::is_same<decltype(CD), const sstr::array_string<2>>::value, "***");
  static_assert(CD.size() == 2, "***");
  static_assert(CD[0] == 'C', "***");
  static_assert(CD[1] == 'D', "***");
  
  constexpr auto AB_CD = sstr::offset_literal<0>("AB_CD");
  static_assert(AB_CD.size() == 5, "***");
  static_assert(AB_CD[0] == 'A', "***");
  static_assert(AB_CD[4] == 'D', "***");
  
  constexpr auto _0 = sstr::offset_literal<5>("AB_CD");
  static_assert(_0.size() == 0, "***");
  
  void run ()
  {
    std::ostringstream os;
    os << CD;
    assert(os.str() == "CD");
  }
}

namespace test_literal_suffix
{
  constexpr auto fpath = sstr::literal("path/fname.txt");
  constexpr auto fname = sstr::suffix(fpath, 5);
  
  void run ()
  {
    std::ostringstream os;
    os << fname;
    assert(os.str() == "fname.txt");
  }
}	

int main ()
{
  test_offset_literal::run();
  test_concatenation::run();
  test_literal_suffix::run();
}
