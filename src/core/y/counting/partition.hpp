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
        static apn Cardinal(const size_t n); //!< \return from Euler's formula \param n integer to part

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        explicit Partition(const size_t n); //!< \param n integer to part
        virtual ~Partition() noexcept;      //!< cleanup

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual const char * callSign()  const noexcept; //!< \return CallSign
        virtual size_t       size()      const noexcept; //!< \return current parts

    private:
        class Code;
        Y_Disable_Copy_And_Assign(Partition); //!< discarding
        Code *code; //!< inner code

        virtual void           doBoot() noexcept;
        virtual bool           doNext() noexcept;
        virtual const size_t & getItemAt(const size_t) const noexcept;

    };
    

}

#endif

