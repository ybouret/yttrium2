
//! \file

#ifndef Y_Concurrent_Singulet_Included
#define Y_Concurrent_Singulet_Included 1

#include "y/system/at-exit.hpp"
#include "y/xml/element.hpp"
#include "y/ability/lockable.hpp"
#include "y/type/ints.hpp"

namespace Yttrium
{

    namespace Concurrent
    {

        //______________________________________________________________________
        //
        //
        //
        //! Base class for Singleton
        //
        //
        //______________________________________________________________________
        class Singulet : public  XML::Element
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static  bool                      Verbose;   //!< to trace operations
            typedef System::AtExit::Longevity Longevity; //!< alias
            //! assigned to Nucleus
            static  const Longevity           GreatestLifeTime = IntegerFor<Longevity>::Maximum;

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Singulet() noexcept; //!< initialize
            virtual ~Singulet() noexcept; //!< cleanup


            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________

            //! assigned longevity
            /** \return class longevity */
            virtual Longevity  lifeTime() const noexcept = 0;

            
            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! helper to display info during operations
            /**
             \param prefix     NULL or prefix text
             \param identifier callSign()
             \param longevity  lifeTime()
             */
            static void Display(const char * const prefix,
                                const char * const identifier,
                                const Longevity    longevity) noexcept;



        private:
            Y_Disable_Copy_And_Assign(Singulet); //!< discarding
        };
    }
    

}


#endif

