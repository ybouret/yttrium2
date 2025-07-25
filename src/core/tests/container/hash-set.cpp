

#include "y/container/associative/hash/set.hpp"
#include "y/utest/run.hpp"
#include "y/string.hpp"
#include "y/hashing/fnv.hpp"
#include "y/hashing/to.hpp"

using namespace Yttrium;

namespace
{
    class StringHasher
    {
    public:
        StringHasher() : H() {}
        ~StringHasher() noexcept {}

        Hashing::FNV H;

        size_t operator()(const String &key)
        {
            return Hashing::To<size_t>(H,key);
        }


    private:
        Y_Disable_Copy_And_Assign(StringHasher);
    };

    class Dummy : public CountedObject
    {
    public:
        explicit Dummy(const char * const id) :
        CountedObject(),
        name(id)
        {

        }

        Dummy(const Dummy &other) :
        CountedObject(), name(other.name)
        {
        }

        virtual ~Dummy() noexcept
        {
        }

        const String & key() const noexcept { return name; }

        const String name;

    private:
        Y_Disable_Assign(Dummy);
    };
}

Y_UTEST(container_hash_set)
{

    HashSet<String,Dummy,StringHasher> set;

#if 0

    {
        const Dummy dum1("dum1");
        Y_CHECK(set.insert(dum1));
        Y_CHECK(!set.insert(dum1));

        {
            const SuffixSet<String,Dummy> &cset = set;
            Y_ASSERT(cset.search("dum1"));
            std::cerr << "const search: " << cset.search("dum1")->key() << std::endl;
        }

        Y_ASSERT(set.search("dum1"));
        std::cerr << "mutable search: " << set.search("dum1")->key() << std::endl;


        Y_CHECK(set.remove("dum1"));
        Y_CHECK(!set.remove("dum1"));
    }

    set.free();
#endif



}
Y_UDONE()

