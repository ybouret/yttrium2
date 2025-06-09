
#include "y/memory/management/purgatory/inferno.hpp"
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

        explicit Dummy(const int arg) noexcept : value(arg)
        {
            ++Count;
        }

        explicit Dummy(const Dummy &_) noexcept : value(_.value)
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
            const size_t choice = ran.leq(2);
            switch(choice)
            {
                case 1:
                    addr[size] = mmgr.template recover<int>( ran.to<uint16_t>() );
                    break;

                case 2:
                {
                    const Dummy dummy(007);
                    addr[size] = mmgr.reenact(dummy);
                } break;

                default:
                    addr[size] = mmgr.recover();
                    break;
            }
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
        Y_CHECK(!Dummy::Count);
    }




}
Y_UDONE()
