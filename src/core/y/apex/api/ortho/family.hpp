
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
                explicit Family(const VCache &) noexcept; //!< setup with shared cache
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
                    return isOrtho( cache->query(arr) );
                }

                bool verify(const Vector &v) const;
                void progeny(Vector * const v) noexcept; //!< \param v new vector added to family

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
                Vector::List  vlist;  //!< current list
                VCache        cache;  //!< share cache
            public:
                Family *      next; //!< for list
                Family *      prev; //!< for list

            private:
                Y_Disable_Assign(Family); //!< discarding
                virtual ConstInterface &locus() const noexcept;

                void    clear()   noexcept;        //!<  return all vectors to  cache
                Vector *isOrtho(Vector * const);   //!< \return remaining non zero vector, NULL otherwise
                Family *replicate(const Family &); //!< from empty to copy

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
                    explicit Cache(const VCache &) noexcept; //!< setup
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
                    Family * query(const Family &F);         //!< \return new empty family
                    void     store(Family * const) noexcept; //!< store and clear family

                    //__________________________________________________________
                    //
                    // Members
                    //__________________________________________________________
                    VCache   vCache; //!< shared cache of vectors
                private:
                    Y_Disable_Copy_And_Assign(Cache); //!< discarding
                    CxxListOf<Family> fCache;         //!< pool
                };


                template <typename ARRAY>
                Family *newFamilyWith(ARRAY &arr, Cache &fc)
                {
                    Vector * const ortho = accepts(arr);
                    if(!ortho) return 0;
                    return createNewFamilyWith(ortho,fc);
                }

            private:
                Family *createNewFamilyWith(Vector * const, Cache &);
            };

            typedef ArcPtr<Family::Cache> FCache; //!< alias

        }


    }

}

#endif

