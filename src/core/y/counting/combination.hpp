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
        static apn Cardinal(const size_t n, const size_t k); //!< \param n n \param k k \return (n,k)

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        explicit Combination(const size_t n, const size_t k); //!< setup \param n n \param k k
        virtual ~Combination() noexcept;                      //!< cleanup

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual size_t         size()                   const noexcept; //!< \return k
        virtual size_t         capacity()               const noexcept; //!< \return k
        virtual const char   * callSign()               const noexcept; //!< \return CallSign

    private:
        Y_Disable_Copy_And_Assign(Combination); //!< discaring
        Code *code;  //!< inner code

        virtual void doBoot() noexcept;
        virtual bool doNext() noexcept;
        virtual const size_t & getItemAt(const size_t indx) const noexcept;
    };

}

#endif

