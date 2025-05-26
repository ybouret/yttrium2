
//! \file

#ifndef Y_Memory_Pages_Included
#define Y_Memory_Pages_Included 1

#include "y/core/linked/list.hpp"
#include "y/calculus/base2.hpp"
#include "y/ability/releasable.hpp"

namespace Yttrium
{
    namespace Memory
    {
        class Dyadic;
        
        struct Page
        {
            Page *next;
            Page *prev;
        };

        class Pages : public Releasable
        {
        public:
            static const char * const CallSign; //!< "Memory::Pages"
            
            Pages(const unsigned userPageShift);
            virtual ~Pages() noexcept;



            void *       query();
            void         store(void * const addr) noexcept;
            void         display(std::ostream &) const;
            virtual void release() noexcept;

        private:
            Core::ListOf<Page> plist;

        public:
            const unsigned shift;
            const size_t   bytes;
            Dyadic &       allocator;

        private:
            Y_Disable_Copy_And_Assign(Pages);
            void release_() noexcept;

        };


    }

}

#endif

