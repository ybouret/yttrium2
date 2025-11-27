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
#include "y/static/moniker.hpp"



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

        //! send data, low-level
        /**
         \param entry    data entry
         \param count    block count
         \param datatype MPI data type
         \param bytes    bytes for data
         \param dest     destination
         \param tag      tag
         */
        void send(const void * const entry,
                  const size_t       count,
                  const MPI_Datatype datatype,
                  const uint64_t     bytes,
                  const size_t       dest,
                  const int          tag);

        //! recv data, low-level
        /**
         \param entry    data entry
         \param count    block count
         \param datatype MPI data type
         \param bytes    bytes for data
         \param source   source
         \param tag      tag
         */
        void recv(void * const       entry,
                  const size_t       count,
                  const MPI_Datatype datatype,
                  const uint64_t     bytes,
                  const size_t       source,
                  const int          tag);


        void sendrecv(const void * const sendEntry,
                      const size_t       sendCount,
                      const MPI_Datatype sendDatatype,
                      const uint64_t     sendBytes,
                      const size_t       sendTarget,
                      const int          sendTag,
                      void * const       recvEntry,
                      const size_t       recvCount,
                      const MPI_Datatype recvDatatype,
                      const uint64_t     recvBytes,
                      const size_t       recvSource,
                      const int          recvTag);


        //! send generic data, low-level
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

        //! receive generic data, low-level
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

        template <typename T, typename U> inline
        void sendrecv(const T * const sendEntry,
                      const size_t    sendCount,
                      const size_t    sendTarget,
                      const int       sendTag,
                      U * const       recvEntry,
                      const size_t    recvCount,
                      const size_t    recvSource,
                      const int       recvTag)
        {
            static const DataType   & t_dt       = getDataTypeOf<T>();
            static const DataType   & u_dt       = getDataTypeOf<U>();
            static const MPI_Datatype t_datatype = t_dt.type();
            static const MPI_Datatype u_datatype = u_dt.type();

            sendrecv(sendEntry,sendCount,t_datatype,t_dt.bytesFor(sendCount), sendTarget, sendTag,
                     recvEntry,recvCount,u_datatype,u_dt.bytesFor(recvCount), recvSource, recvTag);

        }

        template <typename T> inline
        void sendrecv(const T * const sendEntry,
                      const size_t    sendCount,
                      const size_t    sendTarget,
                      T * const       recvEntry,
                      const size_t    recvCount,
                      const size_t    recvSource,
                      const int       tag =  DefaultTag)
        {
            sendrecv<T,T>(sendEntry,sendCount,sendTarget,tag,
                          recvEntry,recvCount,recvSource,tag);
        }



        //! utility send block of bytes
        /**
         \param entry data address
         \param count number of bytes
         \param dest  destination
         \param tag   tag
         */
        void    sendBlock(const void * const entry,
                          const size_t       count,
                          const size_t       dest,
                          const int          tag);

        //! utility recv block of bytes
        /**
         \param entry  data address
         \param count  number of bytes
         \param source originia
         \param tag    tag
         */
        void    recvBlock(void * const entry,
                          const size_t count,
                          const size_t source,
                          const int    tag);

        //! utility to send a size_t
        /**
         \param value to be sent
         \param dest  destination
         \param tag   tag
         */
        void   sendCount(const size_t value,
                         const size_t dest,
                         const int    tag);

        //! utility to receive a size_t
        /**
         \param source origin
         \param tag    tag
         \param varName optional variable name
         */
        size_t recvCount(const size_t       source,
                         const int          tag,
                         const char * const varName = 0);


        void syn(const size_t source);       //!< \param source wait for info from source
        void ack(const size_t target);       //!< \param target send info to targert
        void syncWith(const size_t target);  //!< \param target ack then syn with target




        // for arithmetic types
        template <typename T> struct Plain
        {
            static  const bool    Used = TypeTraits<T>::IsArithmetic;
            typedef T             Type;
            static const unsigned DIMS = 1;

            static inline void Send(MPI        & mpi,
                                    const Type & value,
                                    const size_t target,
                                    const int    tag)
            {
                mpi.send(&value,1,target,tag);
            }

            static inline Type Recv(MPI        & mpi,
                                    const size_t source,
                                    const int    tag)
            {
                Static::Moniker<Type> temp;
                mpi.recv(& *temp, 1, source, tag);
                return *temp;

            }
        };

        // for straight compact linear types
        template <typename T, template <typename> class LINEAR> struct Plain< LINEAR<T> >
        {
            typedef LINEAR<T>     Type;
            static const bool     Derived = Y_Is_SuperSubClass(Readable<T>,Type);
            static const unsigned DIMS    = sizeof(LINEAR<T>)/sizeof(T);
            static const bool     Used    = TypeTraits<T>::IsArithmetic && !Derived;

            static inline void Send(MPI &            mpi,
                                    const Type &     value,
                                    const size_t     target,
                                    const int        tag)
            {
                mpi.send( (T *) &value, DIMS, target, tag);
            }

            static inline Type Recv(MPI        & mpi,
                                    const size_t source,
                                    const int    tag)
            {
                Static::Moniker<Type> temp;
                mpi.recv( (T *)& *temp, DIMS, source, tag);
                return *temp;
            }

        };


        //! for specific types
        template <typename T> struct Codec
        {
            static void Send(MPI &, const T &, const size_t, const int);
            static T    Recv(MPI &, const size_t, const int);
        };


        template <typename T> struct IO
        {
        public:
            static const bool UsePlain = Plain<T>::Used;
            typedef typename Pick<UsePlain,Plain<T>,Codec<T>>::Type API;

            template <typename CONTIGUOUS> static inline
            void Send(MPI                   & mpi,
                      const CONTIGUOUS      & arr,
                      const size_t            target,
                      const int               tag)
            {
                static const IntToType<UsePlain> way = {};
                Send(way,mpi,arr,target,tag);
            }

            template <typename CONTIGUOUS> static inline
            void Recv(MPI                   & mpi,
                      CONTIGUOUS            & arr,
                      const size_t            source,
                      const int               tag)
            {
                static const IntToType<UsePlain> way = {};
                Recv(way,mpi,arr,source,tag);
            }

        private:
            template <typename CONTIGUOUS>
            static inline void Send(const IntToType<true> &,
                                    MPI                   & mpi,
                                    const CONTIGUOUS      & arr,
                                    const size_t            target,
                                    const int               tag)
            {
                const size_t sz = arr.size();
                if(sz>0)
                    mpi.send( (const T *)&arr[1],sz*Plain<T>::DIMS,target,tag);
            }

            template <typename CONTIGUOUS>
            static inline void Recv(const IntToType<true> &,
                                    MPI                   & mpi,
                                    CONTIGUOUS            & arr,
                                    const size_t            source,
                                    const int               tag)

            {
                const size_t sz = arr.size();
                if(sz>0)
                    mpi.recv( (T* )&arr[1],sz*Plain<T>::DIMS,source,tag);
            }

            template <typename CONTIGUOUS>
            static inline void Send(const IntToType<false> &,
                                    MPI                   & mpi,
                                    const CONTIGUOUS      & arr,
                                    const size_t            target,
                                    const int               tag)
            {
                for(size_t i=arr.size();i>0;--i)
                    Codec<T>::Send(mpi,arr[i],target,tag);
            }


            template <typename CONTIGUOUS>
            static inline void Recv(const IntToType<false> &,
                                    MPI                   & mpi,
                                    CONTIGUOUS            & arr,
                                    const size_t            source,
                                    const int               tag)

            {
                for(size_t i=arr.size();i>0;--i)
                    Codec<T>::Recv(mpi,arr[i],source,tag);
            }

        };



        template <typename T> inline
        void send1(const T &    arg,
                   const size_t target,
                   const int    tag = DefaultTag)
        {
            IO<T>::API::Send(*this,arg,target,tag);
        }

        template <typename T> inline
        T recv1(const size_t source,
                const int    tag = DefaultTag )
        {
            return IO<T>::API::Recv(*this,source,tag);
        }

        template <typename T> inline
        void load1(T &arg, const size_t source, const int tag = DefaultTag)
        {
            arg = recv1<T>(source,tag);
        }

        template <typename CONTIGUOUS> inline
        void sendN(const CONTIGUOUS &arr,
                   const size_t      target,
                   const int         tag = DefaultTag)
        {
            IO< typename CONTIGUOUS::Type >::Send(*this,arr,target,tag);
        }


        template <typename CONTIGUOUS> inline
        void recvN(  CONTIGUOUS &arr,
                   const size_t  source,
                   const int     tag = DefaultTag)
        {
            IO< typename CONTIGUOUS::Type >::Recv(*this,arr,source,tag);
        }





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
#define Y_MPI_Gain() (System::WallTime::Ticks() - __mark__)

#define  Y_MPI_ForEach(THE_MPI,CODE) do \
/**/    { \
/**/        MPI &mpi_ = (THE_MPI); \
/**/        if(mpi_.primary) \
/**/        {\
/**/            do { CODE; } while(false); \
/**/            for(size_t rank=1;rank<mpi_.size;++rank) \
/**/                mpi_.syncWith(rank);\
/**/        }\
/**/        else\
/**/        {\
/**/            mpi_.syn(0);\
/**/            do { CODE; } while(false); \
/**/            mpi_.ack(0);\
/**/        }\
/**/    } while(false)
}

#endif // !Y_MPI_Included

