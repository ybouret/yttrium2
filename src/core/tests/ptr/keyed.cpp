
#include "y/pointer/keyed.hpp"
#include "y/pointer/arc.hpp"
#include "y/pointer/auto.hpp"
#include "y/utest/run.hpp"
#include "y/string.hpp"


using namespace Yttrium;

#include "y/object/counted.hpp"

namespace
{
    class Dummy : public CountedObject
    {
    public:
        inline explicit Dummy(const char * const id) noexcept :
        CountedObject(), name(id)
        {

        }

        inline virtual ~Dummy() noexcept
        {

        }

        const String & key() const noexcept { return name; }

        const String name;

    private:
        Y_Disable_Copy_And_Assign(Dummy);
    };


}



Y_UTEST(ptr_keyed)
{

    typedef Keyed< String, AutoPtr<Dummy> > DAutoPtr;

    DAutoPtr p = new Dummy("hello");
    std::cerr << "key = '" << p.key() << "'" << std::endl;

    typedef Keyed< String, ArcPtr<Dummy> > DArcPtr;

    DArcPtr q = new Dummy("world");
    std::cerr << "key = '" << q.key() << "'" << std::endl;


}
Y_UDONE()
