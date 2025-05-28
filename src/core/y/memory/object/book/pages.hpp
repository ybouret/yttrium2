
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
             \param userPageShift in Dyadic::MinBlockShift,Dyadic::MaxBlockShift
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

            //! query a new page with
            /**
             - from plist if count() > 0
             - from memIO.acquireUnlockedDyadic(shift) otherwise
             \return a clear page of bytes=2^shift
             \warning unlocked acquire
             */
            void *       query();


            //!
            void         store(void * const) noexcept;  //!< store a previously acquired page

            //! grow availabale pages
            /**
             use memIO.acquireUnlockedDyadic(shift)
             \param numPages pages to store
             \warning unlocked
             */
            void         cache(size_t numPages);


            size_t       count() const noexcept;        //!< \return available pages
            void         display(std::ostream &) const; //!< display info

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void release() noexcept; //! safe (locked) release

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
        private:
            Core::ListOf<Page> plist; //!< content
        public:
            const unsigned     shift; //!< common shift
            const size_t       bytes; //!< common bytes=2^shift
            Dyadic &           memIO; //!< instance of allocator

        private:
            Y_Disable_Copy_And_Assign(Pages); //!< discarding
            void   release_() noexcept;       //!< release all existing pages
            
        };


    }

}

#endif

