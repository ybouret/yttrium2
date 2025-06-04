
//! \file

#ifndef Y_Memory_Pages_Included
#define Y_Memory_Pages_Included 1

#include "y/core/linked/list.hpp"
#include "y/calculus/base2.hpp"
#include "y/ability/releasable.hpp"
#include "y/memory/page.hpp"
#include "y/xml/element.hpp"

namespace Yttrium
{
    namespace Memory
    {
        class Dyadic;

        namespace Object
        {
            //__________________________________________________________________
            //
            //
            //
            //! Local Pages of the same power-of-two size using Dyadic allocator
            /**
             - acts as a low level cache, not intended to be fast,
             - kept pages are store in increasing memory
             */
            //
            //__________________________________________________________________
            class Pages : public Releasable, public XML::Element
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                static const char * const CallSign; //!< "Memory::Pages"
                
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! tuned on dyadic valid shifts
                /**
                 \param userPageShift in Dyadic::MinBlockShift,Dyadic::MaxBlockShift
                 */
                Pages(const unsigned userPageShift);
                
                //! cleanup
                virtual ~Pages() noexcept;
                
                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! query a new/cached page
                /**
                 - from plist if count() > 0
                 - from memIO.acquireDyadic(shift) otherwise
                 \return a clear page of bytes=2^shift
                 \warning unlocked acquire
                 */
                void *       query();
                
                
                //!
                void         store(void * const) noexcept;  //!< store a previously acquired page
                
                //! grow available pages
                /**
                 \param numPages pages to store
                 */
                void         cache(size_t numPages);
                
                
                size_t       count() const noexcept;        //!< \return available pages

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                virtual void         release() noexcept; 
                virtual void         display(std::ostream &,size_t) const; 
                virtual const char * callSign() const noexcept;

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
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

}

#endif

