
//! \file

#ifndef Y_Memory_Pages_Included
#define Y_Memory_Pages_Included 1

#include "y/core/linked/list.hpp"
#include "y/calculus/base2.hpp"
#include "y/ability/releasable.hpp"
#include "y/memory/page.hpp"

namespace Yttrium
{
    namespace Memory
    {
        class Dyadic;
        
        

        class Pages : public Releasable
        {
        public:
            static const char * const CallSign; //!< "Memory::Pages"

            //! tuned on dyadic
            Pages(const unsigned userPageShift);
            virtual ~Pages() noexcept;


            void *       query();
            void         store(void * const addr) noexcept;
            void         cache(size_t numPages);
            size_t       count() const noexcept;
            void         display(std::ostream &) const;
            virtual void release() noexcept;

        private:
            Core::ListOf<Page> plist;
        public:
            const unsigned     shift;
            const size_t       bytes;
            Dyadic &           memIO;

        private:
            Y_Disable_Copy_And_Assign(Pages);
            void   release_() noexcept;
            void * newPage();
        };


    }

}

#endif

