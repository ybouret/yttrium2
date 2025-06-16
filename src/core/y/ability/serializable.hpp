

//! \file

#ifndef Y_Serializable_Included
#define Y_Serializable_Included 1

#include "y/core/setup.hpp"


namespace Yttrium
{

    class OutputStream;

    //__________________________________________________________________________
    //
    //
    //
    //! Resettable interface
    //
    //
    //__________________________________________________________________________
    class Serializable
    {
    protected:
        explicit Serializable() noexcept; //!< setup

    public:
        virtual ~Serializable() noexcept; //!< cleanup

        //! portable encoding \return written bytes
        virtual size_t serialize(OutputStream &) noexcept = 0;

    private:
        Y_Disable_Copy_And_Assign(Serializable); //!< discarding
    };

}

#endif

