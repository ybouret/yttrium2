//! \file


#ifndef Y_Chemical_Actor_Included
#define Y_Chemical_Actor_Included 1


#include "y/chemical/species.hpp"
#include "y/chemical/type/xreal.hpp"


namespace Yttrium
{
    namespace Chemical
    {
        
        class Actor : public Entity
        {
        public:
            static const char * const   CallSign;
            typedef CxxListOf<Actor>    List;
            typedef Core::ListOf<Actor> CoreList;
            
            enum Role
            {
                InEquilibrium,      //!< define equilibium
                InConservation
            };

            explicit Actor(const unsigned,
                           const Species &,
                           const Role = InEquilibrium);
            virtual ~Actor() noexcept;
            Actor(const Actor &);

            const Species &sp;
            const unsigned nu;
            const xreal_t  xn;
            const unsigned nu1;

            Actor * next;
            Actor * prev;

        private:
            Y_Disable_Assign(Actor);
        };
    }

}

#endif

