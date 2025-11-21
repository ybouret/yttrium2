//! \file

#ifndef Y_MPI_Included
#define Y_MPI_Included 1

#include "y/singleton.hpp"
#include "y/concurrent/life-time.hpp"
#include "y/exception.hpp"
#include "y/system/wall-time.hpp"
#include "y/string.hpp"
#include "y/pointer/arc.hpp"
#include "y/pointer/keyed.hpp"
#include "y/container/associative/hash/set.hpp"
#include "y/protean/bare/heavy/list.hpp"
#include <typeinfo>

//! disable mpicxx
#define OMPI_SKIP_MPICXX 1

//! disable mpicxx
#define MPICH_SKIP_MPICXX 1

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
        static const int          DefaultTag = 1;                               //!< default tag
        static const size_t       MaxCount   = IntegerFor<int>::Maximum;        //!< for int/size_t conversion


        typedef Protean::BareHeavyList<const MPI_Datatype> DTList;

        class DataType : public CountedObject
        {
        public:
            typedef ArcPtr<DataType>        PtrType; //!< alias
            typedef Keyed<String,PtrType>   Pointer; //!< alias
            typedef HashSet<String,Pointer> Set;

            virtual ~DataType() noexcept;
            explicit DataType(MPI_Datatype          dt,
                              const size_t          sz,
                              const std::type_info &ti);
            
            const String & key() const noexcept;

            const DTList list;
            const size_t size;
            const String uuid;


        private:
            Y_Disable_Copy_And_Assign(DataType);
        };

        //______________________________________________________________________
        //
        //
        //! Rate for statistics
        //
        //______________________________________________________________________
        class Rate
        {
        public:
            //__________________________________________________________________
            //
            // C++
            //__________________________________________________________________
            Rate()                         noexcept; //!< setup
            ~Rate()                        noexcept; //!< cleanup
            Rate(const Rate &)             noexcept; //!< duplicate
            Rate & operator=(const Rate &) noexcept; //!< assign \return *this

            //__________________________________________________________________
            //
            // Members
            //__________________________________________________________________
            uint64_t bytes; //!< cumulative bytes
            uint64_t ticks; //!< cumulative ticks
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

        //! convert size to int
        /**
         \param count users's count
         \param func  name of the function where conversion occurs
         \return converted with checkw
         */
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

        void recv(void * const       entry,
                  const size_t       count,
                  const MPI_Datatype datatype,
                  const int          source,
                  const int          tag = DefaultTag);

        void decl(MPI_Datatype          dt,
                  const size_t          sz,
                  const std::type_info &ti);

        void buildDTS();

    public:
        const size_t        size;          //!< COMM_WORLD size
        const size_t        rank;          //!< COMM_WORLD rank
        const int           threadLevel;   //!< current thread level
        const bool          primary;       //!< primary flag
        const bool          replica;       //!< replica flag
        System::WallTime    chrono;        //!< chronometer
        const char * const  processorName; //!< MPI_GetProcessorName
        Rate                sendRate;      //!< sending rate
        Rate                recvRate;      //!< receiving rate
        const DataType::Set dts;

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

