
//! \file

#ifndef Y_Fit_Entity_Included
#define Y_Fit_Entity_Included 1

#include "y/container/writable.hpp"
#include "y/string.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {
            class Entity : public Object
            {
            public:
                template <typename UID> inline
                explicit Entity(const UID & uid ) : name(uid) {}


                virtual ~Entity() noexcept;

                const String name;

            private:
                Y_Disable_Copy_And_Assign(Entity);
            };
        }

    }

}

#endif // !Y_Fit_Entity_Included
