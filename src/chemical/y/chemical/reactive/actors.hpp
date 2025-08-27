
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

            //! \param X xmul, update \param C concentrations \param L level
            void massAction(XMul &X, const XReadable &C, const Level L) const;

            //! \param X xmul, updated at xi \param C concentrations \param L level \param xi extent
            void massAction(XMul &X, const XReadable &C, const Level L, const xreal_t xi) const;

            //! move safely \param C concentrations \param L level \param xi extent
            void moveSafely(XWritable &C, const Level L, const xreal_t xi) const;

            //! compute limit \param C concentration \param L level \return min(C/nu)
            xreal_t fastLimit(const XReadable &C, const Level L) const noexcept;



        private:
            Y_Disable_Assign(Actors); //!< discard
            Y_Ingress_Decl();         //!< helper
            Actor::List       list;   //!< current list
            const Actor::Role role;   //!< current role

        };

    }

}

#endif

