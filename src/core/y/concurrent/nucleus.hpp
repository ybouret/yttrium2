
//! \file

#ifndef Y_Concurrent_Nucleus_Included
#define Y_Concurrent_Nucleus_Included 1

#include "y/concurrent/singulet.hpp"
#include "y/system/platform.hpp"

namespace Yttrium
{

    namespace Concurrent
    {
        //______________________________________________________________________
        //
        //
        //
        //! Internal Singleton holding top-level giant mutex
        //
        //
        //______________________________________________________________________
        class Nucleus : public Singulet
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitiosn
            //
            //__________________________________________________________________
            static const char * const CallSign;                              //!< "Concurrent::Nucleus"
            static const Longevity    LifeTime = Singulet::GreatestLifeTime; //!< oldest
            static const size_t       Replicae = 4;                          //!< internal low-level mutexes
            class        Code;

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________

            //! [Identifiable]
            /** \return CallSign */
            virtual const char * callSign() const noexcept;

            //! [Singulet]
            /** \return LifeTime */
            virtual Longevity    lifeTime() const noexcept;

            //! [Singulet]
            /** \return internal mutex */
            virtual Lockable & access() noexcept;

            //! [XML::Element]
            virtual void display(std::ostream &,size_t) const;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! query on of the replica mutex
            /**
             \return persistent lockable interface  
             */
            Lockable & queryLockable();

            

#if defined(Y_BSD)
            const void *get_pthread_mutex_attr() const noexcept;
#endif


            //! create/get unique instance
            /** \return unique internal instance */
            static Nucleus & Instance();

        private:
            Y_Disable_Copy_And_Assign(Nucleus); //!< discarding
            explicit Nucleus();                 //!< setup
            virtual ~Nucleus() noexcept;        //!< cleanup
            Code * code;                        //!< holds extra code

            //! for AtExit
            static void SelfDestruct(void*) noexcept;
        };
    }

}

#endif

