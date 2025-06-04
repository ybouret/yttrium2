
#include "y/memory/object/book.hpp"
#include "y/memory/object/book/pages.hpp"
#include "y/memory/stealth.hpp"
#include "y/type/destruct.hpp"
#include "y/xml/attribute.hpp"

namespace Yttrium
{
    namespace Memory
    {
        namespace Object
        {

            const char * const Book:: CallSign = "Memory::Object::Book";
            const unsigned     Book:: NumPageShift;

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

            void Book:: display(std::ostream &os, size_t indent) const
            {
                initProlog(os,indent) << Y_XML_Attr(NumPageShift);
                initEpilog(os,false);
                ++indent;
                for(unsigned i=MinPageShift;i<=MaxPageShift;++i)
                {
                    const Pages & pages = bookPages[i];
                    if(pages.count()>0) pages.display(os,indent+1);
                }
                --indent;
                quit(os,indent);
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


            void Book:: gc(const uint8_t amount) noexcept
            {
                for(unsigned i=MaxPageShift;i>=MinPageShift;--i) bookPages[i].gc(amount);
            }
            

        }
    }

}


