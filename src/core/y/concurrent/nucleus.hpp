
//! \file

#ifndef Y_Concurrent_Nucleus_Included
#define Y_Concurrent_Nucleus_Included 1

#include "y/concurrent/singulet.hpp"


namespace Yttrium
{

    namespace Concurrent
    {
        class Nucleus : public Singulet
        {
        public:
            static const char * const CallSign; //!< "Concurrent::Nucleus"
            static const Longevity    LifeTime = Singulet::GreatestLifeTime;
            class        Code;

            // Interface

            //! [Identifiable]
            /** \return CallSign */
            virtual const char * callSign() const noexcept;

            //! [Singulet]
            /** \return LifeTime */
            virtual Longevity    lifeTime() const noexcept;

            //! [Singulet]
            /** \return internal mutex */
            virtual Lockable & access() noexcept;

            // Methods

            static Nucleus & Instance();

        private:
            Y_Disable_Copy_And_Assign(Nucleus);
            explicit Nucleus();
            virtual ~Nucleus() noexcept;
            Code * code;

            static void SelfDestruct(void*) noexcept;
        };
    }

}

#endif

