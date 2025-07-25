#include "y/container/associative/suffix/map.hpp"
#include "y/utest/run.hpp"
#include "y/string.hpp"

#include "y/utest/run.hpp"

using namespace Yttrium;

namespace {

    class Dummy
    {
    public:
        Dummy(const int v) : a(v) {}
        ~Dummy() noexcept {}

        Dummy(const Dummy &other) noexcept : a(other.a) {}

        const int a;

    private:
        Y_Disable_Assign(Dummy);
    };
}

Y_UTEST(container_suffix_map)
{

    SuffixMap<String,Dummy> map;

    {
        const Dummy dum(7);
        Y_CHECK(map.insert("dum7", dum));
        Y_CHECK(!map.insert("dum7", dum));

        Y_CHECK(map.search("dum7"));

        Y_CHECK(map.remove("dum7"));
        Y_CHECK(!map.search("dum7"));
        Y_CHECK(!map.remove("dum7"));


    }

}
Y_UDONE()

