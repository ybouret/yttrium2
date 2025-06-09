
#include "y/memory/workspace/cxx.hpp"
#include "y/system/rand.hpp"
#include "y/utest/run.hpp"
#include "y/core/display.hpp"

using namespace Yttrium;

namespace
{
    class Dummy
    {
    public:
        static unsigned Count;

        Dummy() noexcept :
        value( ++Count )
        {

        }

        static inline void Create(void * const addr)
        {
            new (addr) Dummy();
        }

        static inline void Create2(void * const addr, const size_t offset)
        {
            new (addr) Dummy();
            Y_ASSERT(offset==Dummy::Count);
        }


        inline friend std::ostream & operator<<(std::ostream &os, const Dummy &self)
        {
            os << self.value;
            return os;
        }


        ~Dummy() noexcept
        {
            assert(Count>0);
            --Count;
        }

        const unsigned value;

    private:
        Y_Disable_Assign(Dummy);
    };

    unsigned Dummy::Count = 0;

}

Y_UTEST(memory_workspace)
{
    {
        Memory::CxxWorkspace<Dummy,10> wksp;
        Core::Display(std::cerr,&wksp[1],wksp.size()) << std::endl;
        for(size_t i=1;i<=wksp.size();++i)
        {
            std::cerr << wksp[i] << std::endl;
        }
    }
    Y_CHECK(0==Dummy::Count);

    {
        Memory::CxxWorkspace<Dummy,15> wksp(Procedural,Dummy::Create);
        Core::Display(std::cerr,&wksp[1],wksp.size()) << std::endl;
    }
    Y_CHECK(0==Dummy::Count);

    {
        Memory::CxxWorkspace<Dummy,7> wksp(Procedural,Dummy::Create2,1);
        Core::Display(std::cerr,wksp.begin(),wksp.size()) << std::endl;
    }
    Y_CHECK(0==Dummy::Count);
}
Y_UDONE()

