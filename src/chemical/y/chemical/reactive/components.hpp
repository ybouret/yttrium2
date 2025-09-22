//! \file

#ifndef Y_Chemical_Components_Included
#define Y_Chemical_Components_Included 1


#include "y/chemical/reactive/actors.hpp"


namespace Yttrium
{
    namespace Chemical
    {

        //______________________________________________________________________
        //
        //
        //! Components status
        //
        //______________________________________________________________________
        enum Status
        {
            Running, //!< no singularity
            Blocked, //!< two singularities
            Crucial  //!< one singularity
        };

        //______________________________________________________________________
        //
        //
        //! Components classification
        //
        //______________________________________________________________________
        enum MatterFlow
        {
            Dangling, //!< no prod, no rec
            BothWays, //!< prod and reac
            ProdOnly, //!< only prod
            ReacOnly, //!< only reac
        };

        //______________________________________________________________________
        //
        //
        //
        //! Base class for Equilibrium
        //
        //
        //______________________________________________________________________
        class Components : public Indexed, public Freezable, public Vizible
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const Arrows;       //!< "<=>"
            static const char * const Prod;         //!< "Prod"
            static const char * const Reac;         //!< "Reac"
            static const char         Prefix = '@'; //!< alias
            static const char *       HumanReadableStatus(const Status) noexcept; //!< \return textual info

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            //! setup \param id name \param top top-level index
            template <typename ID> inline
            explicit Components(const ID & id, const size_t top) :
            Indexed(id,top),
            reac(),
            prod(),
            flow(Dangling),
            xdim(0),
            drNu(0),
            minusOne(-1)
            {
            }
            
            virtual ~Components() noexcept; //!< cleanup
            Y_OSTREAM_PROTO(Components);    //!< display

            //__________________________________________________________________
            //
            //
            // Methods to setup
            //
            //__________________________________________________________________
            void p(const unsigned, const Species &); //!< add product
            void r(const unsigned, const Species &); //!< add reactant
            void p(const Species &); //!< add product
            void r(const Species &); //!< add reactant

            bool neutral() const;                     //!< \return true iff electro-neutrality
            bool got(const Species &) const noexcept; //!< \return true if species is found

            //! fill topology array
            /**
             \param arr   target array
             \param level index level
             */
            template <typename ARR> inline
            void topology(ARR &arr, const Level level) const
            {
                for(const Actor *a=prod->head;a;a=a->next) a->sp(arr,level) =   (int) a->nu;
                for(const Actor *a=reac->head;a;a=a->next) a->sp(arr,level) = - (int) a->nu;
            }

            //! \param sp species \return its coefficient
            int stoichiometry(const Species &sp) const noexcept;

            //! display compact content \return ostream
            std::ostream & displayCompact(std::ostream &, const XReadable &, const Level) const;

            //! display compact representation \return ostream
            std::ostream & print(std::ostream &) const;

            //! merge species into target list
            void mergeSpeciesInto(SList &) const;

            //__________________________________________________________________
            //
            //
            // Methods to compute
            //
            //__________________________________________________________________

            //! \param X xmul \param K constant \param C concentration \param L level \return mass action at C
            xreal_t massAction(XMul &X, const xreal_t K, const XReadable &C, const Level L) const;

            //! \param X xmul \param K constant \param C concentration \param L level \param xi extent \return mass action at C+nu*xi*
            xreal_t massAction(XMul &X, const xreal_t K, const XReadable &C, const Level L, const real_t xi) const;

            //! move safely \param C concentrations \param L level \param xi extent
            void    moveSafely(XWritable &C, const Level L, const xreal_t xi) const;

            //! \param xadd helper \param C concentrations \param L level \param C0 origin \return average extent
            xreal_t extent(XAdd &xadd, const XReadable &C, const Level L, const XReadable &C0) const;

            //! status depending on phase space
            /**
             \param C    concentrations
             \param L    level
             \return matching status
             */
            Status status(const XReadable &C, const Level L) const noexcept;

            //! affinity if running
            /**
             \param xadd helper
             \param K    constant
             \param C    concentrations
             \param L    level
             \return log(K) - log(Q), Q=prod/reac
             */
            xreal_t affinity(XAdd &xadd, const xreal_t K, const XReadable &C, const Level L) const;

            //! full gradient
            /**
             \param dma mass action derivatives
             \param X helper
             \param K pre-computed constant
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

            //! compute jacobian of affinity
            /**
             \param J dA/dC
             \param C concentrations
             \param L level
             */
            void jacobian(XWritable       &J,
                          const XReadable &C,
                          const Level      L) const;


            //! emit GraphViz code
            /**
             \param fp    output stream
             \param color precomputed color
             \return stream
             */
            OutputStream & viz(OutputStream &fp, const String &color) const;

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const Actors      reac; //!< reactants
            const Actors      prod; //!< products
            const MatterFlow  flow; //!< current flow
            const xreal_t     xdim; //!< components in xreal_t
            const unit_t      drNu; //!< Delta_r Nu
            const xreal_t     minusOne; //!< =1
        private:
            Y_Disable_Copy_And_Assign(Components); //!< discarding
            void updateFlow() noexcept; //!< update after adding
        };
    }

}

#endif // !Y_Chemical_Components_Included

