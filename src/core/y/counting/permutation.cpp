#include "y/counting/permutation.hpp"
#include "y/exception.hpp"
#include "y/object/school-of.hpp"
#include "y/memory/allocator/pooled.hpp"
#include "y/counting/c/perm.h"

namespace Yttrium
{

    apn Permutation:: Cardinal(const size_t n)
    {
        return apn::Factorial(n);
    }

    const char * const Permutation::CallSign = "Permutation";

    const char * Permutation:: callSign() const noexcept { return CallSign; }

    static inline Cardinality getCard(const size_t n)
    {
        if(n<1) throw Specific::Exception(Permutation::CallSign,"n<1");
        const apn np = Permutation::Cardinal(n);
        return np.cast<Cardinality>(Permutation::CallSign);
    }

    class Permutation:: Code : public Memory::SchoolOf<size_t>
    {
    public:

        inline explicit Code(const size_t n) :
        Memory::SchoolOf<size_t>(n),
        perm()
        {
            Y_Perm_Init(&perm,n);
            Y_Perm_Boot(&perm,cxx);
        }


        inline virtual ~Code() noexcept {}

        inline void boot() noexcept { Y_Perm_Boot(&perm,cxx); }
        inline bool next() noexcept { return 0 != Y_Perm_Next(&perm,cxx); }


        Y_Perm         perm;

    private:
        Y_Disable_Copy_And_Assign(Code);
    };

    Permutation:: Permutation(const size_t n) :
    Schedule( getCard(n)  ),
    code( new Code(n) )
    {
    }

    Permutation:: ~Permutation() noexcept
    {
        assert(0!=code);
        delete code;
        code = 0;
    }

    void Permutation:: doBoot() noexcept
    {
        code->boot();
    }

    bool Permutation:: doNext() noexcept
    {
        return code->next();
    }


    size_t Permutation:: size() const noexcept
    {
        return code->perm.n;
    }

    size_t Permutation:: capacity() const noexcept
    {
        return code->perm.n;
    }

    const size_t & Permutation:: getItemAt(const size_t i) const noexcept
    {
        assert(i>0);
        assert(i<=code->perm.n);
        return code->cxx[i];
    }


}
