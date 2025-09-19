
//! \file


#ifndef Y_Chemical_Actors_Included
#define Y_Chemical_Actors_Included 1


#include "y/chemical/reactive/actor.hpp"
#include "y/ability/freezable.hpp"
#include "y/chemical/type/assembly.hpp"

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
        public Freezable,
        public Assembly
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
            void add(const unsigned, const Species &);   //!< add new actor
            void add(const Species &);                   //!< add new actor
            bool got(const Species &)    const noexcept; //!< \return true iff species is here
            bool gotOneOf(const SList &) const noexcept; //!< \return ture iff at least one species if there

            //! \param X xmul, update \param C concentrations \param L level
            void massAction(XMul &X, const XReadable &C, const Level L) const;

            //! \param X xmul, updated at xi \param C concentrations \param L level \param xi extent
            void massAction(XMul &X, const XReadable &C, const Level L, const xreal_t xi) const;


            //! move safely \param C concentrations \param L level \param xi extent
            void moveSafely(XWritable &C, const Level L, const xreal_t xi) const;

            //! compute limit \param C concentration \param L level \return min(C/nu)
            xreal_t fastLimit(const XReadable &C, const Level L) const noexcept;

            //! \return true iff at least one zero conc
            bool degenerate(const XReadable &, const Level) const noexcept;

            //! one sided derivatives
            /**
             \param dma mass action derivatives
             \param X helper
             \param K constant/-1
             \param C concentrations
             \param L level
             \param ma auxiliary array for individua mass action
             */
            void diffAction(XWritable       &dma,
                            XMul            &X,
                            const xreal_t    K,
                            const XReadable &C,
                            const Level      L,
                            XWritable       &ma) const;

            String html() const; //!< \return hmtl conservation

            void mergeSpeciesInto(SList &) const;

        private:
            Y_Disable_Assign(Actors); //!< discard
            Y_Ingress_Decl();         //!< helper
        protected:
            Actor::List       list;   //!< current list
        public:
            const Actor::Role role;   //!< current role

        };

    }

}

#endif

