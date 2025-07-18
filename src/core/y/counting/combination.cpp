
#include "y/counting/combination.hpp"
#include "y/system/exception.hpp"
#include "y/object/school-of.hpp"
#include "y/counting/c/comb.h"

namespace Yttrium
{


    apn Combination:: Cardinal(const size_t n, const size_t k)
    {
        assert(n>0);
        assert(k>0);
        assert(k<=n);
        return apn::Comb(n,k);
    }

    const char * const Combination::CallSign = "Combination";

    const char   * Combination:: callSign() const noexcept { return CallSign; }


    static inline size_t getCard(const size_t n, const size_t k)
    {
        if(n<1)   throw Specific::Exception(Combination::CallSign,"n<1");
        if(k<1)   throw Specific::Exception(Combination::CallSign,"k<1");
        if(k>n)   throw Specific::Exception(Combination::CallSign,"k>n");

        const apn np = Combination::Cardinal(n,k);
        return np.cast<size_t>(Combination::CallSign);
    }

    class Combination:: Code : public Object, public Memory::SchoolOf<size_t>
    {
    public:

        inline explicit Code(const size_t n,
                             const size_t k) :
        Object(),
        Memory::SchoolOf<size_t>(k),
        indx(cxx),
        comb()
        {
            Y_Comb_Init(&comb,n,k);
            Y_Comb_Boot(&comb,indx);
        }


        inline virtual ~Code() noexcept {}

        inline void boot() noexcept { Y_Comb_Boot(&comb,indx); }
        inline bool next() noexcept { return 0 != Y_Comb_Next(&comb,indx); }


        size_t * const indx;
        Y_Comb         comb;

    private:
        Y_Disable_Copy_And_Assign(Code);
    };

    Combination:: Combination(const size_t n, const size_t k) :
    Schedule( getCard(n,k)  ),
    code( new Code(n,k) )
    {
    }

    Combination:: ~Combination() noexcept
    {
        assert(0!=code);
        delete code;
        code = 0;
    }

    void Combination:: doBoot() noexcept
    {
        code->boot();
    }

    bool Combination:: doNext() noexcept
    {
        return code->next();
    }


    size_t Combination:: size() const noexcept
    {
        return code->comb.k;
    }

    size_t Combination:: capacity() const noexcept
    {
        return code->comb.k;
    }

#if 0
    const size_t & Combination:: operator[](const size_t i) const noexcept
    {
        assert(i>0);
        assert(i<=code->comb.k);
        return code->indx[i];
    }
#endif

    const size_t & Combination:: getItemAt(const size_t i) const noexcept
    {
        assert(i>0);
        assert(i<=code->comb.k);
        return code->indx[i];
    }



}
