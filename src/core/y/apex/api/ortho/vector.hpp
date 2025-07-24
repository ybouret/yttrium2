
//! \file

#ifndef Y_Apex_Ortho_Vector_Included
#define Y_Apex_Ortho_Vector_Included 1

#include "y/apex/api/ortho/metrics.hpp"
#include "y/container/cxx/array.hpp"
#include "y/apex/rational.hpp"
#include "y/core/linked/list/cxx.hpp"
#include "y/object/counted.hpp"

namespace Yttrium
{
    namespace Apex
    {
        namespace Ortho
        {

            //! base type for apz vector
            typedef CxxArray<const apz> VectorType;

            //__________________________________________________________________
            //
            //
            //
            //! vector to form orthogonal basis
            //
            //
            //__________________________________________________________________
            class Vector :
            public Object,
            public Metrics,
            public VectorType
            {
            public:
                typedef CxxListOf<Vector> List;

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                Vector(const Metrics &);           //!< setup to zero from metrics
                Vector(const Vector &);            //!< duplicate
                virtual ~Vector() noexcept;        //!< cleanup
                Vector & operator=(const Vector&); //!< assign with same dimensions \return *this


                //! assign from compatible array (int,apz,apn,apq...) and update
                /**
                 \param copyOf helper
                 \param arr    array eith positive size
                 */
                template <typename ARRAY> inline
                Vector(const CopyOf_ &copyOf, ARRAY &arr) :
                Object(),
                Metrics( arr.size() ),
                VectorType(copyOf,arr),
                ncof(0),
                nrm2(),
                next(0),
                prev(0)
                {
                    update();
                }

                //! assign compatible array with same size/metrics
                /**
                 copy all components and update
                 \param array
                 */
                template <typename ARRAY> inline
                Vector & operator=(ARRAY &arr)
                {
                    assert(arr.size()==dimensions);
                    try {
                        for(size_t i=dimensions;i>0;--i)
                            Coerce( (*this)[i] ) = arr[i];
                    }
                    catch(...) { ldz(); throw; }
                    update();
                    return *this;
                }

                //! display with extra info
                friend std::ostream & operator<<(std::ostream &, const Vector &);

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________=
                void ldz() noexcept; //!< no-throw clear
                void update();       //!< update to univocal vector

                //! test equality
                friend bool operator==(const Vector &, const Vector &) noexcept;

                bool keepOrtho(const Vector &b);

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const size_t ncof; //!< number of non-zero coefficient
                const apn    nrm2; //!< |*this|^2
                Vector *     next; //!< for list/pool
                Vector *     prev; //!< for list

                //______________________________________________________________
                //
                //
                // Cache
                //
                //______________________________________________________________
                class Cache : public CountedObject, public Metrics
                {
                public:
                    explicit Cache(const Metrics &) noexcept;
                    virtual ~Cache() noexcept;

                    Vector * query();
                    void     store(Vector * const) noexcept;

                    template <typename ARRAY> inline
                    Vector * query(ARRAY &arr)
                    {
                        Vector * const v = query();
                        try {
                            *v = arr;
                        }
                        catch(...)
                        {
                            store(v);
                            throw;
                        }
                        return v;
                    }

                private:
                    Y_Disable_Copy_And_Assign(Cache);
                    List list;
                };
            };


        }

    }

}

#endif
