#include "y/apex/lock.hpp"
#include "y/concurrent/api/simd/crew.hpp"
#include "y/object/factory.hpp"
#include "y/memory/small/metrics.hpp"
#include "y/utest/run.hpp"

#include "y/random/park-miller.hpp"
#include "y/pointer/auto.hpp"
#include "y/apex/rational.hpp"
#include "y/container/sequence/vector.hpp"

using namespace Yttrium;

namespace
{
    class ParaMem
    {
    public:
        explicit ParaMem() : result(0), kernel( I(), & ParaMem::run)
        {
        }

        virtual ~ParaMem() noexcept
        {
        }

        Concurrent::Kernel & operator*() noexcept { return kernel; }


    private:
        Y_Disable_Copy_And_Assign(ParaMem);
        int                result;
        Concurrent::Kernel kernel;

        inline ParaMem * I() noexcept { return this; }

        void run(const Concurrent::Context &ctx)
        {
            { Y_Giant_Lock(); ( std::cerr << "in " << ctx << std::endl).flush() ; }

            Random::ParkMiller ran;
            Object::Factory   &mgr = Object::Factory::Instance();
            for(size_t i=0;i<=10000;  i += ran.in<size_t>(1,10) )
            {
                void * blk = mgr.query(i);
                mgr.store(blk,i);
            }

            {
                AutoPtr<String> ps = new String("Hello, World!");
                *ps += " from ";
                *ps += ctx.c_str();

                { Y_Giant_Lock(); (std::cerr << ps << std::endl).flush(); }

            }

            Vector<apq> qvec;
            for(size_t i=5+ran.leq(5);i>0;--i)
            {
                qvec << apq(ran,ran.in<size_t>(1,10),ran.in<size_t>(1,10));
            }

            {
                Y_Giant_Lock();
                Y_Apex_Giant_Lock();
                (std::cerr << ctx << " : " << qvec << std::endl).flush();
            }


        }
    };
}

Y_UTEST(concurrent_memory)
{
    ParaMem          mem;
    Concurrent::Crew crew( Concurrent::Site::Default );
    crew( *mem );

}
Y_UDONE()
