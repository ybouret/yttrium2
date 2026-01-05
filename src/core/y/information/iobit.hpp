
//! \file

#ifndef Y_Information_IOBit_Included
#define Y_Information_IOBit_Included 1

#include "y/type/args.hpp"
#include "y/concurrent/life-time.hpp"
#include "y/protean/cache/warped.hpp"
#include "y/threading/multi-threaded-handle.hpp"

namespace Yttrium
{

    namespace Information
    {
        //______________________________________________________________________
        //
        //
        //
        //!
        //
        //
        //______________________________________________________________________
        class IOBit
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
            static const System::AtExit::Longevity                    LifeTime = LifeTimeOf::IOBits; //!< lifetime
            static const char * const                                 CallSign;                      //!< "Information::Bit"
            typedef Protean::WarpedCacheOf<IOBit,MultiThreadedHandle> Cache;                         //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            IOBit(ParamType)                 noexcept; //!< setup
            IOBit(const IOBit &)             noexcept; //!< duplicate
            ~IOBit()                         noexcept; //!< cleanup
            IOBit & operator=(const IOBit &) noexcept; //!< assign \return *this

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
            IOBit *  next; //!< for list
            IOBit *  prev; //!< for list
        private:
            bool     code; //!< content
        };
    }

}

#endif // !Y_Information_IOBit_Included

