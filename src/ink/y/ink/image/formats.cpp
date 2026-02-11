
#include "y/ink/image/formats.hpp"

namespace Yttrium
{
    namespace Ink
    {

        const char * const Formats:: CallSign = "Ink::Formats";

        Formats:: ~Formats() noexcept
        {
            
        }


        Formats:: Formats() :
        Singleton<Formats,ClassLockPolicy>(),
        FormatsDB()
        {
        }

        void Formats:: operator()(Format * const fmt)
        {
            assert( 0 != fmt );
            Format::Handle hfm = fmt;
            if( ! insert(hfm) )
                throw Specific::Exception(CallSign,"mulitple format '%s'", hfm->key().c_str());
        }



    }

}
