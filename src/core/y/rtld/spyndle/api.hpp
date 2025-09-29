
//! \file

#ifndef Y_RTLD_SpyndleAPI_Included
#define Y_RTLD_SpyndleAPI_Included 1

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
    //! API For SpyndleClass
    //
    //
    //__________________________________________________________________________
    class SpyndleAPI : public Object, public Identifiable
    {
    public:
        static const size_t  MessageLength = 256;
        static char          What[MessageLength];
        static char          When[MessageLength];
        static void          NoMessage() noexcept;
        static void          OnError(const char * const what, const char * const when) noexcept;
        static void          OnError(const std::exception &,  const char * const when) noexcept;
        static void          OnError(const Exception &)                                noexcept;

        
        virtual ~SpyndleAPI() noexcept;
    protected:
        explicit SpyndleAPI() noexcept;

    private:
        Y_Disable_Copy_And_Assign(SpyndleAPI);
    };

#define Y_Spyndle_Code(CODE,SUCCESS,FAILURE) \
/**/ do {\
/**/    try { CODE; SUCCESS; }\
/**/    catch(const Yttrium::Exception &excp) { OnError(excp); FAILURE; }\
/**/    catch(const std::exception     &excp) { OnError(excp,ClassType::CallSign); FAILURE; } \
/**/    catch(...) { OnError("Unhandled Exception",ClassType::CallSign); FAILURE; } \
/**/ } while(false)


}

#endif // !Y_RTLD_SpyndleAPI_Included

