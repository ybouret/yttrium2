
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
    //! API For Spyndle<Class>
    //
    //
    //__________________________________________________________________________
    class SpyndleAPI : public Object, public Identifiable
    {
    public:

        //______________________________________________________________________
        //
        //
        // error handling
        //
        //______________________________________________________________________

        static const size_t  MessageLength = 256; //!< alias
        static char          What[MessageLength]; //!< holds global error what
        static char          When[MessageLength]; //!< holds global error when
        static void          NoMessage() noexcept; //!< cleanup
        static void          OnError(const char * const what, const char * const when) noexcept; //!< \param what what \param when when
        static void          OnError(const std::exception &,  const char * const when) noexcept; //!< use exception what() \param when when
        static void          OnError(const Exception &)                                noexcept; //!< use exception what()/when()


        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        virtual ~SpyndleAPI() noexcept; //!< cleanup
    protected:
        explicit SpyndleAPI() noexcept; //!< setup

    private:
        Y_Disable_Copy_And_Assign(SpyndleAPI); //!< discarding
    };

    //! helper to intercept exception
#define Y_Spyndle_Code(CODE,SUCCESS,FAILURE) \
/**/ do {\
/**/    try { CODE; SUCCESS; }\
/**/    catch(const Yttrium::Exception &excp) { OnError(excp); FAILURE; }\
/**/    catch(const std::exception     &excp) { OnError(excp,ClassType::CallSign); FAILURE; } \
/**/    catch(...) { OnError("Unhandled Exception",ClassType::CallSign); FAILURE; } \
/**/ } while(false)

    //! boolean code
#define Y_Spyndle_Boolean(CODE) Y_Spyndle_Code(CODE,return true,return false)

}

#endif // !Y_RTLD_SpyndleAPI_Included

