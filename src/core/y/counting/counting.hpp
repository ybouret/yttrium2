//! \file

#ifndef Y_Counting_Included
#define Y_Counting_Included 1

#include "y/ability/identifiable.hpp"

namespace Yttrium
{

    typedef uint64_t Cardinality; //!< counting cardinality

    //__________________________________________________________________________
    //
    //
    //
    //! base class for counting objects
    //
    //
    //__________________________________________________________________________
    class Counting : public Identifiable
    {
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
    protected:
        explicit Counting(const Cardinality) noexcept; //!< setup total

    public:
        virtual ~Counting() noexcept; //!< cleanup

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        void boot() noexcept; //!< [re]boot state
        bool next() noexcept; //!< compute next state \return false when done

        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________
        const Cardinality  index; //!< moving index in 1..total
        const Cardinality  total; //!< fixed total number of configuration

    private:
        Y_Disable_Copy_And_Assign(Counting); //!< discarding
        virtual void doBoot() noexcept = 0;  //!< boot indices
        virtual bool doNext() noexcept = 0;  //!< next indices \return false when done
    };

}


#endif

