
//! \file


#ifndef Y_Chemical_Conservation_Law_Included
#define Y_Chemical_Conservation_Law_Included 1


#include "y/chemical/reactive/equilibrium.hpp"
#include "y/stream/xmlog.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        namespace Conservation
        {
            //__________________________________________________________________
            //
            //
            //
            //! base class to project/correct concentrations
            //
            //
            //__________________________________________________________________
            class Remedy : public Object
            {
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
            protected:
                explicit Remedy(const size_t, const size_t); //!< setup rows x cols
            public:
                virtual ~Remedy() noexcept; //!< cleanup

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const XMatrix numer; //!< rows of numerators
                const XArray  denom; //!< matching denominators
            private:
                Y_Disable_Copy_And_Assign(Remedy); //!< discarding
            };

            //__________________________________________________________________
            //
            //
            //
            //! Conservation Law
            //
            //
            //__________________________________________________________________
            class Law : public Actors, public Vizible
            {
            public:

                //______________________________________________________________
                //
                //
                //! Projection on law
                //
                //______________________________________________________________
                class Projection : public Remedy
                {
                public:
                    //__________________________________________________________
                    //
                    // C++
                    //__________________________________________________________
                    explicit Projection(const size_t); //!< setup with number of species
                    virtual ~Projection() noexcept;    //!< cleanup

                    //__________________________________________________________
                    //
                    // Methods
                    //__________________________________________________________

                    //! compute new Ctop from a broken law
                    /**
                     \param law  broken law
                     \param xadd inner addition
                     \param Ctop top-level concentrations breaking law
                     \param Ctmp temporary array for computation
                     */
                    void compute(const Actors & law,
                                 XAdd         & xadd,
                                 XWritable    & Ctop,
                                 XWritable    & Ctmp) const;

                    
                private:
                    Y_Disable_Copy_And_Assign(Projection); //!< discarding
                };


                class Correction : public Remedy
                {
                public:
                    explicit Correction(const size_t, const size_t);
                    virtual ~Correction() noexcept;
                    

                    void compute(const Law    &law,
                                 XAdd         &xadd,
                                 XWritable    &Ctop,
                                 XWritable    &xi,
                                 XWritable    &Ctmp,
                                 Accumulator  &Cnew) const;

                private:
                    Y_Disable_Copy_And_Assign(Correction); //!< discarding
                };


                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                explicit Law();           //!< setup
                virtual ~Law() noexcept;  //!< cleanup
                Y_OSTREAM_PROTO(Law);     //!< display

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! finalize metrics and query involved equilibria
                /**
                 \param xml      output
                 \param primary  list of primary equilibria
                 \param topology primary topology matrix
                 */
                void finalize(XMLog &         xml,
                              const EList   & primary,
                              const iMatrix & topology); //!< finalize metrics

                //! \return positive excess if any
                xreal_t excess(XAdd &, const XReadable &, const Level) const;

                //! GraphViz with color \return output stream
                OutputStream & viz(OutputStream &, const String &) const;

                //! projection on valid phase space
                /**
                 \param xadd inner addition
                 \param Ctop top-level concentration breaking the law
                 \param Ctmp temporary for computation
                 */
                void project(XAdd        & xadd,
                             XWritable   & Ctop,
                             XWritable   & Ctmp) const;


                //! nullify last cleared
                /**
                 \param xadd inner addition
                 \param Ctop top-level concentration breaking the law
                 \param Ctmp temporary for computation
                 */
                void nullify(XAdd        & xadd,
                             XWritable   & Ctop,
                             XWritable   & Xi,
                             XWritable   & Ctmp,
                             Accumulator & Cnew) const;


                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const AutoPtr<Projection> prj;   //!< projection data
                const AutoPtr<Correction> cor;   //!< correction data
                const unsigned            ua2;   //!< |*this|^2, unsigned
                const xreal_t             xa2;   //!< |*this|^2, xreal_t
                const xreal_t             norm;  //!< |*this| = sqrt(xa2)
                const EList               lead;  //!< leading primary
                const SList               clan;  //!< all species from lead
                const xreal_t             zero;  //!< for computations
                Law *                     next;  //!< for list
                Law *                     prev;  //!< for list

            private:
                Y_Disable_Copy_And_Assign(Law); //!< discarding
                void computeProjection();
                void computeCorrection();
            };

            typedef Protean::BareLightList<const Law> LList; //!< alias
            typedef LList::NodeType                   LNode; //!< alias


        }
    }

}

#endif // !Y_Chemical_Conservation_Law_Included

