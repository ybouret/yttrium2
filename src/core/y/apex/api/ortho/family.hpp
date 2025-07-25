
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

            typedef Ingress< const Core::ListOf<Vector> > IFamily;

            class Family :
            public CountedObject,
            public Metrics,
            public IFamily,
            public Recyclable
            {
            public:
                explicit Family(const VCache &) noexcept;
                virtual ~Family() noexcept;
                Family(const Family &);

                template <typename ARRAY> inline
                bool accepts(ARRAY &arr)
                {
                    assert(dimensions==arr.size());
                    if(isBasis()) return false;
                    return isOrtho( fetch() = arr );
                }

                void         grow() noexcept;
                virtual void free() noexcept;


                const Quality quality;
            private:
                Vector *      ortho;  //!< last orthogonal vector
                Vector::List  vlist;  //!< current list
                VCache        cache;  //!< share cache

                Y_Disable_Assign(Family);
                virtual ConstInterface &locus() const noexcept;
                Vector &fetch();
                void    prune() noexcept;
                void    clear() noexcept;

                bool    isBasis() noexcept;
                bool    isOrtho(Vector &a);
            };

        }

    }

}

#endif

