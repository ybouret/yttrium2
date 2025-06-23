//! \file

#ifndef Y_Stream_IO_Char_Included
#define Y_Stream_IO_Char_Included 1

#include "y/core/setup.hpp"
#include "y/type/args.hpp"
#include "y/concurrent/life-time.hpp"
#include "y/protean/cache/warped.hpp"
#include "y/threading/multi-threaded-handle.hpp"

namespace Yttrium
{

    namespace IO
    {
        class Char
        {
        public:
            Y_ARGS_DECL(uint8_t,Type);
            static const System::AtExit::Longevity LifeTime = LifeTimeOf::IOChars;
            static const char * const              CallSign;
            typedef Protean::WarpedCacheOf<Char,MultiThreadedHandle> Cache;



            ConstType & operator*() const noexcept { return code; }
            Type      & operator*()       noexcept { return code; }


            Char *  next;
            Char *  prev;

            Char(ParamType)    noexcept;
            Char(const Char &) noexcept;
            ~Char() noexcept;
            Char & operator=(const Char &) noexcept;

            static Cache & CacheInstance();
            

        private:
            MutableType code;
        };
    }

}

#endif

