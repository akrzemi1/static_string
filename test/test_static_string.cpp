#include <ak_toolkit/static_string.hpp>

namespace sstr = ak_toolkit::static_str;

#if __cplusplus >= 201703L
constexpr sstr::string CD = sstr::literal("CD");
constexpr sstr::string NAME = "AB" + CD + sstr::literal("EF") + "GH";
#else
constexpr auto CD = sstr::literal("CD");
constexpr auto NAME = "AB" + CD + sstr::literal("EF") + "GH";
#endif

static_assert(NAME.size() == 8, "***");
static_assert(NAME[0] == 'A', "***");

#include <sstream>
#include <cassert>

int main ()
{
	std::ostringstream os;
	os << NAME;
	assert(os.str() == "ABCDEFGH");
}