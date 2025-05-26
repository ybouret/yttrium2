
//! \file

#ifndef Y_Memory_Pages_Included
#define Y_Memory_Pages_Included 1

#include "y/core/linked/list.hpp"
#include "y/calculus/base2.hpp"

namespace Yttrium
{
    namespace Memory
    {
        class Dyadic;
        
        struct Page
        {
            typedef Core::ListOf<Page> List;
            Page *next;
            Page *prev;
        };

        class Pages : public Page::List
        {
        public:
            static const char * const CallSign;



            Pages(const unsigned userPageShift);
            virtual ~Pages() noexcept;



            void *query();
            void  store(void * const addr) noexcept;


            const unsigned shift;
            const size_t   bytes;
            Dyadic &       allocator;

        private:
            Y_Disable_Copy_And_Assign(Pages);

            static size_t ComputePageSize(const size_t requestedPageSize, unsigned &computedBlockShift);
        };


    }

}

#endif

