//! \file

#ifndef Y_Container_Included
#define Y_Container_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! Container interface
    //
    //
    //__________________________________________________________________________
    class Container
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        static const char LBRACK     = '['; //!< alias
        static const char RBRACK     = ']'; //!< alias
        static const char SEMICOLON  = ';'; //!< alias

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
    protected:
        explicit Container() noexcept; //!< initialize

    public:
        virtual ~Container() noexcept; //!< cleanup

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual size_t size() const noexcept = 0; //!< \return current size

    private:
        Y_Disable_Copy_And_Assign(Container); //!< discarding
    };
}


#endif // !Y_Container_Included

