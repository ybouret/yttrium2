
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
                bool accepts(ARRAY &arr)
                {
                    assert(dimensions==arr.size());
                    if(isBasis()) return false;
                    return isOrtho( fetch() = arr );
                }

                template <typename ARRAY> inline
                bool contains(ARRAY &arr)
                {
                    assert(dimensions==arr.size());
                    if(isBasis()) return true;
                    return ! isOrtho( fetch() = arr );
                }

                bool includes(const Family &F);


                void           grow()                       noexcept; //!< grow last accepted vector
                const char *   humanReadableQuality() const noexcept; //!< \return quality
                const Vector & last()                 const noexcept; //!< \return last ortho after successful accepts and before groe



                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________

                const Quality quality; //!< current quality
            private:
                Vector *      ortho;  //!< last orthogonal vector
                Vector::List  vlist;  //!< current list
                VCache        cache;  //!< share cache
            public:
                Family *      next; //!< for list
                Family *      prev; //!< for list

            private:
                Y_Disable_Assign(Family); //!< discarding
                virtual ConstInterface &locus() const noexcept;

                Vector &fetch();            //!< ensure ortho is not NULL \return *ortho
                void    prune()   noexcept; //!< ensure ortho==NULL
                void    clear()   noexcept; //!< prune and return all vectors to  cache
                bool    isBasis() noexcept; //!< \return true iff size>=dims iff quality == Basis
                bool    isOrtho(Vector &);  //!< \return true if something remains after all projections

            public:
                //______________________________________________________________
                //
                //
                //! cache
                //
                //______________________________________________________________
                class Cache : public CountedObject, public Metrics, public Caching
                {
                public:
                    explicit Cache(const VCache &) noexcept;
                    virtual ~Cache() noexcept;


                    virtual size_t count()     const noexcept;
                    virtual void   gc(const uint8_t) noexcept;
                    virtual void   cache(const size_t);

                    Family * query();
                    void     store(Family * const) noexcept;

                    VCache   vCache;

                private:
                    Y_Disable_Copy_And_Assign(Cache);
                    CxxListOf<Family> fCache;
                };
            };

            typedef ArcPtr<Family::Cache> FCache;

        }


    }

}

#endif

