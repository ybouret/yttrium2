
#include "y/concurrent/data/inferno.hpp"
#include "y/utest/run.hpp"
#include "y/system/rand.hpp"
#include "y/memory/stealth.hpp"

using namespace Yttrium;


namespace
{

    class Dummy
    {
    public:
        static const System::AtExit::Longevity LifeTime = 1001;
        static const char * const CallSign;
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

    int                Dummy::Count = 0;
    const char * const Dummy::CallSign = "Dummy";

    typedef Concurrent::Inferno<Dummy> DummyInferno;



    static const size_t     maxi = 1000;

    static inline
    void fill(Dummy *                addr[],
              size_t &               size,
              DummyInferno &         mgr,
              System::Rand &         ran)
    {
        while(size<maxi)
        {
            const size_t choice = ran.leq(2);
            switch(choice)
            {
                case 1:
                    addr[size] = mgr.template produce<int>( ran.to<uint16_t>() );
                    break;

                case 2:
                {
                    const Dummy dummy(007);
                    addr[size] = mgr.reenact(dummy);
                } break;

                default:
                    addr[size] = mgr.recover();
                    break;
            }
            ++size;
        }
    }


    static inline
    void empty(const size_t       to,
               Dummy *            addr[],
               size_t &           size,
               DummyInferno &      mgr,
               System::Rand &      ran)
    {
        ran.shuffle(addr,size);
        while(size>to)
        {
            mgr.zombify( addr[--size] );
        }
        mgr.gc(0xaa);
    }

}


Y_UTEST(concurrent_inferno)
{

    System::Rand     ran;
    DummyInferno    &mgr = DummyInferno::Instance();
    //std::cerr << mgr.callSign() << std::endl;

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
Y_UDONE()
