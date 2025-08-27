
//! \file


#ifndef Y_Chemical_Assemblies_Included
#define Y_Chemical_Assemblies_Included 1


#include "y/chemical/type/assembly.hpp"
#include "y/chemical/reactive/components.hpp"


namespace Yttrium
{
    namespace Chemical
    {
        //______________________________________________________________________
        //
        //
        //
        //! Monitor different parts of components
        //
        //
        //______________________________________________________________________
        class Assemblies
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Assemblies() noexcept;
            virtual ~Assemblies() noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            void enroll(const Components &) noexcept; //!< update all parts

            //! pretty display \return stream
            std::ostream & display(std::ostream &, const Components &) const;


            const Assembly nameFmt; //!< specific assembly
            const Assembly reacFmt; //!< specific assembly
            const Assembly prodFmt; //!< specific assembly

        private:
            Y_Disable_Copy_And_Assign(Assemblies); //!< discarding
        };

    }

}

#endif

