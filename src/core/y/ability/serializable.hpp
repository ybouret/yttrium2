

//! \file

#ifndef Y_Serializable_Included
#define Y_Serializable_Included 1

#include "y/core/setup.hpp"
#include "y/string/fwd.hpp"

namespace Yttrium
{

    class OutputStream;
    class InputStream;
    
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
        virtual size_t serialize(OutputStream &) const = 0;

        //! \return binary code
        Core::String<char> toBinary() const;
        

    private:
        Y_Disable_Copy_And_Assign(Serializable); //!< discarding
    };

}

#endif

