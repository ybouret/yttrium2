
//! \file

#ifndef Y_Ink_Filter_Metrics_Included
#define Y_Ink_Filter_Metrics_Included 1

#include "y/type/sign.hpp"

namespace Yttrium
{
    namespace Ink
    {

        //______________________________________________________________________
        //
        //
        //
        //! compute metrics from block size
        //
        //
        //______________________________________________________________________
        class FilterMetrics
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign; //!< "Filter"

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param blockSize number of items in the filter data
            explicit FilterMetrics(const size_t blockSize);
            virtual ~FilterMetrics() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methds
            //
            //__________________________________________________________________

            //! \param blockAddr data \param blockSize size \return non-zero elements
            template <typename T> static inline
            size_t Count(const T * const blockAddr, const size_t blockSize)
            {
                assert(0!=blockAddr);
                size_t res = 0;
                for(size_t i=0;i<blockSize;++i)
                {
                    switch( Sign::Of(blockAddr[i]) )
                    {
                        case __Zero__: continue;
                        case Negative:
                        case Positive:
                            ++res;
                            continue;
                    }
                }
                return res;
            }

            //__________________________________________________________________
            //
            //
            // Mebers
            //
            //__________________________________________________________________
            const size_t side;  //!< sqrt(blockSize)
            const unit_t delta; //!< side/2-1

        private:
            Y_Disable_Copy_And_Assign(FilterMetrics); //!< discarding
        };
    }

}

#endif // !Y_Ink_Filter_Metrics_Included

