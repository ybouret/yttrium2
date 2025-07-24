
//! \file

#ifndef Y_Apex_Ortho_Vector_Included
#define Y_Apex_Ortho_Vector_Included 1

#include "y/apex/api/ortho/metrics.hpp"
#include "y/container/cxx/array.hpp"
#include "y/apex/rational.hpp"

namespace Yttrium
{
    namespace Apex
    {
        namespace Ortho
        {

            typedef CxxArray<const apz> VectorType;

            class Vector :
            public Object,
            public Metrics,
            public VectorType
            {
            public:
                Vector(const Metrics &);
                Vector(const Vector &);
                virtual ~Vector() noexcept;

                Vector & operator=( const Vector & );


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


                friend std::ostream & operator<<(std::ostream &, const Vector &);

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

                void ldz() noexcept;
                void update();


                const size_t ncof;
                apn          nrm2;
                Vector *     next;
                Vector *     prev;

            };


        }

    }

}

#endif
