
#include "y/mpi++/api.hpp"
#include "y/type/temporary.hpp"
#include "y/xml/attribute.hpp"

namespace Yttrium
{

    const char * const MPI:: CallSign = "MPI";

    int MPI:: GetCount(const size_t count, const char * const func)
    {
        assert(func);
        if(count>MaxCount) throw Specific::Exception(func,"count overflow");
        return (int) count;
    }

    MPI:: ~MPI() noexcept
    {
        MPI_Finalize();
    }

    const char *   MPI:: HumanReadableThreadLevel(const int t) noexcept
    {
        switch(t)
        {
                Y_Return_Named_Case(MPI_THREAD_SINGLE);
                Y_Return_Named_Case(MPI_THREAD_FUNNELED);
                Y_Return_Named_Case(MPI_THREAD_SERIALIZED);
                Y_Return_Named_Case(MPI_THREAD_MULTIPLE);
            default:
                break;
        }
        return Core::Unknown;

    }


    namespace
    {
        static bool     __mpi_auth = false;
        static int *    __mpi_argc = 0;
        static char *** __mpi_argv = 0;
        static int      __mpi_cntl = 0;
        static char     __mpi_processor_name[MPI_MAX_PROCESSOR_NAME] = { 0 };
    }

    MPI & MPI:: Init(int *argc, char ***argv, const int required)
    {
        if( Exists() ) throw Specific::Exception(CallSign,"already initialized");

        const Temporary<int>      _1(__mpi_cntl,required);
        const Temporary<int *>    _2(__mpi_argc,argc);
        const Temporary<char ***> _3(__mpi_argv,argv);
        const Temporary<bool>     _4(__mpi_auth,true);


        return Instance();
    }

    void MPI:: display(std::ostream &os, size_t indent) const
    {
        initProlog(os,indent) << Y_XML_Attr(size) << Y_XML_Attr(rank) << Y_XML_Attr(processorName);
        //initEpilog(os,true);
        initEpilog(os,false);
        for(DataType::Set::ConstIterator it=dts.begin();it!=dts.end();++it)
        {
            const DataType &dt = **it;

            XML::Indent(std::cerr,indent+1) << "type='" << dt.uuid << "'";
            std::cerr << std::endl;
        }
        quit(os,indent);
    }

    MPI:: MPI() :
    Concurrent::Member(1,0),
    threadLevel(-1),
    primary(true),
    replica(false),
    parallel(size>1),
    sendRate(),
    recvRate(),
    processorName(__mpi_processor_name),
    dts()
    {
        if(!__mpi_auth) throw Specific:: Exception(CallSign,"must call Init(...)");

        Y_MPI_Call( MPI_Init_thread(__mpi_argc, __mpi_argv, __mpi_cntl, & Coerce(threadLevel)) );

        {
            int sz = 0;
            Y_MPI_Call( MPI_Comm_size(MPI_COMM_WORLD, &sz) );
            Coerce(size) = (size_t) sz;
        }

        {
            int rk = 0;
            Y_MPI_Call( MPI_Comm_size(MPI_COMM_WORLD, &rk) );
            Coerce(rank) = (size_t) rk;
            Coerce(indx) = rank+1;
        }

        if(0!=rank) CoerceSwap(primary,replica);

        {
            int res = 0;
            Y_MPI_Call( MPI_Get_processor_name(__mpi_processor_name,&res) );
        }

        buildDTS();

    }

}
