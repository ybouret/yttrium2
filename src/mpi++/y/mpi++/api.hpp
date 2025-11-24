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

#include "y/concurrent/member.hpp"

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
    class MPI : public Singleton<MPI,ClassLockPolicy>, public Concurrent::Member
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


        typedef Protean::BareHeavyList<const MPI_Datatype> DTList; //!< alias
        typedef DTList::NodeType                           DTNode; //!< alias

        //______________________________________________________________________
        //
        //
        //! Extended DataType
        //
        //______________________________________________________________________
        class DataType : public CountedObject
        {
        public:
            //__________________________________________________________________
            //
            // Definitions
            //__________________________________________________________________
            typedef ArcPtr<DataType>        PtrType; //!< alias
            typedef Keyed<String,PtrType>   Pointer; //!< alias
            typedef HashSet<String,Pointer> Set;     //!< alias

            //__________________________________________________________________
            //
            // C++
            //__________________________________________________________________

            //! setup
            /**
             \param dt MPI_Datatype
             \param sh integer log2 of type size
             \param ti system type id
             */
            explicit DataType(MPI_Datatype          dt,
                              const unsigned        sh,
                              const std::type_info &ti);

            //! cleanup
            virtual ~DataType() noexcept;

            //__________________________________________________________________
            //
            // Methods
            //__________________________________________________________________
            const String & key()         const noexcept; //!< \return identifier
            MPI_Datatype   type()        const noexcept; //!< \return head type
            uint64_t       bytesFor(const size_t) const; //!< \return check count to bytes

            //__________________________________________________________________
            //
            // Members
            //__________________________________________________________________
            const DTList   list; //!< matching data types
            const unsigned ishl; //!< left shift
            const String   uuid; //!< identifier

        private:
            Y_Disable_Copy_And_Assign(DataType); //!< discarding
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

        //! helper to declare MPI_Datatype for a given type
        void decl(MPI_Datatype, const unsigned , const std::type_info &);


        //! \return DataType for declared, matching type id
        const DataType & getDataType( const std::type_info & ) const;

        //! \return DataType for declared, matching type
        template <typename T> inline
        const DataType & getDataTypeOf() const
        {
            static const DataType & dt = getDataType( typeid(T) );
            return dt;
        }

        //______________________________________________________________________
        //
        //
        // Point to point
        //
        //______________________________________________________________________

        //! send data
        /**
         \param entry data entry
         \param count block count
         \param datatype MPI data type
         \param bytes bytes for data
         \param dest  destination
         \param tag   tag
         */
        void send(const void * const entry,
                  const size_t       count,
                  const MPI_Datatype datatype,
                  const uint64_t     bytes,
                  const size_t       dest,
                  const int          tag);

        //! recv data
        /**
         \param entry    data entry
         \param count    block count
         \param datatype MPI data type
         \param bytes    bytes for data
         \param source  source
         \param tag     tag
         */
        void recv(void * const       entry,
                  const size_t       count,
                  const MPI_Datatype datatype,
                  const uint64_t     bytes,
                  const size_t       source,
                  const int          tag);

        //! send data
        /**
         \param entry data entry
         \param count block count
         \param dest  destination
         \param tag   tag
         */
        template <typename T> inline
        void send(const T * const entry,
                  const size_t    count,
                  const size_t    dest,
                  const int       tag = DefaultTag )
        {
            static const DataType &   dt       = getDataTypeOf<T>();
            static const MPI_Datatype datatype = dt.type();
            send(entry,count,datatype,dt.bytesFor(count),dest,tag);
        }

        //! receive data
        /**
         \param entry  data entry
         \param count  block count
         \param source source
         \param tag    tag
         */
        template <typename T> inline
        void recv(T * const    entry,
                  const size_t count,
                  const size_t source,
                  const int    tag = DefaultTag )
        {
            static const DataType &   dt       = getDataTypeOf<T>();
            static const MPI_Datatype datatype = dt.type();
            recv(entry,count,datatype,dt.bytesFor(count),source,tag);
        }

        void sendBlock(const void * const entry,
                       const size_t       count,
                       const size_t       dest,
                       const int          tag = DefaultTag);

        void recvBlock(void * const entry,
                       const size_t count,
                       const size_t source,
                       const int    tag = DefaultTag);



    public:
        const int           threadLevel;   //!< current thread level
        const bool          primary;       //!< primary flag
        const bool          replica;       //!< replica flag
        const bool          parallel;      //!< size>1
        Rate                sendRate;      //!< sending rate
        Rate                recvRate;      //!< receiving rate
        const char * const  processorName; //!< MPI_GetProcessorName
        const DataType::Set dts;           //!< DataType set

    private:
        friend class Singleton<MPI,ClassLockPolicy>;
        Y_Disable_Copy_And_Assign(MPI); //!< discarding
        explicit MPI();                 //!< initialize by Init
        virtual ~MPI() noexcept;        //!< cleanup, MPI_Finalize()
        void buildDTS();                //!< build DataType Set
    };

    //! helper to handle errors
#define Y_MPI_Call( CODE ) do { \
/**/ const int err = CODE;      \
/**/ if( MPI_SUCCESS != err ) throw MPI::Exception(err,"in '%s'",#CODE); \
} while(false)

#define Y_MPI_Mark() const uint64_t __mark__ = System::WallTime::Ticks()

}

#endif // !Y_MPI_Included

