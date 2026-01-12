//! \file

#ifndef Y_Apex_Lock_Included
#define Y_Apex_Lock_Included 1

#include "y/ability/lockable.hpp"

namespace Yttrium
{

    extern Lockable & ApexGiantLock(); //!< \return memory access lock

    //! lock memory access, mostly to display within threads
#define Y_Apex_Giant_Lock() Y_Lock( ApexGiantLock() )


}

#endif // !Y_Apex_Lock_Included
