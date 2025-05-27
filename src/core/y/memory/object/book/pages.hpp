
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

        //______________________________________________________________________
        //
        //
        //
        //! Pages of the same power-of-two size
        //
        //
        //______________________________________________________________________
        class Pages : public Releasable
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign; //!< "Memory::Pages"

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! tuned on dyadic valid shifts
            /**
             \param usePageShift in Dyadic::MinBlockShift,Dyadic::MaxBlockShift
             */
            Pages(const unsigned userPageShift);

            //! cleanup
            virtual ~Pages() noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            void *       query();
            void         store(void * const addr) noexcept;
            void         cache(size_t numPages);
            size_t       count() const noexcept;
            void         display(std::ostream &) const;

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void release() noexcept;

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
        private:
            Core::ListOf<Page> plist;
        public:
            const unsigned     shift;
            const size_t       bytes;
            Dyadic &           memIO;

        private:
            Y_Disable_Copy_And_Assign(Pages); //!< discarding
            void   release_() noexcept;       //!< release all existing pages
            void * newPage();                 //!< create a new page
        };


    }

}

#endif

