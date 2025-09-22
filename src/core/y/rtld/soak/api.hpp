
//! \file

#ifndef Y_RTLD_SoakAPI_Included
#define Y_RTLD_SoakAPI_Included 1

#include "y/rtld/dso.h"
#include "y/exception.hpp"
#include "y/ability/identifiable.hpp"
#include "y/object.hpp"

namespace Yttrium
{

    class SoakAPI : public Object, public Identifiable
    {
    public:
        static const size_t       MessageLength = 256;
        static const char * const UnhandledException;
    protected:
        explicit SoakAPI() noexcept;

    public:
        virtual ~SoakAPI() noexcept;

        static void OnError(const std::exception &, const char * const) noexcept;
        static void OnError(const Exception &)                          noexcept;
        static void OnError(const char * const, const char * const)     noexcept;

        
        static char What[MessageLength];
        static char When[MessageLength];

    private:
        Y_Disable_Copy_And_Assign(SoakAPI);
        static void NoError() noexcept;
    };

}


#endif // !Y_RTLD_SoakAPI_Included
