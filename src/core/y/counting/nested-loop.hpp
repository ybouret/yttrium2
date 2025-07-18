
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

        //! (prod(i=0:d-1) (n-i))/d!
        static Cardinality CardinalityFor(const size_t d, const size_t n);

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! d>=1, n>=d
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
        virtual const char * callSign() const noexcept; //!< CallSign

        //______________________________________________________________________
        //
        //
        // [Readable]
        //
        //______________________________________________________________________
        virtual size_t          size()                    const noexcept; //!< dimensions
        
    private:
        Y_Disable_Copy_And_Assign(NestedLoop);
        class Code;
        Code *code;

        virtual void doBoot() noexcept;
        virtual bool doNext() noexcept;
        virtual const size_t & getItemAt(const size_t indx) const noexcept;

    };


}

#endif

