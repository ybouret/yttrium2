
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
        FormatsDB(),
        Codec(CallSign)
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


        void  Formats:: onSave(const Image  &image, const String &fileName, const Options * const options) const
        {
            (*this)[fileName].save(image,fileName,options);
        }

        Image Formats:: onLoad(const String &fileName, const Options * const options) const
        {
            return (*this)[fileName].load(fileName,options);
        }

    }

}

#include "y/vfs/vfs.hpp"

namespace Yttrium
{
    namespace Ink
    {

        const Format   & Formats:: operator[](const String &path) const
        {
            const String       base = VFS::BaseName(path);
            const char * const pExt = VFS::Extension(base);
            if(!pExt) throw Specific::Exception(CallSign,"no extension in '%s'", base.c_str());
            const String       ext  = pExt+1;
            //std::cerr << "Looking for extension [" << ext << "] of [" << path << "]" << std::endl;
            {
                Y_Lock( Coerce(access) );
                for(ConstIterator it=begin();it!=end();++it)
                {
                    Format &fmt = Coerce(**it);
                    //std::cerr << "\ttrying '" << fmt.name << "'" << std::endl;
                    if(fmt.extension.found(Jive::Matching::Exactly,base,ext))
                    {
                        //std::cerr << "Found " << fmt.name << " for " << base << std::endl;
                        return fmt;
                    }
                }
            }
            throw Specific::Exception(CallSign,"not format matching '%s'", base.c_str());
        }
    }

}
