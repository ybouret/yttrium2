
#ifndef Y_Counting_Permutation_Included
#define Y_Counting_Permutation_Included 1

#include "y/counting/schedule.hpp"
#include "y/apex/natural.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! Permutation of n (n!)
    //
    //
    //__________________________________________________________________________
    class Permutation : public Schedule
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        static const char * const CallSign;  //!< "Permutation"
        static apn Cardinal(const size_t n); //!< \param n items to permute \return n!

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        explicit Permutation(const size_t n); //!< setup \param n items to permute
        virtual ~Permutation() noexcept;      //!< cleanup

        virtual size_t         size()                   const noexcept; //!< \return n
        virtual size_t         capacity()               const noexcept; //!< \return n
        virtual const char    *callSign()               const noexcept; //!< \return CallSign

    private:
        class Code;
        Y_Disable_Copy_And_Assign(Permutation); //!< discarding
        Code *code; //!< inner code

        virtual void doBoot() noexcept;
        virtual bool doNext() noexcept;
        virtual const size_t & getItemAt(const size_t indx) const noexcept;
    };

}

#endif

