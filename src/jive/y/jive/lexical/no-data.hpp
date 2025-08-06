
//! \file

#ifndef Y_Jive_Lexical_NoData_Included
#define Y_Jive_Lexical_NoData_Included 1

#include "y/jive/tag.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Lexical
        {
            //__________________________________________________________________
            //
            //
            //
            //! creating a shared, empty tag
            //
            //
            //__________________________________________________________________
            class NoData
            {
            public:
                NoData();                        //!< setup
                NoData(const NoData &) noexcept; //!< duplicate
                ~NoData() noexcept;              //!< cleanup
                const Tag tag;                   //!< zero-length tag

            private:
                Y_Disable_Assign(NoData); //!< discarding
            };
        }

    }

}

#endif

