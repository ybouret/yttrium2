
//! \file

#ifndef Y_Memory_Dyads_Included
#define Y_Memory_Dyads_Included 1

#include "y/memory/object/factory.hpp"
#include "y/memory/limits.hpp"
#include "y/concurrent/singleton/alias-lock-policy.hpp"

namespace Yttrium
{
    namespace Memory
    {
        typedef AliasLockPolicy<Object::Factory> DyadsLockPolicy; //!< policy alias

        //______________________________________________________________________
        //
        //
        //
        //! produce all possible power-of-two blocks
        //
        //
        //______________________________________________________________________
        class Dyads : public Singleton<Dyads,DyadsLockPolicy>
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign;                            //!< "Memory::Dyads"
            static const Longevity    LifeTime = LifeTimeOf:: MemoryDyads; //!< life time


            static const unsigned     MaxFactoryShift = Object::Factory::LIMIT_OBJECT_SHIFT; //!< alias
            static const unsigned     MaxAllowedShift = Limits::MaxBlockShift;               //!< alias
            static const unsigned     NumFactoryShift = MaxFactoryShift+1;                   //!< [0..MaxFactoryShift]
            static const unsigned     NumGreaterShift = MaxAllowedShift-MaxFactoryShift;     //!< [MaxFactoryShift+1..MaxAllowedShift]

            class Code;

            //__________________________________________________________________
            //
            //
            //! Manager interface
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

            //! acquire a power of two large block
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
            Y_Disable_Copy_And_Assign(Dyads); //!< discarding
            explicit Dyads();                 //!< setup
            virtual ~Dyads() noexcept;        //!< cleanup
            Code * const code;                //!< internal code
            friend class Singleton<Dyads,DyadsLockPolicy>;
        };


    }

}

#endif

