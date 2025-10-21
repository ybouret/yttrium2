
//! \file

#ifndef Y_Justify_Included
#define Y_Justify_Included 1

#include "y/string.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Justified display
    //
    //
    //__________________________________________________________________________
    class Justify
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________

        //! how to...
        enum Type
        {
            Left,   //!< left + space
            Center, //!< space/2 + center + (space-space/2)
            Right   //!< space + right
        };

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        Justify(const char * const, const size_t, const Type = Left) noexcept; //!< setu[
        Justify(const String &,     const size_t, const Type = Left) noexcept; //!< setu[
        Justify(const Justify&) noexcept; //!< duplicate
        ~Justify() noexcept;              //!< cleanup
        Y_OSTREAM_PROTO(Justify);         //!< display

    private:
        Y_Disable_Assign(Justify); //!< discarding
        const char * const text;   //!< persistent text
        const size_t       size;   //!< text size
        const Type         type;   //!< how to
        const size_t       width;  //!< required width

        std::ostream &raw(std::ostream&) const; //!< display text \return stream
    };

}

#endif // !Y_Justify_Included

