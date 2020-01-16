#include <ak_toolkit/static_string.hpp>
#include <sstream>
#include <cassert>
#include <type_traits>

namespace sstr = ak_toolkit::static_str;

template <typename T>
std::string to_string(T s)
{
  std::ostringstream os;
  os << s;
  return os.str(); 
}

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
    assert(to_string(NAME) == "ABCDEFGH");
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
    assert(to_string(CD) == "CD");
  }
}

namespace test_literal_suffix
{
  constexpr auto fpath = sstr::literal("path/fname");
  constexpr auto fname = sstr::suffix(fpath, 5);
  constexpr auto full_fname = fname + ".txt";
    
  constexpr auto AB = sstr::literal("AB");
  constexpr auto B = sstr::suffix(AB, 1);
  constexpr auto ABB = AB + B;
  constexpr auto BAB = B + AB;
  constexpr auto BB = B + B;
  
  void run () 
  {
    assert (to_string(BB) == "BB");
    assert (to_string(ABB) == "ABB");
    assert (to_string(BAB) == "BAB");
    assert (to_string(full_fname) == "fname.txt");
  }
}	

namespace test_substr
{
  constexpr auto AB = sstr::literal("AB");
  constexpr auto B = sstr::substr<1,1>(AB);
  constexpr auto ABB = AB + B;
  constexpr auto BAB = B + AB;
  constexpr auto BB = B + B;

  constexpr auto full_path = sstr::literal("path/fname.txt");
  constexpr auto path = sstr::substr<0, 4>(full_path);
  constexpr auto fname = sstr::substr<5, 5>(full_path);
  constexpr auto file_ext = sstr::substr<11, 3>(full_path);
  constexpr auto rfull_path = path + "/" + fname + "." + file_ext;


  namespace find
  {

    template<int N, typename T>
    constexpr std::size_t find_char(sstr::string<N, T> const& str, char const c, std::size_t const pos = 0)
    {
       return pos >= str.size() ? str.size() : str[pos] == c ? pos : find_char(str, c, pos + 1);
    }

    constexpr auto full_path = sstr::literal("path/fname.txt");
    constexpr auto slash_pos = find_char(full_path, '/');
    constexpr auto point_pos = find_char(full_path, '.') ;

    constexpr auto path = sstr::substr<0, slash_pos>(full_path);
    constexpr auto fname_short = sstr::substr<slash_pos + 1, point_pos - slash_pos - 1>(full_path);
  }

  void run ()
  {
    assert (to_string(BB) == "BB");
    assert (to_string(ABB) == "ABB");
    assert (to_string(BAB) == "BAB");
    assert (to_string(fname) == "fname");
    assert (to_string(full_path) == to_string(rfull_path));
    assert (to_string(find::path) == "path");
    assert (to_string(find::fname_short) == "fname");
  }
}


int main ()
{
  test_offset_literal::run();
  test_concatenation::run();
  test_literal_suffix::run();
  test_substr::run();
}
