#ifndef Y_Counting_Combination_Included
#define Y_Counting_Combination_Included 1

#include "y/counting/schedule.hpp"
#include "y/apex/natural.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! (n,k))
    //
    //
    //__________________________________________________________________________
    class Combination : public Schedule
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        class Code;
        static const char * const CallSign;  //!< "Combination"
        static apn Cardinal(const size_t n, const size_t k); //!< (n,k)

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        explicit Combination(const size_t n, const size_t k); //!< setup
        virtual ~Combination() noexcept;                      //!< cleanup

        virtual size_t         size()                   const noexcept; //!< k
        virtual size_t         capacity()               const noexcept; //!< k
        virtual const char   * callSign()               const noexcept; //!< CallSign

    private:
        Y_Disable_Copy_And_Assign(Combination);
        Code *code;

        virtual void doBoot() noexcept;
        virtual bool doNext() noexcept;
        virtual const size_t & getItemAt(const size_t indx) const noexcept;
    };

}

#endif

