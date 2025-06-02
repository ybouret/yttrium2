
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
        typedef AliasLockPolicy<Object::Factory> DyadsLockPolicy;

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


            static const unsigned     MaxFactoryShift = Object::Factory::LIMIT_OBJECT_SHIFT;
            static const unsigned     MaxAllowedShift = Limits::MaxBlockShift;
            static const unsigned     NumFactoryShift = MaxFactoryShift+1;               //!< [0..MaxFactoryShift]
            static const unsigned     NumGreaterShift = MaxAllowedShift-MaxFactoryShift; //! [MaxFactoryShift+1..MaxAllowedShift]

            class Code;

            //__________________________________________________________________
            //
            //
            // Manager interface
            //
            //__________________________________________________________________
            class Manager
            {
            protected:
                explicit Manager(const unsigned blockShift) noexcept;
            public:
                virtual ~Manager() noexcept;

                const unsigned shift;
                const size_t   bytes;
                
            private:
                Y_Disable_Copy_And_Assign(Manager);
            };


            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void display(std::ostream &os,
                                 size_t        indentation) const;


            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

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

