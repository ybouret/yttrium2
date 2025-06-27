
#include "y/apex/block/model.hpp"



#include "y/utest/run.hpp"
#include "y/system/rand.hpp"

namespace Yttrium
{
    namespace Apex
    {



        template <typename U>
        struct UFmt
        {
            static inline
            U * Make(uint64_t &data, const size_t size) noexcept
            {
                assert(size<=sizeof(uint64_t)/sizeof(U));
                uint64_t        v = data;
                U        * const u = (U *) &data;
                for(size_t i=0;i<size;++i)
                {
                    u[i] = U(v);
                    v >>= 8*sizeof(U);
                }
                return u;
            }

        };

        template <typename T> inline
        const T * Format(uint64_t &data, size_t &size)
        {
            size          = Block<T>::SizeFor( Calculus::BitsFor::Count(data) );
            return UFmt<T>::Make(data,size);
        }

    }
}

using namespace Yttrium;



Y_UTEST(apex_model)
{
    System::Rand ran;

    {
        const uint64_t u = ran.gen<uint64_t>(57);

        {
            uint64_t q = u;
            size_t   s = 0;
            const uint8_t * const p = Apex::Format<uint8_t>(q,s);
            Hexadecimal::Display(std::cerr,p,s) << "#" << s << std::endl;
        }

        {
            uint64_t q = u;
            size_t   s = 0;
            const uint16_t * const p = Apex::Format<uint16_t>(q,s);
            Hexadecimal::Display(std::cerr,p,s) << "#" << s << std::endl;
        }
    }

    {
        std::cerr << "Using Models" << std::endl;
        const uint64_t arr[2] = { ran.gen<uint64_t>( unsigned(ran.leq(30)) ), ran.gen<uint64_t>( unsigned(ran.leq(30)) ) };
        Apex::Model m(arr,2);
        
        std::cerr << m << std::endl;

        m.set(Apex::View8);
        std::cerr << m << std::endl;

        m.set(Apex::View16);
        std::cerr << m << std::endl;

        m.set(Apex::View32);
        std::cerr << m << std::endl;


    }
}
Y_UDONE()
