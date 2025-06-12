
#include "y/memory/operating.hpp"
#include "y/type/destruct.hpp"
#include "y/memory/stealth.hpp"
#include "y/utest/run.hpp"
#include "y/system/rand.hpp"
#include "y/core/display.hpp"

using namespace Yttrium;

namespace {

    class Dummy
    {
    public:
        static int Count;

        Dummy() : indx(0)
        {
            ++Count;
            std::cerr << "[+] Dummy" << std::endl;
        }

        Dummy(size_t i) : indx(i)
        {
            ++Count;
            std::cerr << "[+] Dummy#" << indx << std::endl;
        }

        Dummy(const Dummy &other) noexcept : indx(other.indx)
        {
            ++Count;
            std::cerr << "[*] Dummy#" << indx << std::endl;
        }


        ~Dummy() noexcept
        {
            --Count;
            std::cerr << "[-] Dummy" << std::endl;
        }

        const size_t indx;

        static inline
        void Create(void * const       target,
                    void * const       source,
                    const size_t       indexx,
                    void * const)
        {
            Y_ASSERT(0==source);
            Y_ASSERT(indexx>0);
            new (target) Dummy();
        }

        static inline
        void Create2(void * const       target,
                     void * const       source,
                     const size_t       indexx,
                     void * const       params)
        {
            Y_ASSERT(0==source);
            Y_ASSERT(indexx>0);
            Y_ASSERT(0!=params);
            new (target) Dummy(indexx + *(ptrdiff_t*)params);
        }

        static inline
        void Create3(void * const       target,
                     void * const       source,
                     const size_t       indexx,
                     void * const)
        {
            Y_ASSERT(0!=source);
            Y_ASSERT(indexx>0);
            const Dummy * const dum = static_cast<const Dummy *>(source)-1;
            new (target) Dummy( dum[indexx] );
        }

        static inline
        void Delete(void * const addr) noexcept
        {
            assert(0!=addr);
            Destruct( static_cast<Dummy *>(addr) );
        }

    private:
        Y_Disable_Assign(Dummy);
    };

    int Dummy:: Count = 0;

}

Y_UTEST(memory_operative)
{

    static const size_t numWords = 10;
    void *       wksp[ numWords ];
    const size_t wlen = sizeof(wksp);


    {
        Y_Memory_BZero(wksp);
        Memory::Operative op(wksp,wlen/sizeof(Dummy),sizeof(Dummy),
                             Dummy::Create,
                             0,
                             0,
                             Dummy::Delete);
    }
    Y_ASSERT(!Dummy::Count);

    {
        ptrdiff_t offset = 1;
        Y_Memory_BZero(wksp);
        Memory::Operative op(wksp,wlen/sizeof(Dummy),sizeof(Dummy),
                             Dummy::Create2,
                             0,
                             &offset,
                             Dummy::Delete);


        void *wksp2[numWords];
        Y_Memory_BZero(wksp2);
        Memory::Operative op2(wksp2,wlen/sizeof(Dummy),sizeof(Dummy),
                              Dummy::Create3,
                              wksp,
                              0,
                              Dummy::Delete);

    }
    Y_ASSERT(!Dummy::Count);

    std::cerr << "C++" << std::endl;
    System::Rand ran;
    {
        Y_Memory_BZero(wksp);
        static const size_t numArr = 3;
        uint16_t            array[numArr];
        Y_Memory_BZero(array);
        {
            Memory::Operating<Dummy> op(wksp,wlen/sizeof(Dummy));
        }

        {
            Core::Display(std::cerr,array,numArr) << std::endl;
            ran.fill(array,sizeof(array));
            Core::Display(std::cerr,array,numArr) << std::endl;
            Memory::Operating<Dummy> op(wksp,array,numArr);
        }
    }




}
Y_UDONE()

