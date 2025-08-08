
#include "y/jive/tagdb.hpp"
#include "y/system/exception.hpp"
namespace Yttrium
{
    namespace Jive
    {
        TagDB:: ~TagDB() noexcept
        {
        }

        TagDB:: TagDB()
        {
        }


        
        Tag TagDB:: get(const String &id)
        {
            if(Tag *p = search(id)) return *p;
            const Tag  tag(id);
            if(!insert(tag)) throw Specific::Exception("Jive::TagDB","failed to insert '%s'", tag->c_str());
            return tag;
        }

        Tag TagDB:: get(const char * const id)
        {
            const String _(id); return get(_);
        }

        Tag TagDB:: get(const char C)
        {
            const String _(C); return get(_);
        }

        Tag TagDB:: read(InputStream &fp, const char * const varName)
        {
            const String id(fp,varName);
            return get(id);
        }


    }

}
