//! \file

#ifndef Y_Ink_Collect_Included
#define Y_Ink_Collect_Included 1

#include "y/ink/ops.hpp"
#include "y/core/utils.hpp"
#include "y/sorting/heap.hpp"

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

            template <typename T, typename PIXMAP> inline
            void load(T * target, PIXMAP & source, const Coord origin)
            {
                unit_t y = origin.y+dy;
                for(size_t j=h;j>0;--j)
                {
                    typename PIXMAP::Row & row = source[y++];
                    unit_t x = origin.x + dx;
                    for(size_t i=w;i>0;--i)
                        *(target++) = row[x++];
                }
            }

            template <typename T, typename PIXMAP> inline
            T minimum(PIXMAP & source, const Coord origin)
            {
                T      res = source[origin.y][origin.x];
                unit_t y = origin.y+dy;
                for(size_t j=h;j>0;--j)
                {
                    typename PIXMAP::Row & row = source[y++];
                    unit_t x = origin.x + dx;
                    for(size_t i=w;i>0;--i)
                        InSituMin(res,row[x++]);
                }
                return res;
            }

            template <typename T, typename PIXMAP> inline
            T maximum(PIXMAP & source, const Coord origin)
            {
                T      res = source[origin.y][origin.x];
                unit_t y = origin.y+dy;
                for(size_t j=h;j>0;--j)
                {
                    typename PIXMAP::Row & row = source[y++];
                    unit_t x = origin.x + dx;
                    for(size_t i=w;i>0;--i)
                        InSituMax(res,row[x++]);
                }
                return res;
            }

            template <typename T, typename PIXMAP> inline
            T median(T * const target, PIXMAP & source, const Coord origin)
            {
                load(target,source,origin);
                Sorting::Heap::Sort(target,items,Sign::Increasing<T>);
                return target[ihalf];
            }

            const unit_t dx;
            const size_t w;
            const unit_t dy;
            const size_t h;
            const size_t items;
            const size_t ihalf;
            
        private:
            Y_Disable_Copy_And_Assign(Collect);
        };

    }

}

#endif // !Y_Ink_Collect_Included
