
#include "y/memory/object/book.hpp"
#include "y/memory/object/book/pages.hpp"
#include "y/memory/stealth.hpp"
#include "y/type/destruct.hpp"

namespace Yttrium
{
    namespace Memory
    {
        namespace Object
        {

            const char * const Book:: CallSign = "Memory::Object::Book";

            namespace
            {
                static const unsigned Requested   = sizeof(Pages) * Book::NumPageShift;
                static void *         PagesData[ Alignment::WordsGEQ<Requested>::Count ];
                static Pages *        bookPages = 0;
            }

            Book:: Book()  : Singleton<Book,BroadLockPolicy>()
            {
                assert(0==bookPages);
                bookPages = static_cast<Pages *>( Y_Memory_BZero(PagesData) ) - MinPageShift;
                for(unsigned i=MinPageShift;i<=MaxPageShift;++i)
                    new (bookPages+i) Pages(i);
            }

            Book:: ~Book() noexcept
            {
                assert(0!=bookPages);
                for(unsigned i=MaxPageShift;i>=MinPageShift;--i)
                    Memory::Stealth::Zero( Destructed(bookPages+i), sizeof(Pages) );
                bookPages = 0;
            }

            void Book:: display(std::ostream &os) const
            {
                os << '<' << CallSign << " NumPageShift=" << NumPageShift << '>' << std::endl;
                for(unsigned i=MinPageShift;i<=MaxPageShift;++i)
                {
                    const Pages & pages = bookPages[i];
                    if(pages.count()>0) pages.display(os);
                }
                os << '<' << CallSign << '/' << '>' << std::endl;
            }

            void * Book:: query(const unsigned blockShift)
            {
                Y_Lock(access);
                assert(blockShift>=MinPageShift);
                assert(blockShift<=MaxPageShift);
                return bookPages[blockShift].query();
            }

            void   Book:: store(const unsigned blockShift, void * const blockAddr) noexcept
            {
                Y_Lock(access);
                assert(blockShift>=MinPageShift);
                assert(blockShift<=MaxPageShift);
                bookPages[blockShift].store(blockAddr);
            }

            void  Book::  cache(const unsigned blockShift, const size_t numPages)
            {
                Y_Lock(access);
                assert(blockShift>=MinPageShift);
                assert(blockShift<=MaxPageShift);
                bookPages[blockShift].cache(numPages);
            }

            void Book:: release() noexcept
            {
                //Y_Lock(access);
                for(unsigned i=MaxPageShift;i>=MinPageShift;--i) bookPages[i].release();
            }


        }
    }

}


