//! \file

#ifndef Y_MPI_Included
#define Y_MPI_Included 1

#include "y/singleton.hpp"
#include "y/concurrent/life-time.hpp"
#include <mpi.h>

namespace Yttrium
{

    class MPI : public Singleton<MPI,ClassLockPolicy>
    {
    public:
        static const char * const CallSign;
        static const Longevity    LifeTime = LifeTimeOf:: MPI;

        static MPI & Init(int *argc, char ***argv, const int required);

    private:
        Y_Disable_Assign(MPI);
        explicit MPI();
        virtual ~MPI() noexcept;
    };
}

#endif

