
//! \file

#ifndef Y_Concurrent_Nucleus_Included
#define Y_Concurrent_Nucleus_Included 1

#include "y/concurrent/singulet.hpp"


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
            static const char * const CallSign; //!< "Concurrent::Nucleus"
            static const Longevity    LifeTime = Singulet::GreatestLifeTime; //!< oldest
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

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

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

