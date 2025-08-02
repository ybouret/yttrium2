
//! \file

#ifndef Y_Jive_Char_Included
#define Y_Jive_Char_Included 1

#include "y/jive/context.hpp"
#include "y/concurrent/life-time.hpp"
#include "y/protean/cache/warped.hpp"
#include "y/threading/multi-threaded-handle.hpp"
#include "y/core/linked/list.hpp"

namespace Yttrium
{
    namespace Jive
    {

        //______________________________________________________________________
        //
        //
        //
        //! byte with full context
        //
        //
        //______________________________________________________________________
        class Char : public Context
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Declare_Spec(uint8_t,Type);                                                         //!< aliases
            static const System::AtExit::Longevity                   LifeTime = LifeTimeOf::JiveChars; //!< lifetime
            static const char * const                                CallSign;                         //!< "Jive::Char"
            typedef Protean::WarpedCacheOf<Char,MultiThreadedHandle> Cache;                            //!< alias
            typedef Core::ListOf<Char>                               List;                             //!< alis

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            Char(ParamType, const Context &)    noexcept; //!< setup
            Char(const Char &) noexcept;                  //!< duplicate
            virtual ~Char() noexcept;                     //!< cleanup

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
            Y_Disable_Assign(Char); //!< discarding
            MutableType code;       //!< content

        };
    }

}

#endif

