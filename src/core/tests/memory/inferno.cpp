
#include "y/memory/management/inferno.hpp"
#include "y/utest/run.hpp"
#include "y/system/rand.hpp"
#include "y/memory/stealth.hpp"

using namespace Yttrium;


namespace
{

    class Dummy
    {
    public:
        static int Count;
        explicit Dummy() noexcept : value(0)
        {
            ++Count;
        }

        virtual ~Dummy() noexcept
        {
            --Count;
        }

        const int value;
    private:
        Y_Disable_Assign(Dummy);
    };

    int Dummy::Count = 0;


    static const size_t     maxi = 1000;


    template <typename T> static inline
    void fill(T *                  addr[],
              size_t &             size,
              Memory::Inferno<T> & mmgr,
              System::Rand &       ran)
    {
        while(size<maxi)
        {
            addr[size] = mmgr.recover();
            ++size;
        }
    }


    template <typename T> static inline
    void empty(const size_t       to,
               T *                addr[],
               size_t &           size,
               Memory::Inferno<T> &mmgr,
               System::Rand &      ran)
    {
        ran.shuffle(addr,size);
        while(size>to)
        {
            mmgr.zombify( addr[--size] );
        }
        mmgr->gc(0xaa);
    }

}

Y_UTEST(memory_inferno)
{

    System::Rand     ran;

    {
        Memory::Inferno<Dummy>  mgr;
        Dummy  *                addr[maxi]; Y_Memory_BZero(addr);
        size_t                  size=0;
        fill(addr,size,mgr,ran);
        for(size_t iter=0;iter<10;++iter)
        {
            empty(size>>1,addr,size,mgr,ran);
            fill(addr,size,mgr,ran);
        }
        empty(0,addr,size,mgr,ran);
    }




}
Y_UDONE()
