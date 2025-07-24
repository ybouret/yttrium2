
//! \file

#ifndef Y_Apex_Ortho_Metrics_Included
#define Y_Apex_Ortho_Metrics_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Apex
    {
        namespace Ortho
        {

            class Metrics
            {
            public:
                Metrics(const size_t dims);
                virtual ~Metrics() noexcept;
                Metrics(const Metrics &) noexcept;

                const size_t dimensions;

            private:
                Y_Disable_Assign(Metrics);
            };
        }

    }
}

#endif

