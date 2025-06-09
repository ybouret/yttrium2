#include "y/memory/management/studio.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace
{
    class Foo
    {
    public:
        Foo() {}
        ~Foo() noexcept {}
        Foo(const Foo &) noexcept;

        static void * operator new(const size_t);
        static void   operator delete(void * const, const size_t) noexcept;

       
    private:
        Y_Disable_Assign(Foo);
    };

    typedef Memory::Studio<Foo,0> FooStudio;


    

}

namespace Yttrium
{
    namespace Memory
    {
        template <> const char * const FooStudio :: CallSign = "Foo::Studio";
    }
}

Y_UTEST(memory_studio)
{

    FooStudio &studio = FooStudio::Instance();

    studio.display(std::cerr,0);

}
Y_UDONE()

