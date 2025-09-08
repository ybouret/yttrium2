
#include "y/rtld/dll.hpp"
#include "y/object/counted.hpp"

#include "y/system/platform.hpp"
#include "y/ability/lockable.hpp"
#include "y/system/exception.hpp"
#include "y/type/destroy.hpp"

#if defined(Y_WIN)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#define  Y_DLL HMODULE
#endif

#if defined(Y_BSD)
#include <dlfcn.h>
#define Y_DLL void *
#endif

namespace Yttrium
{
    class DLL:: Code : public CountedObject
    {
    public:
        inline explicit Code(const String &     str) : handle( Init(str) ) {}
        inline explicit Code(const char * const str) : handle( Init(str) ) {}


        inline virtual ~Code() noexcept
        {
            assert(handle);
            Y_Giant_Lock();
            
#if defined(Y_BSD)
            dlclose(handle);
#endif

#if defined(Y_WIN)
            ::FreeLibrary(handle);
#endif

            Coerce(handle) = 0;
        }

        Y_DLL const handle;

    private:
        Y_Disable_Copy_And_Assign(Code);

        static inline Y_DLL Init(const String &dll)
        {
            Y_Giant_Lock();
            const char * const name = dll.c_str();
#if defined(Y_BSD)
            Y_DLL const res = dlopen(name, RTLD_LAZY);
            if(!res)
            {
                const char * err = dlerror();
                if(!err)     err = Core::Unknown;
                throw Specific::Exception("dlopen","%s for '%s'",err,name);
            }
            return res;
#endif

#if defined(Y_WIN)
            Y_DLL const res = ::LoadLibrary(name);
            if(!res)
            {
                throw Windows::Exception( ::GetLastError(), "LoadLibrary(%s)", name);
            }
            return res;
#endif
        }

        static inline Y_DLL Init(const char * const dll)
        {
            const String _(dll);
            return Init(_);
        }

    };


    DLL:: ~DLL() noexcept
    {
        if(code->liberate())
        {
            Destroy(code);
        }
    }

    DLL:: DLL(const String &str) :
    code( new Code(str) )
    {
        code->withhold();
    }

    DLL:: DLL(const char * const str) :
    code( new Code(str) )
    {
        code->withhold();
    }

    DLL:: DLL(const DLL &dll) noexcept :
    code( dll.code )
    {
        code->withhold();
    }


    void * DLL:: query(const String &symbol) const noexcept
    {
        assert(0!=code);
        
#if defined(Y_BSD)
        return dlsym(code->handle,symbol.c_str());
#endif

#if defined(Y_WIN)
        return (void*) ::GetProcAddress(code->handle,symbol.c_str());
#endif
    }

    void * DLL:: query(const char * const symbol) const noexcept
    {
        const String _(symbol); return query(_);
    }



}


