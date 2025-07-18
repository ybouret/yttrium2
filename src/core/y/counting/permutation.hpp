
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
        class Code;
        static const char * const CallSign;  //!< "Permutation"
        static apn Cardinal(const size_t n); //!< n!

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        explicit Permutation(const size_t n); //!< setup
        virtual ~Permutation() noexcept;      //!< cleanup

        virtual size_t         size()                   const noexcept; //!< n
        virtual size_t         capacity()               const noexcept; //!< n
        virtual const char    *callSign()               const noexcept; //!< CallSign

    private:
        Y_Disable_Copy_And_Assign(Permutation);
        Code *code;

        virtual void doBoot() noexcept;
        virtual bool doNext() noexcept;
        virtual const size_t & getItemAt(const size_t indx) const noexcept;
    };

}

#endif

