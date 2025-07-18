//! \file

#ifndef Y_Counting_Partition_Included
#define Y_Counting_Partition_Included 1

#include "y/counting/schedule.hpp"
#include "y/apex/natural.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! Partition of n
    //
    //
    //__________________________________________________________________________
    class Partition : public Schedule
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        static const char * const CallSign;  //!< "Partition"
        static apn Cardinal(const size_t n); //!< from Euler's formula

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        explicit Partition(const size_t n); //!< integer to part
        virtual ~Partition() noexcept;      //!< cleanup

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual const char * callSign()  const noexcept; //!< CallSign
        virtual size_t       size()      const noexcept; //!< current parts

    private:
        Y_Disable_Copy_And_Assign(Partition);
        class Code;
        Code *code;

        virtual void           doBoot() noexcept;
        virtual bool           doNext() noexcept;
        virtual const size_t & getItemAt(const size_t) const noexcept;

    };
    

}

#endif

