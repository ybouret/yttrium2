
//! \file

#ifndef Y_Coven_Carrier_Included
#define Y_Coven_Carrier_Included 1

#include "y/apex/api/coven/types.hpp"
#include "y/apex/api/coven/ilist.hpp"


namespace Yttrium
{

    namespace Coven
    {

        class Carrier : public QMetrics
        {
        public:
            explicit Carrier(const size_t dims);
            virtual ~Carrier() noexcept;

            QVector::Pool vpool;
            QFamily::Pool fpool;

        private:
            Y_Disable_Copy_And_Assign(Carrier);
        };

    }
}

#endif

