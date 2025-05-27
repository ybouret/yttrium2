//! \file

#ifndef Y_Memory_Book_Included
#define Y_Memory_Book_Included 1


#include "y/memory/limits.hpp"
#include "y/calculus/alignment.hpp"
#include "y/singleton.hpp"
#include "y/concurrent/life-time.hpp"
#include "y/ability/releasable.hpp"

namespace Yttrium
{
    namespace Memory
    {

        //______________________________________________________________________
        //
        //
        //
        //! (System) Book of pages
        //
        //
        //______________________________________________________________________
        class Book : public Singleton<Book,GiantLockPolicy>, public Releasable
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign;                                     //!< "Memory::Book"
            static const Longevity    LifeTime      = LifeTimeOf:: MemoryBook;      //!< LifeTimeOf::MemoryBook
            static const unsigned     MinPageShift = Limits::MinBlockShift;         //!< alias
            static const unsigned     MaxPageShift = Limits::MaxBlockShift;         //!< alias
            static const unsigned     NumPageShift = 1+MaxPageShift - MinPageShift; //!< alias
            static const size_t       MinPageBytes = Limits::MinBlockBytes;         //!< alias
            static const size_t       MaxPageBytes = Limits::MaxBlockBytes;         //!< alias

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
            // Methods
            //
            //__________________________________________________________________

            //! query clear page
            /**
             \param blockShift valid block shift
             \return 2^blockShift bytes
             */
            void * query(const unsigned blockShift);

            //! store previously queried page
            /**
             \param blockShift valid block shift
             \param blockAddr  prevous 2^blockShift page
             */
            void   store(const unsigned blockShift, void * const blockAddr) noexcept;

            //! reserve pages
            /**
             \param blockShift valid block shift
             \param numPages number of 2^blockShift to store
             */
            void   cache(const unsigned blockShift, const size_t numPages);

            void display(std::ostream &) const; //!< display info

        private:
            Y_Disable_Copy_And_Assign(Book);               //!< discarding
            friend class Singleton<Book,GiantLockPolicy>;
            explicit Book() noexcept; //!< initialize
            virtual ~Book() noexcept; //!< cleanup

            
        };
    }

}

#endif

