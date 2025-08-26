
//! \file


#ifndef Y_Chemical_Actors_Included
#define Y_Chemical_Actors_Included 1


#include "y/chemical/reactive/actor.hpp"


namespace Yttrium
{
    namespace Chemical
    {

        class Actors : public Entity, public Ingress< const Actor::CoreList >
        {
        public:
            static const char * const CallSign;
            
            explicit Actors(const Actor::Role = Actor::InEquilibrium);
            virtual ~Actors() noexcept;

            Actors(const Actors &);

            void add(const unsigned, const Species &);
            void add(const Species &);



        private:
            Y_Disable_Assign(Actors);
            Y_Ingress_Decl();
            Actor::List       list;
            const Actor::Role role;

        };

    }

}

#endif

