//! \file

#ifndef Y_Ink_Collect_Included
#define Y_Ink_Collect_Included 1

#include "y/ink/pixmap.hpp"
#include "y/ink/broker.hpp"

namespace Yttrium
{
    namespace Ink
    {

        class Collect
        {
        public:
            explicit Collect(const size_t deltaX,
                             const size_t deltaY) noexcept;
            virtual ~Collect() noexcept;


            const unit_t dx;
            const size_t w;
            const unit_t dy;
            const size_t h;
            const size_t items;

        private:
            Y_Disable_Copy_And_Assign(Collect);
        };

    }

}

#endif // !Y_Ink_Collect_Included
