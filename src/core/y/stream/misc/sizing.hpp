


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
        explicit SizingOutput() noexcept;
        virtual ~SizingOutput() noexcept;

        virtual void write(const char);
        virtual void flush();

        const size_t result;
    private:
        Y_Disable_Copy_And_Assign(SizingOutput);
    };

}

#endif
