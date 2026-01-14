
//! \file

#ifndef Y_Information_Pack_Category_Included
#define Y_Information_Pack_Category_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{

    namespace Information
    {
        namespace Pack
        {
            //! type of usage
            enum Category
            {
                Streaming=0x1, //!< +NYT, -EOS
                Messaging=0x2  //!< +NYT, +EOS
            };
        }
        
    }

}

#endif // !Y_Information_Pack_Category_Included

