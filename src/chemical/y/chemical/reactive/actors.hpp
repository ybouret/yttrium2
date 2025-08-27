
//! \file


#ifndef Y_Chemical_Actors_Included
#define Y_Chemical_Actors_Included 1


#include "y/chemical/reactive/actor.hpp"
#include "y/ability/freezable.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        //______________________________________________________________________
        //
        //
        //
        //! List of Actors
        //
        //
        //______________________________________________________________________
        class Actors :
        public Entity,
        public Ingress< const Actor::CoreList >,
        public Freezable
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign; //!< "Actors"

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Actors(const Actor::Role = Actor::InEquilibrium); //!< setup
            virtual ~Actors() noexcept; //!< cleanup
            Actors(const Actors &);     //!< duplicate

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            void add(const unsigned, const Species &); //!< add new actor
            void add(const Species &);                 //!< add new actor
            bool has(const Species &) const noexcept;  //!< \return true iff species is here

            void massAction(XMul &X, const XReadable &C, const Level L) const;
            void massAction(XMul &X, const XReadable &C, const Level L, const xreal_t xi) const;


        private:
            Y_Disable_Assign(Actors); //!< discard
            Y_Ingress_Decl();         //!< helper
            Actor::List       list;   //!< current list
            const Actor::Role role;   //!< current role

        };

    }

}

#endif

