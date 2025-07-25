
#include "y/container/associative.hpp"
#include "y/container/tree/suffix.hpp"
#include "y/container/htable.hpp"

#include "y/utest/run.hpp"
#include "y/protean/cache/warped.hpp"
#include "y/threading/single-threaded-class.hpp"

#include "y/string.hpp"

namespace Yttrium
{

    typedef SingleThreadedClass AssociativeThreading;

    struct SuffixSetAPI
    {
        template <typename KEY, typename T>
        class Knot
        {
        public:
            Y_Args_Declare(T,Type);
            Y_Args_Declare(KEY,Key);
            typedef Protean::WarpedCacheOf<Knot,AssociativeThreading> Pool;
            typedef Core::ListOf<Knot> List;

            inline Knot(ParamType arg) :
            data(arg),
            next(0),
            prev(0)
            {
            }

            inline Knot(const Knot &knot) :
            data(knot.data),
            next(0),
            prev(0)
            {
            }


            inline ~Knot() noexcept
            {}

            ConstKey & key() const noexcept { return data.key(); }

            Type   data;
            Knot * next;
            Knot * prev;

        private:
            Y_Disable_Assign(Knot);
        };
    };



}

using namespace Yttrium;

namespace
{
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

Y_UTEST(container_associative)
{

    {
        typedef SuffixSetAPI::Knot<String,Dummy> Knot;
        typedef Knot::Pool  KPool;

        const Dummy dum1("dum1");

        KPool  kpool;
        Knot * knot = kpool.summon(dum1);
        std::cerr << "knot: " << knot->key() << std::endl;
        Knot * kcpy = kpool.mirror(knot);
        std::cerr << "kcpy: " << knot->key() << std::endl;

        kpool.banish(knot);
        kpool.remove(kcpy);

    }

}
Y_UDONE()

