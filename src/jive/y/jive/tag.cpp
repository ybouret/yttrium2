
#include "y/jive/tag.hpp"
#include "y/stream/input.hpp"
#include "y/pointer/auto.hpp"
#include "y/system/exception.hpp"
#include "y/format/decimal.hpp"

namespace Yttrium
{
    namespace Jive
    {

        const char * const Tag:: CallSign = "Jive::Tag";

        Tag:: ~Tag() noexcept
        {
        }

        Tag:: Tag(const Tag &tag) noexcept :
        TagType(tag), Serializable()
        {}

        Tag:: Tag(String * const p) noexcept : TagType(p) {}


        Tag:: Tag(const String &s) : TagType( new String(s) ) {}

        Tag:: Tag(const char * const s) : TagType( new String(s) ) {}

        Tag:: Tag(const char c) : TagType( new String(c) ) {}


        size_t Tag:: serialize(OutputStream &fp) const
        {
            return (**this).serialize(fp);
        }


        String * LoadTag(InputStream &fp)
        {
            const size_t    length = fp.readVBR<size_t>(Tag::CallSign,"length");
            AutoPtr<String> pstr   = new String(WithAtLeast,length,false);
            for(size_t i=1;i<=length;++i)
            {
                char c = 0;
                if(!fp.query(c))
                    throw Specific::Exception(Tag::CallSign,"missing char %s/%s", Decimal(i).c_str(), Decimal(length).c_str());
                *pstr += c;
            }
            return pstr.yield();
        }

        Tag:: Tag(InputStream &fp) : TagType( LoadTag(fp) )
        {

        }

        Tag & Tag:: operator+=( const Tag &rhs )
        {
            Coerce((**this)) += *rhs;
            return *this;
        }

        Tag & Tag:: operator+=(const String &rhs)
        {
            Coerce((**this)) += rhs;
            return *this;
        }

        Tag & Tag:: operator+=(const char * const rhs)
        {
            Coerce((**this)) += rhs;
            return *this;
        }

        Tag & Tag:: operator+=(const char rhs)
        {
            Coerce((**this)) += rhs;
            return *this;
        }

    }

}

