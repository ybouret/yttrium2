
//! \file

#ifndef Y_Memory_Quanta_Included
#define Y_Memory_Quanta_Included 1

#include "y/memory/object/factory.hpp"
#include "y/memory/limits.hpp"
#include "y/concurrent/singleton/alias-lock-policy.hpp"
#include "y/memory/allocator.hpp"

namespace Yttrium
{
    namespace Memory
    {
        typedef AliasLockPolicy<Object::Factory> QuantaLockPolicy; //!< policy alias

        //______________________________________________________________________
        //
        //
        //
        //! produce all possible, reusable power-of-two blocks
        /**
         - uses Object::Factory for small blocks
         - uses Object::Book    for large blocks
         */
        //
        //______________________________________________________________________
        class Quanta :
        public Singleton<Quanta,QuantaLockPolicy>,
        public Allocator
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign;                             //!< "Memory::Dyads"
            static const Longevity    LifeTime = LifeTimeOf:: MemoryQuanta; //!< life time


            static const unsigned     MaxFactoryShift = Object::Factory::LIMIT_OBJECT_SHIFT; //!< alias
            static const unsigned     MaxAllowedShift = Limits::MaxBlockShift;               //!< alias
            static const unsigned     NumFactoryShift = MaxFactoryShift+1;                   //!< [0..MaxFactoryShift]
            static const unsigned     NumGreaterShift = MaxAllowedShift-MaxFactoryShift;     //!< [MaxFactoryShift+1..MaxAllowedShift]
            static const size_t       MaxAllowedBytes = Limits::MaxBlockBytes;               //!< alias

            class Code;

            //__________________________________________________________________
            //
            //
            //! Manager interface for given bytes=2^shift
            //
            //__________________________________________________________________
            class Manager
            {
            protected:
                //! initialize \param blockShift blocSize=2^blockShift
                explicit Manager(const unsigned blockShift) noexcept;
            public:
                //! cleanup
                virtual ~Manager() noexcept;

                virtual void * acquire()                      = 0;  //!< \return a new block
                virtual void   release(void * const) noexcept = 0;  //!< release a previously acquired block

                const unsigned shift; //!< shift
                const size_t   bytes; //!< 2^shift

            private:
                Y_Disable_Copy_And_Assign(Manager); //!< discarding
            };


            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void display(std::ostream &,size_t) const;


            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! acquire any power of two bytes memory area
            /**
             \param blockShift block shift
             \return 2^blockShift bytes memory area
             */
            void *acquireDyadic(const unsigned blockShift);

            //! release a previously acquired block
            /**
             \param blockAddr block address
             \param blockShift block is 2^blockShift bytes
             */
            void  releaseDyadic(void * const blockAddr, const unsigned blockShift) noexcept;

        private:
            Y_Disable_Copy_And_Assign(Quanta); //!< discarding
            explicit Quanta();                 //!< setup
            virtual ~Quanta() noexcept;        //!< cleanup
            Code * const code;                //!< internal code
            friend class Singleton<Quanta,QuantaLockPolicy>;

            virtual void * acquireBlock(size_t&);
            virtual void   releaseBlock(void * const, const size_t) noexcept;

        };


    }

}

#endif

