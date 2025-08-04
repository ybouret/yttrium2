


//! \file

#ifndef Y_Output_Sizing_Stream_Included
#define Y_Output_Sizing_Stream_Included 1

#include "y/stream/output.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! count bytes that should be emitted
    //
    //
    //__________________________________________________________________________
    class SizingOutput : public OutputStream
    {
    public:
        explicit SizingOutput() noexcept; //!< setup
        virtual ~SizingOutput() noexcept; //!< cleanup

        virtual void write(const char);   //!< increase result
        virtual void flush();             //!< do noting

        const size_t result; //!< store result, increased upon write()
    private:
        Y_Disable_Copy_And_Assign(SizingOutput); //!< discarding
    };

}

#endif
