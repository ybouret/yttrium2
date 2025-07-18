
#ifndef Y_Counting_Nested_Loop_Included
#define Y_Counting_Nested_Loop_Included 1

#include "y/counting/schedule.hpp"

namespace Yttrium
{    

    //__________________________________________________________________________
    //
    //
    //
    //! loop (i=1:n,j=i+1:n,k=j+1:n,...)
    //
    //
    //__________________________________________________________________________
    class NestedLoop : public Schedule
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        static const char * const CallSign; //!< "NestedLoop"

        //! \param d dim \param n count \return (prod(i=0:d-1) (n-i))/d!
        static Cardinality CardinalityFor(const size_t d, const size_t n);

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup \param d d>=1 \param n n>=d
        explicit NestedLoop(const size_t d,
                            const size_t n);

        //! cleanup
        virtual ~NestedLoop() noexcept;

        //______________________________________________________________________
        //
        //
        // [Identifiable]
        //
        //______________________________________________________________________
        virtual const char * callSign() const noexcept; //!< \return CallSign

        //______________________________________________________________________
        //
        //
        // [Readable]
        //
        //______________________________________________________________________
        virtual size_t          size() const noexcept; //!< \return dimensions

    private:
        class Code;
        Y_Disable_Copy_And_Assign(NestedLoop); //!< discarding
        Code *code; //!< inner code

        virtual void doBoot() noexcept;
        virtual bool doNext() noexcept;
        virtual const size_t & getItemAt(const size_t indx) const noexcept;

    };


}

#endif

