
//! \file

#ifndef Y_RTLD_SoakAPI_Included
#define Y_RTLD_SoakAPI_Included 1

#include "y/rtld/dso.h"
#include "y/exception.hpp"
#include "y/ability/identifiable.hpp"
#include "y/object.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! API For Soak classes
    //
    //
    //__________________________________________________________________________
    class SoakAPI : public Object, public Identifiable
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        static const size_t       MessageLength = 256; //!< to store messages
        static const char * const UnhandledException;  //!< "unhandled exception"

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
    protected:
        explicit SoakAPI() noexcept; //!< setup

    public:
        virtual ~SoakAPI() noexcept; //!< cleanup

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        static void OnError(const std::exception &, const char * const) noexcept; //!< fill What/When
        static void OnError(const Exception &)                          noexcept; //!< fill What/When
        static void OnError(const char * const, const char * const)     noexcept; //!< fill What/When

        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________
        static char What[MessageLength]; //!< store exception/message content
        static char When[MessageLength]; //!< store exception/message content

    private:
        Y_Disable_Copy_And_Assign(SoakAPI); //!< discarding
        static void NoError() noexcept;     //!< clean What/When

    protected:
        void        onValid() const noexcept; //!< write CallSign in What
    };

}


#endif // !Y_RTLD_SoakAPI_Included
