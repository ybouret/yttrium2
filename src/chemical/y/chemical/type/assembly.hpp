
//! \file


#ifndef Y_Chemical_Assembly_Included
#define Y_Chemical_Assembly_Included 1


#include "y/chemical/type/entity.hpp"


namespace Yttrium
{
    namespace Chemical
    {
        //______________________________________________________________________
        //
        //
        //
        //! Monitor name length of entities
        //
        //
        //______________________________________________________________________

        class Assembly
        {
        public:
            explicit Assembly() noexcept;
            virtual ~Assembly() noexcept;

            void reset() noexcept;
            void enroll(const Entity &) noexcept;

            const size_t width; //!< max name length
        private:
            Y_Disable_Copy_And_Assign(Assembly); //!< disarding
        };


    }

}

#endif

