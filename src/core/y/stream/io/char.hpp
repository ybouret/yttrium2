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
        //______________________________________________________________________
        //
        //
        //
        //! node for Chars, managed by Inventory
        //
        //
        //______________________________________________________________________
        class Char
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Declare_Spec(uint8_t,Type); //!< aliases
            typedef uint8_t ReturnType;        //!< alias
            static const System::AtExit::Longevity                   LifeTime = LifeTimeOf::IOChars; //!< lifetime
            static const char * const                                CallSign;                       //!< "IO::Char"
            typedef Protean::WarpedCacheOf<Char,MultiThreadedHandle> Cache;                          //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            Char(ParamType)    noexcept;             //!< setup
            Char(const Char &) noexcept;             //!< duplicate
            ~Char() noexcept;                        //!< cleanup
            Char & operator=(const Char &) noexcept; //!< assign \return *this

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            ConstType    & operator*() const noexcept; //!< \return content
            Type         & operator*()       noexcept; //!< \return content
            static Cache & CacheInstance();            //!< global instance \return Inventory<Char>

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            Char *      next; //!< for list
            Char *      prev; //!< for list
        private:
            MutableType code; //!< content
        };
    }

}

#endif

