
#include "y/ink/image/format.hpp"
#include "y/jive/regexp.hpp"

namespace Yttrium
{
    namespace Ink
    {

        Format:: ~Format() noexcept
        {
        }

        Jive::Pattern * Format:: MakePattern(String &rx)
        {
            return Jive::RegExp::Compile(((rx >> '(') << ')' << '&'));
        }

        void Format:: renderExtension() const
        {
            const String dotFile = name + ".dot";
            Vizible::Render(dotFile,*extension.motif);
        }




    }

}

#include "y/vfs/vfs.hpp"
namespace Yttrium
{
    namespace Ink
    {
        String Format:: LowerCaseExt(const String &path)
        {
            const char * const pExt = VFS::Extension(path);
            if(!pExt) return String();
            String ext = pExt+1;
            for(size_t i=ext.size();i>0;--i)
            {
                ext[i] = (char) tolower(ext[i]);
            }
            return ext;
        }

    }
}
