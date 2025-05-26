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

        class Book : public Singleton<Book,GiantLockPolicy>, public Releasable
        {
        public:
            static const char * const CallSign;
            static const Longevity    LifeTime      = LifeTimeOf:: MemoryBook;         //!< lifetime
            static const unsigned MinPageShift = Limits::MinDyadicBlockShift;
            static const unsigned MaxPageShift = Limits::MaxDyadicBlockShift;
            static const unsigned NumPageShift = 1+MaxPageShift - MinPageShift;


            virtual void release() noexcept;

            void * query(const unsigned blockShift);
            void   store(const unsigned blockShift, void * const blockAddr) noexcept;
            void   cache(const unsigned blockShift, const size_t numPages);

            void display(std::ostream &) const;

        private:
            Y_Disable_Copy_And_Assign(Book);
            friend class Singleton<Book,GiantLockPolicy>;

            explicit Book() noexcept;
            virtual ~Book() noexcept;

            
        };
    }

}

#endif

