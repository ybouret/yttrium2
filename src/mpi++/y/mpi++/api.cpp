
#include "y/mpi++/api.hpp"
#include "y/system/exception.hpp"
#include "y/type/temporary.hpp"
#include "y/xml/attribute.hpp"

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
        if( Exists() ) throw Specific::Exception(CallSign,"already initialized");

        Temporary<int>      (__mpi_cntl,required);
        Temporary<int *>    (__mpi_argc,argc);
        Temporary<char ***> (__mpi_argv,argv);

        return Instance();
    }

    void MPI:: display(std::ostream &os, size_t indent) const
    {
        initProlog(os,indent);
        initEpilog(os,true);
    }

    MPI:: MPI() : threadLevel(-1)
    {
        
    }

}
