
#include "y/graphviz/vizible.hpp"
#include "y/format/hexadecimal.hpp"
#include "y/string.hpp"
#include "y/stream/output.hpp"
#include "y/ascii/embedding.hpp"

namespace Yttrium
{

    

    Vizible:: Vizible() noexcept {}

    Vizible:: ~Vizible() noexcept
    {
    }


    OutputStream & Vizible:: Endl(OutputStream &fp)
    {
        return fp << ';' << '\n';
    }


    OutputStream & Vizible:: name(OutputStream &fp) const
    {
        union {
            uint64_t       data;
            const void *   addr;
        } alias = { 0 };
        alias.addr = this;

        const Hexadecimal id(alias.data,Concise);
        return fp << 'n' << id.c_str();
    }


    OutputStream & Vizible:: to(const Vizible * const target, OutputStream &fp) const
    {
        assert(0!=target);
        return target->name( name(fp) << " -> " );
    }

    OutputStream & Vizible:: Label(OutputStream &fp, const String &id)
    {
        fp << "label=\"";
        for(size_t i=1;i<=id.size();++i)
        {
            fp << ASCII::Embedding::Text(id[i]);
        }
        return fp << "\"";
    }

    OutputStream & Vizible:: Label(OutputStream &fp, const char * const id)
    {
        const String _(id);
        return Label(fp,_);

    }

    OutputStream & Vizible:: Label(OutputStream &fp, const char c)
    {
        const String _(c);
        return Label(fp,_);
    }

    OutputStream & Vizible:: Enter(OutputStream &fp)
    {
        return fp << "digraph G {\n";
    }

    OutputStream & Vizible:: Leave(OutputStream &fp)
    {
        return fp << "}\n";
    }

}

#include "y/vfs/local/fs.hpp"
#include "y/stream/libc/output.hpp"

namespace Yttrium
{


    void Vizible:: DotToPng(const String &dotFile, const bool keepDot)
    {
        const String pngFile = VFS::ChangedExtension("png", dotFile);
        const String cmd = "dot -T png " + dotFile + " -o " + pngFile;
        system(cmd.c_str());
        if(!keepDot) LocalFS::Instance().tryRemoveFile(dotFile);
    }


    void Vizible:: DotToPng(const char * const dotFile, const bool keepDot)
    {
        const String _(dotFile);
        DotToPng(_,keepDot);
    }

    OutputStream * Vizible:: NewDotFile(const Core::String<char> &fileName)
    {
        return new OutputFile(fileName);
    }

    OutputStream * Vizible:: NewDotFile(const char * const fileName)
    {
        return new OutputFile(fileName);
    }
    
    void Vizible:: DelDotFile(OutputStream * const handle) noexcept
    {
        assert(0!=handle);
        delete handle;
    }


}

