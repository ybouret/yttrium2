#include "y/concurrent/mutex.hpp"
#include "y/system/platform.hpp"
#include "y/memory/workspace.hpp"
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

        Mutex:: Mutex() : code( Memory::Object::Blocks::Instance().createAs<Code>() )
        {
        }

        Mutex:: ~Mutex() noexcept
        {
            assert(0!=code);
            Memory::Object::Blocks::Location().deleteAs( Coerce(code) );
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
