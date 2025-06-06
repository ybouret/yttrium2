#include "y/concurrent/condition.hpp"
#include "y/system/platform.hpp"
#include "y/memory/workspace/solitary.hpp"
#include "y/system/exception.hpp"
#include "y/memory/small/blocks.hpp"

#if defined(Y_BSD)
#include "mutex/bsd.hxx"
#endif

#if defined(Y_WIN)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "mutex/win.hxx"
#endif



namespace Yttrium
{
    namespace Concurrent
    {

        typedef Memory::Small::Blocks Provider;

        Mutex:: Mutex() : code( Provider::Instance().createAs<Code>() )
        {
        }

        Mutex:: ~Mutex() noexcept
        {
            assert(0!=code);
            Provider::Location().deleteAs( Coerce(code) );
        }
        
        void Mutex:: doLock() noexcept
        {
            assert(0!=code);
            code->lock();
        }

        void Mutex:: doUnlock() noexcept
        {
            assert(0!=code);
            code->unlock();
        }

        bool Mutex:: doTryLock() noexcept
        {
            assert(0!=code);
            return code->tryLock();
        }


    }
}


namespace Yttrium
{
    namespace Concurrent
    {

        Condition:: Condition() : code( Provider::Instance().createAs<Code>() )
        {
            std::cerr << "sizeof(Condition::Code)=" << sizeof(Code) << std::endl;
        }

        Condition:: ~Condition() noexcept
        {
            assert(0!=code);
            Provider::Location().deleteAs( Coerce(code) );
        }

        void Condition:: wait(Mutex &mutex) noexcept
        {
            assert(0!=code);
            code->wait(mutex);
        }

        void Condition:: signal() noexcept
        {
            assert(0!=code);
            code->signal();
        }


    }
}

