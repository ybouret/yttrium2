#include "y/pointer/arc.hpp"
#include "y/utest/run.hpp"



using namespace Yttrium;

#include "y/object/counted.hpp"
namespace
{
    class Dummy : public CountedObject
    {
    public:
        inline explicit Dummy(const int x) noexcept :
        CountedObject(), value(x)
        {

        }

        inline virtual ~Dummy() noexcept
        {

        }

        const int value;

    private:
        Y_Disable_Copy_And_Assign(Dummy);
    };

    
}



Y_UTEST(ptr_arc)
{
    {
        ArcPtr<Dummy> ap( new Dummy(4) );
        {
            ArcPtr<Dummy> cp(ap);
        }
    }

    ArcPtr<Dummy> ap = new Dummy(7);
    
}
Y_UDONE()
