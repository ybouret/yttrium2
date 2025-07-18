
#ifndef Y_Counting_Schedule_Included
#define Y_Counting_Schedule_Included 1

#include "y/counting/counting.hpp"
#include "y/container/readable.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! base class for counting as array of indices
    //
    //
    //__________________________________________________________________________
    class Schedule : public Counting, public Readable<size_t>
    {
    protected:
        explicit Schedule(const Cardinality) noexcept; //!< setup with cardinality
    public:
        virtual ~Schedule() noexcept;                  //!< cleanup
        
    private:
        Y_Disable_Copy_And_Assign(Schedule); //!< discarding
    };

}

#endif
