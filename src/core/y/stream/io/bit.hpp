
//! \file

#ifndef Y_IO_Bit_Included
#define Y_IO_Bit_Included 1

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
        //! I/O bit
        //
        //
        //______________________________________________________________________
        class Bit
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Declare_Spec(bool,Type); //!< aliases
            typedef bool ReturnType;        //!< alias
            static const System::AtExit::Longevity                  LifeTime = LifeTimeOf::IOBits; //!< lifetime
            static const char * const                               CallSign;                      //!< "IO::Bits"
            typedef Protean::WarpedCacheOf<Bit,MultiThreadedHandle> Cache;                         //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            Bit(ParamType)               noexcept; //!< setup
            Bit(const Bit &)             noexcept; //!< duplicate
            ~Bit()                       noexcept; //!< cleanup
            Bit & operator=(const Bit &) noexcept; //!< assign \return *this

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
            Bit *  next; //!< for list
            Bit *  prev; //!< for list
        private:
            bool   code; //!< content
        };
    }

}

#endif // !Y_IO_Bit_Included

