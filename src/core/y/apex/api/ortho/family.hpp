
//! \file

#ifndef Y_Apex_Ortho_Family_Included
#define Y_Apex_Ortho_Family_Included 1

#include "y/apex/api/ortho/vector.hpp"
#include "y/type/ingress.hpp"

namespace Yttrium
{
    namespace Apex
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
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                explicit Family(Vector::Pool &) noexcept; //!< setup with shared cache
                virtual ~Family() noexcept;               //!< cleanup
                Family(const Family &);                   //!< duplicate
                Y_OSTREAM_PROTO(Family);                  //!< display

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                virtual void free() noexcept;

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

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


                const char *   humanReadableQuality() const noexcept; //!< \return quality





                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________

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
                //______________________________________________________________
                //
                //
                //! Cache
                //
                //______________________________________________________________
                class Cache : public CountedObject, public Metrics, public Caching
                {
                public:
                    //__________________________________________________________
                    //
                    // C++
                    //__________________________________________________________
                    explicit Cache(Vector::Pool &) noexcept; //!< setup
                    virtual ~Cache() noexcept;               //!< cleanup

                    //__________________________________________________________
                    //
                    // Interface
                    //__________________________________________________________
                    virtual size_t count()     const noexcept;
                    virtual void   gc(const uint8_t) noexcept;
                    virtual void   cache(const size_t);

                    //__________________________________________________________
                    //
                    // Methods
                    //__________________________________________________________
                    Family * query(const Family &F);         //!< \param F source family \return new empty replicated family
                    void     store(Family * const) noexcept; //!< store and clear family

                    //__________________________________________________________
                    //
                    // Members
                    //__________________________________________________________
                    Vector::Pool &vpool; //!< shared cache of vectors
                private:
                    Y_Disable_Copy_And_Assign(Cache); //!< discarding
                    CxxListOf<Family> fCache;         //!< pool
                };


                //! try to create a new family from a test vector
                /**
                 \param arr a compatible array in type and size
                 \param fc  a family cache
                 \return replicate + new vector upon success
                 */
                template <typename ARRAY>
                Family *newFamilyWith(ARRAY &arr, Cache &fc)
                {
                    Vector * const ortho = accepts(arr); if(!ortho) return 0;
                    return createNewFamilyWith(ortho,fc);
                }

            private:
                //! \return augmented family
                Family *createNewFamilyWith(Vector * const, Cache &);
            };

            typedef ArcPtr<Family::Cache> FCache; //!< alias

        }


    }

}

#endif

