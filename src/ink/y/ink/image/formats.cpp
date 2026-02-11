
#include "y/ink/image/formats.hpp"
#include "y/xml/attribute.hpp"

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


        void Formats:: display(std::ostream &os ,
                               size_t        indent) const
        {
            const size_t numFormats = size();
            initProlog(os,indent) << Y_XML_Attr(numFormats);
            initEpilog(os,false);
            ++indent;
            for(ConstIterator it=begin();it!=end();++it)
            {
                const Format &fmt = **it;
                XML::Indent(os,indent) << "[+] '" << fmt.name << "'" << std::endl;
            }
            --indent;
            quit(os,indent);
        }
    }

}
