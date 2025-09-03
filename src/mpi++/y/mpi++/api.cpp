
#include "y/mpi++/api.hpp"

namespace Yttrium
{

    const char * const MPI:: CallSign = "MPI";

    MPI:: ~MPI() noexcept
    {
        MPI_Finalize();
    }


    namespace
    {
        static int *    __mpi_argc = 0;
        static char *** __mpi_argv = 0;
        static int      __mpi_cntl = 0;
    }

    MPI & MPI:: Init(int *argc, char ***argv, const int required)
    {
    }


    MPI:: MPI()
    {

    }

}
