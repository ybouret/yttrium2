//! \file

#ifndef Y_MPI_Included
#define Y_MPI_Included 1

#include "y/singleton.hpp"
#include "y/concurrent/life-time.hpp"
#include "y/exception.hpp"

//! disable mpicc
#define OMP_SKIP_MPICXX 1
#include <mpi.h>

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! MPI Instance
    //
    //
    //__________________________________________________________________________
    class MPI : public Singleton<MPI,ClassLockPolicy>
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        static const char * const CallSign;                     //!< "MPI"
        static const Longevity    LifeTime = LifeTimeOf:: MPI;  //!< Life Time
        static const char *   HumanReadableThreadLevel(const int) noexcept; //!< \return thread level


        //______________________________________________________________________
        //
        //
        //! Exception
        //
        //______________________________________________________________________
        class Exception : public Yttrium:: Exception
        {
        public:
            Exception(const int err, const char * fmt,...) noexcept Y_Printf_Check(3,4);
            Exception(const Exception &) noexcept;
            virtual ~Exception()         noexcept;
            virtual const char * what() const noexcept;

        private:
            Y_Disable_Assign(Exception); //!< discarding
            char info[Length];           //!< info storage
        };


        static MPI & Init(int *argc, char ***argv, const int required = MPI_THREAD_SINGLE);
        virtual void display(std::ostream &, size_t) const;


    public:
        const size_t       size;
        const size_t       rank;
        const int          threadLevel;
        const bool         primary;
        const bool         replica;
        const char * const processorName;
        
    private:
        Y_Disable_Copy_And_Assign(MPI);
        friend Singleton<MPI,ClassLockPolicy>;
        explicit MPI();
        virtual ~MPI() noexcept;
    };

#define Y_MPI_Call( CODE ) do { \
/**/ const int err = CODE;      \
/**/ if( MPI_SUCCESS != err ) throw MPI::Exception(err,"in '%s'",#CODE); \
} while(false)

}

#endif

