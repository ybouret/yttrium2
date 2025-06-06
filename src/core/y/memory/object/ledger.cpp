
#include "y/memory/object/ledger.hpp"
#include "y/memory/object/ledger/pages.hpp"
#include "y/memory/stealth.hpp"
#include "y/type/destruct.hpp"
#include "y/xml/attribute.hpp"

namespace Yttrium
{
    namespace Memory
    {
        namespace Object
        {

            const char * const Ledger:: CallSign = "Memory::Object::Ledger";
            const unsigned     Ledger:: NumPageShift;

            namespace
            {
                static const unsigned Requested   = sizeof(Pages) * Ledger::NumPageShift;
                static void *         PagesData[ Alignment::WordsGEQ<Requested>::Count ];
                static Pages *        bookPages = 0;
            }

            Ledger:: Ledger()  : Singleton<Ledger,BroadLockPolicy>()
            {
                assert(0==bookPages);
                bookPages = static_cast<Pages *>( Y_Memory_BZero(PagesData) ) - MinPageShift;
                for(unsigned i=MinPageShift;i<=MaxPageShift;++i)
                    new (bookPages+i) Pages(i);
            }

            Ledger:: ~Ledger() noexcept
            {
                assert(0!=bookPages);
                for(unsigned i=MaxPageShift;i>=MinPageShift;--i)
                    Memory::Stealth::Zero( Destructed(bookPages+i), sizeof(Pages) );
                bookPages = 0;
            }

            void Ledger:: display(std::ostream &os, size_t indent) const
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

            void * Ledger:: query(const unsigned blockShift)
            {
                Y_Lock(access);
                assert(blockShift>=MinPageShift);
                assert(blockShift<=MaxPageShift);
                return bookPages[blockShift].query();
            }

            void   Ledger:: store(const unsigned blockShift, void * const blockAddr) noexcept
            {
                Y_Lock(access);
                assert(blockShift>=MinPageShift);
                assert(blockShift<=MaxPageShift);
                bookPages[blockShift].store(blockAddr);
            }

            void  Ledger::  cache(const unsigned blockShift, const size_t numPages)
            {
                Y_Lock(access);
                assert(blockShift>=MinPageShift);
                assert(blockShift<=MaxPageShift);
                bookPages[blockShift].cache(numPages);
            }


            void Ledger:: gc(const uint8_t amount) noexcept
            {
                for(unsigned i=MaxPageShift;i>=MinPageShift;--i) bookPages[i].gc(amount);
            }
            

        }
    }

}


