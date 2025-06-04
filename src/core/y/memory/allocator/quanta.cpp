
#include "y/memory/allocator/quanta.hpp"
#include "y/memory/object/factory.hpp"
#include "y/memory/object/guild.hpp"
#include "y/memory/object/book.hpp"

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
            public Object::Guild
            {
            public:
                inline explicit SmallManager(const unsigned blockShift) :
                Quanta::Manager(blockShift),
                Object::Guild(bytes)
                {
                    std::cerr << "[+] " << bytes << std::endl;
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
                book( Object::Book::Instance() )
                {
                    std::cerr << "[+] " << bytes << std::endl;
                }

                inline virtual ~LargeManager() noexcept {}

                inline virtual void *acquire()
                {
                    return book.query(shift);
                }

                inline virtual void   release(void * const addr) noexcept
                {
                    assert(0!=addr);
                    book.store(shift,addr);
                }

                static void Create(void * const addr, const size_t blockShift)
                {
                    new (addr) LargeManager(unsigned(blockShift));
                }

                Memory::Object::Book &book;

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
            largeManager(Procedural,LargeManager::Create,NumFactoryShift)
            {
                Y_Memory_BZero(manager);

                for(unsigned i=0;i<=MaxFactoryShift;++i)
                {
                    manager[i] = &smallManager[i+1];
                    assert(i==manager[i]->shift);
                }

                for(unsigned i=0;i<NumGreaterShift;++i)
                {
                    manager[i+NumFactoryShift] = &largeManager[i+1];
                    assert(i+NumFactoryShift==manager[i+NumFactoryShift]->shift);
                }

            }

            inline ~Code() noexcept
            {
            }

            Manager *                                   manager[MaxAllowedShift+1];
            CxxWorkspace<SmallManager,NumFactoryShift>  smallManager;
            CxxWorkspace<LargeManager,NumGreaterShift>  largeManager;

        private:
            Y_Disable_Copy_And_Assign(Code);
        };

        namespace
        {
            static void * codeWorkspace[ Alignment::WordsFor<Quanta::Code>::Count ];
        }


        const unsigned Quanta:: NumFactoryShift;
        const unsigned Quanta:: NumGreaterShift;

        Quanta:: Quanta() :
        Singleton<Quanta, QuantaLockPolicy>(),
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
            << Attribute("NumFactoryShift",NumFactoryShift)
            << Attribute("NumGreaterShift",NumGreaterShift);
            initEpilog(os,false);

            ++indent;
            Memory::Object::Book::Location().display(os,indent);
            --indent;

            quit(os,indent);
        }

        void * Quanta:: acquireDyadic(const unsigned int blockShift)
        {
            assert(blockShift<=MaxAllowedShift);
            assert(blockShift==code->manager[blockShift]->shift);
            return code->manager[blockShift]->acquire();
        }

        const size_t Quanta::MaxAllowedBytes;

        void * Quanta:: acquireBlock(size_t &blockSize)
        {
            assert(blockSize>0);
            if(blockSize>=MaxAllowedBytes)
                throw Specific::Exception(CallSign,"blockSize=%s exceeed %s", Decimal(blockSize).c_str(), Decimal(MaxAllowedBytes).c_str());

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
