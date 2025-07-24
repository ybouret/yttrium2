
//! \file

#ifndef Y_Apex_Ortho_VCache_Included
#define Y_Apex_Ortho_VCache_Included 1

#include "y/apex/api/ortho/vector.hpp"
#include "y/object/counted.hpp"
#include "y/pointer/arc.hpp"

namespace Yttrium
{
    namespace Apex
    {
        namespace Ortho
        {
            class VCache : public CountedObject, Metrics
            {
            public:
                explicit VCache(const Metrics &);
                virtual ~VCache() noexcept;

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
                CxxListOf<Vector> list;
            };

            //typedef ArcPtr<VCache>

        }
    }

}

#endif

