//! \file

#ifndef Y_MPI_Included
#define Y_MPI_Included 1

#include "y/singleton.hpp"
#include "y/concurrent/life-time.hpp"
#include "y/exception.hpp"
#include "y/system/wall-time.hpp"

//! disable mpicc
#define OMPI_SKIP_MPICXX 1
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
        static const char * const CallSign;                                     //!< "MPI"
        static const Longevity    LifeTime = LifeTimeOf:: MPI;                  //!< Life Time
        static const char *       HumanReadableThreadLevel(const int) noexcept; //!< \return thread level
        static const int          DefaultTag = 1;
        static const size_t       MaxCount   = IntegerFor<int>::Maximum;

        class Rate
        {
        public:
            Rate() noexcept;
            ~Rate() noexcept;
            Rate(const Rate &) noexcept;
            Rate & operator=(const Rate &) noexcept;

            uint64_t bytes;
            uint64_t ticks;

        };

        //______________________________________________________________________
        //
        //
        //! Exception
        //
        //______________________________________________________________________
        class Exception : public Yttrium:: Exception
        {
        public:
            //! setup \param err error code \param fmt C-style format
            Exception(const int err, const char * fmt,...) noexcept Y_Printf_Check(3,4);
            Exception(const Exception &) noexcept;      //!< duplicate
            virtual ~Exception()         noexcept;      //!< cleanup
            virtual const char * what() const noexcept; //!< \return info

        private:
            Y_Disable_Assign(Exception); //!< discarding
            char info[Length];           //!< info storage
        };

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual void display(std::ostream &, size_t) const;

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! MPI_Init, wrapper
        /**
         \param argc     for MPI_Init_Thread
         \param argv     for MPI_Init_Thread
         \param required for MPI_Init_Thread
         \return MPI instance, initialized
         */
        static MPI & Init(int *argc, char ***argv, const int required = MPI_THREAD_SINGLE);


        static int GetCount(const size_t count, const char * const func);

        //______________________________________________________________________
        //
        //
        // Point to point
        //
        //______________________________________________________________________
        void send(const void * const entry,
                  const size_t       count,
                  const MPI_Datatype datatype,
                  const int          dest,
                  const int          tag = DefaultTag);

        void recv(void * const entru,
                  const size_t count,
                  const MPI_Datatype datatype,
                  const int source,
                  const int tag = DefaultTag);

    public:
        const size_t       size;          //!< COMM_WORLD size
        const size_t       rank;          //!< COMM_WORLD rank
        const int          threadLevel;   //!< current thread level
        const bool         primary;       //!< primary flag
        const bool         replica;       //!< replica flag
        System::WallTime   chrono;        //!< chronometer
        const char * const processorName; //!< MPI_GetProcessorName
        Rate               sendRate;      //!< sending rate
        Rate               recvRate;      //!< receiving rate

    private:
        friend class Singleton<MPI,ClassLockPolicy>;
        Y_Disable_Copy_And_Assign(MPI); //!< discarding
        explicit MPI();                 //!< initialize by Init
        virtual ~MPI() noexcept;        //!< cleanup, MPI_Finalize()
    };

    //! helper to handle errors
#define Y_MPI_Call( CODE ) do { \
/**/ const int err = CODE;      \
/**/ if( MPI_SUCCESS != err ) throw MPI::Exception(err,"in '%s'",#CODE); \
} while(false)

#define Y_MPI_Mark() const uint64_t __mark__ = System::WallTime::Ticks()

}

#endif

