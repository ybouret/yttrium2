

//! \file

#ifndef Y_Apex_Block_API_Included
#define Y_Apex_Block_API_Included 1

#include "y/apex/metrics.hpp"

namespace Yttrium
{
    namespace Apex
    {
        enum ViewType
        {
            View8,
            View16,
            View32,
            View64
        };


#define Y_Block_Check(EXPR) do { \
if ( !(EXPR) ) { std::cerr << #EXPR << " failure" << std::endl; return false; } \
} while(false)


        class BlockAPI
        {
        protected:
            explicit BlockAPI(const size_t   n,
                              const ViewType v);

        public:
            virtual ~BlockAPI() noexcept;
            Y_OSTREAM_PROTO(BlockAPI);


            virtual size_t update(BlockAPI * const []) noexcept = 0;
            virtual void   resize(const size_t numBits) noexcept = 0;
            bool           isValid() const noexcept;

            size_t         size;
            const size_t   maxi;
            const ViewType view;

            static const ViewType VTable[Metrics::Views];

        private:
            Y_Disable_Copy_And_Assign(BlockAPI);
            virtual bool           doCheck()   const noexcept = 0;
            virtual void           zeroPad()         noexcept = 0;
            virtual std::ostream & print(std::ostream&) const = 0;

        };


    }

}

#endif
