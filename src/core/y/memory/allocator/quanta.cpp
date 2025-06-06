
#include "y/memory/allocator/quanta.hpp"
#include "y/object/factory.hpp"
#include "y/memory/small/guild.hpp"
#include "y/memory/small/ledger.hpp"

#include "y/memory/workspace/cxx.hpp"
#include "y/xml/attribute.hpp"
#include "y/system/exception.hpp"
#include "y/decimal.hpp"

#include <iostream>

namespace Yttrium
{
    namespace Memory
    {

        const char * const Quanta:: CallSign = "Memory::Quanta";

        Quanta:: Manager:: Manager(const unsigned int blockShift) noexcept :
        shift( blockShift ),
        bytes( size_t(1) << blockShift )
        {

        }

        Quanta:: Manager:: ~Manager() noexcept
        {

        }

        namespace
        {


            class SmallManager :
            public Quanta::Manager,
            public Small::Guild
            {
            public:
                inline explicit SmallManager(const unsigned blockShift) :
                Quanta::Manager(blockShift),
                Small::Guild(bytes)
                {
                    //std::cerr << "[+] " << bytes << std::endl;
                }

                inline virtual ~SmallManager() noexcept
                {
                }

                inline virtual void * acquire()
                {
                    return acquireBlock();
                }

                inline virtual void   release(void * const addr) noexcept
                {
                    assert(0!=addr);
                    releaseBlock(addr);
                }


                //! for procedural creation
                static void Create(void * const addr, const size_t blockShift)
                {
                    new (addr) SmallManager(unsigned(blockShift));
                }

            private:
                Y_Disable_Copy_And_Assign(SmallManager);
            };

            

        }

        namespace
        {
            class LargeManager : public Quanta::Manager
            {
            public:
                inline explicit LargeManager(const unsigned blockShift) :
                Quanta::Manager(blockShift),
                ledger( Small::Ledger::Instance() )
                {
                    //std::cerr << "[+] " << bytes << std::endl;
                }

                inline virtual ~LargeManager() noexcept {}

                inline virtual void *acquire()
                {
                    return ledger.query(shift);
                }

                inline virtual void   release(void * const addr) noexcept
                {
                    assert(0!=addr);
                    ledger.store(shift,addr);
                }

                static void Create(void * const addr, const size_t blockShift)
                {
                    new (addr) LargeManager(unsigned(blockShift));
                }

                Memory::Small::Ledger &ledger;

            private:
                Y_Disable_Copy_And_Assign(LargeManager);
            };


        }



        class Quanta:: Code
        {
        public:
            explicit Code() :
            manager(),
            smallManager(Procedural,SmallManager::Create,0),
            largeManager(Procedural,LargeManager::Create,NumBlocksShift)
            {
                Y_Memory_BZero(manager);

                for(unsigned i=0;i<=MaxBlocksShift;++i)
                {
                    manager[i] = &smallManager[i+1];
                    assert(i==manager[i]->shift);
                }

                for(unsigned i=0;i<NumLargerShift;++i)
                {
                    manager[i+NumBlocksShift] = &largeManager[i+1];
                    assert(i+NumBlocksShift==manager[i+NumBlocksShift]->shift);
                }

            }

            inline ~Code() noexcept
            {
            }

            Manager *                                   manager[MaxLedgerShift+1];
            CxxWorkspace<SmallManager,NumBlocksShift>   smallManager;
            CxxWorkspace<LargeManager,NumLargerShift>   largeManager;

        private:
            Y_Disable_Copy_And_Assign(Code);
        };

        namespace
        {
            static void * codeWorkspace[ Alignment::WordsFor<Quanta::Code>::Count ];
        }


        const unsigned Quanta:: NumBlocksShift;
        const unsigned Quanta:: NumLargerShift;

        Quanta:: Quanta() :
        Singleton<Quanta,ClassLockPolicy>(),
        Allocator(CallSign),
        code( new (Y_Memory_BZero(codeWorkspace)) Code()  )
        {
        }

        Quanta:: ~Quanta() noexcept
        {
            assert(0!=code);
            (void) Stealth::DestructedAndZeroed(code);
            Coerce(code) = 0;
        }

        void Quanta:: display(std::ostream &os, size_t indent) const
        {
            assert(0!=code);
            initProlog(os,indent)
            << Y_XML_Attr(NumBlocksShift)
            << Y_XML_Attr(NumLargerShift);
            initEpilog(os,false);

            ++indent;
            Memory::Small::Ledger::Location().display(os,indent);
            --indent;

            quit(os,indent);
        }

        void * Quanta:: acquireDyadic(const unsigned int blockShift)
        {
            assert(blockShift<=MaxLedgerShift);
            assert(blockShift==code->manager[blockShift]->shift);
            return code->manager[blockShift]->acquire();
        }

        void Quanta:: releaseDyadic(const unsigned int blockShift, void *const blockAddr) noexcept
        {
            assert(0!=blockAddr);
            assert(blockShift<=MaxLedgerShift);
            assert(blockShift==code->manager[blockShift]->shift);
            code->manager[blockShift]->release(blockAddr);
        }

        const size_t Quanta::MaxLedgerBytes;

        void * Quanta:: acquireBlock(size_t &blockSize)
        {
            assert(blockSize>0);
            if(blockSize>=MaxLedgerBytes)
                throw Specific::Exception(CallSign,"blockSize=%s exceeed %s", Decimal(blockSize).c_str(), Decimal(MaxLedgerBytes).c_str());

            unsigned blockShift = 0;
            blockSize = NextPowerOfTwo(blockSize,blockShift);
            return code->manager[blockShift]->acquire();
        }


        void Quanta:: releaseBlock(void * const blockAddr, const size_t blockSize) noexcept
        {
            assert(0!=blockAddr);
            assert(IsPowerOfTwo(blockSize));
            code->manager[ ExactLog2(blockSize) ]->release(blockAddr);
        }

    }

}
