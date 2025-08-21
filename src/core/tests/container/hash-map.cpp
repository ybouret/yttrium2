


#include "y/container/associative/hash/map.hpp"
#include "y/utest/run.hpp"
#include "y/string.hpp"
#include "y/hashing/fnv.hpp"
#include "y/hashing/to.hpp"

using namespace Yttrium;

namespace
{

    class Dummy
    {
    public:
        Dummy(const int value) : a(value) {}
        ~Dummy() noexcept {}

        Dummy(const Dummy &d) : a(d.a) {}

        const int a;
    private:
        Y_Disable_Assign(Dummy);
    };
}

Y_UTEST(container_hash_map)
{

    HashMap<String,Dummy> map;

    {
        const String key = "dum1";
        const Dummy dum1(7);
        Y_CHECK(map.insert(key,dum1));
        Y_CHECK(!map.insert(key,dum1));

        {
            const HashMap<String,Dummy> &cmap = map;
            Y_ASSERT(cmap.search(key));
            std::cerr << "const search: " << cmap.search(key)->a << std::endl;
        }

        Y_ASSERT(map.search(key));
        std::cerr << "mutable search: " << map.search(key)->a << std::endl;

        Y_CHECK(map.remove(key));
        Y_CHECK(!map.remove(key));
        
    }



}
Y_UDONE()

