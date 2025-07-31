
//! \file

#ifndef Y_Apex_Ortho_Family_Included
#define Y_Apex_Ortho_Family_Included 1

#include "y/ortho/vector.hpp"
#include "y/type/ingress.hpp"

namespace Yttrium
{
    namespace Ortho
    {

        typedef Ingress< const Core::ListOf<Vector> > IFamily; //!< alias

        //__________________________________________________________________
        //
        //
        //
        //! Family of orthogonal vectors
        //
        //
        //__________________________________________________________________
        class Family :
        public Object,
        public Metrics,
        public IFamily,
        public Recyclable
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Family(Vector::Pool &) noexcept; //!< setup with shared cache
            virtual ~Family() noexcept;               //!< cleanup
            Family(const Family &);                   //!< duplicate
            Y_OSTREAM_PROTO(Family);                  //!< display

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void free() noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            size_t size() const noexcept; //!< \return vlist.size

            //! try to accept compatible array
            /**
             \param arr compatible array in type and size
             \return true if something remains (in ortho) after projections
             */
            template <typename ARRAY> inline
            Vector * accepts(ARRAY &arr)
            {
                assert(dimensions==arr.size());
                if( Basis == dimensions) return 0;
                return orthogonalPart( vpool.query(arr) );
            }

            //! \return ncof>0, nrm2>0, orthogonal to all family vectors
            bool verify(const Vector &) const;

            //! \param v new vector added to family
            void progeny(Vector * const v) noexcept;

            //! \return text for quality
            const char *   humanReadableQuality() const noexcept;

            //! \return same sizes and vectors
            friend bool operator==(const Family &, const Family &) noexcept;

            static SignType Compare(const Family &lhs, const Family &rhs) noexcept;


            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________

            const Quality        quality; //!< current quality
            const Vector * const lastVec; //!< last progeny vector

        private:
            Vector::List   vlist;  //!< current list
            Vector::Pool & vpool;  //!< persistent pool

        public:
            Family *      next; //!< for list
            Family *      prev; //!< for list

        private:
            Y_Disable_Assign(Family); //!< discarding
            virtual ConstInterface &locus() const noexcept;

            void    clear()   noexcept;        //!<  return all vectors to  cache
            Family *replicate(const Family &); //!< \return from empty to copy or source family

            //! check for a vector that may expand the family
            /**
             the vector is returned to cache upon failure
             \param v test vector
             \return remaining orthogonal part
             */
            Vector *orthogonalPart(Vector * const v);

        public:
            //__________________________________________________________________
            //
            //
            //! Pool
            //
            //__________________________________________________________________
            class Pool : public Metrics, public Caching
            {
            public:
                //______________________________________________________________
                //
                // C++
                //______________________________________________________________
                explicit Pool(Vector::Pool &) noexcept; //!< setup
                virtual ~Pool() noexcept;               //!< cleanup

                //______________________________________________________________
                //
                // Interface
                //______________________________________________________________
                virtual size_t count()     const noexcept;
                virtual void   gc(const uint8_t) noexcept;
                virtual void   cache(const size_t);

                //______________________________________________________________
                //
                // Methods
                //______________________________________________________________
                Family * query(const Family &F);         //!< \param F source family \return new empty replicated family
                void     store(Family * const) noexcept; //!< store and clear family
                Family * query();                        //!< \return new empty family

                //! start family from an initial vector
                /**
                 \param arr compatible array
                 \return new family if array was not zero, NULL otherwise
                 */
                template <typename ARRAY> inline
                Family * start(ARRAY & arr)
                {
                    Family * const F = query();
                    try {
                        if(Vector *v=F->accepts(arr))
                        {
                            F->progeny(v);
                            assert(F->lastVec == v);
                            return F;
                        }
                        store(F);
                        return 0;
                    }
                    catch(...)
                    {
                        store(F); throw;
                    }
                }

                //______________________________________________________________
                //
                // Members
                //______________________________________________________________
                Vector::Pool &vpool; //!< shared cache of vectors
            private:
                Y_Disable_Copy_And_Assign(Pool); //!< discarding
                CxxListOf<Family> flist;         //!< list
            };


            //! try to create a new family from a test vector
            /**
             \param arr    a compatible array in type and size
             \param fpool  a compativle family cache
             \return replicate + new vector upon success
             */
            template <typename ARRAY>
            Family *newFamilyWith(ARRAY &arr, Pool &fpool)
            {
                Vector * const ortho = accepts(arr); if(!ortho) return 0;
                return createNewFamilyWith(ortho,fpool);
            }

        private:
            //! \return augmented family
            Family *createNewFamilyWith(Vector * const, Pool &);
        };


    }

    

}

#endif

