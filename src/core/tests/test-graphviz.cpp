#include "y/graphviz/vizible.hpp"
#include "y/graphviz/color-scheme.hpp"
#include "y/utest/run.hpp"
#include "y/stream/libc/output.hpp"
#include "y/string.hpp"
#include <cctype>
#include "y/format/decimal.hpp"
#include "y/vfs/local/fs.hpp"

using namespace Yttrium;

Y_UTEST(graphviz)
{

#if 0

    if(false)
    {
        static const char esc[] = "\n\r\t\"";
        static const char viz[] = "nrt\"0";
        //static const char num   = sizeof(esc)-1;

        static const char raw[] = "!@#$%^&*()_-+={}[]';:/?.,><";

        uint8_t c=0;
        for(size_t i=0;i<16;++i)
        {
            for(size_t j=0;j<16;++j,++c)
            {
                std::cerr << " \"";
                if( isalnum(c) || (c>0 && strchr(raw,c)) )
                {
                    std::cerr << char(c);
                }
                else
                {
                    if(const char * const p = strchr(esc,c))
                    {
                        std::cerr << "\\\\\\\\" << viz[p-esc];
                    }
                    else
                    {
                        char buff[16];
                        snprintf(buff,sizeof(buff),"\\\\x%02x",c);
                        std::cerr << buff;
                    }

                }
                std::cerr << "\"";
                if(c<255) std::cerr << ",";
            }
            std::cerr << std::endl;
        }
        std::cerr << std::endl;

    }
#endif


    Vizible viz[256];
    int     c = 0;

    {
        OutputFile fp("table.dot");
        Vizible::Enter(fp);
        for(size_t i=0;i<16;++i)
        {
            for(size_t j=0;j<16;++j,++c)
            {
                const char C = (char)c;
                viz[c].nodeName(fp) << '[';
                const String label = C; Y_ASSERT(1==label.size());
                Vizible::Label(fp,label);
                Vizible::Endl(fp << ']');

                if(j>0)
                {
                    Vizible::Endl( viz[c-1].to( &viz[c], fp ) );
                }
            }
        }
        Vizible:: Leave(fp);
    }

    Vizible::DotToPng("table.dot");


    {
        LocalFS &fs = LocalFS::Instance();
        const String dirName = "tmp/";
        fs.createSubDirs(dirName);


        for(unsigned i=0;i<GraphViz::ColorScheme::Count;++i)
        {
            const GraphViz::ColorScheme &cs = GraphViz::ColorScheme::Table[i];
            const String fileName = dirName + cs.name + ".dot";
            {
                OutputFile fp(fileName);
                Vizible::Enter(fp);
                //std::cerr << cs.name << std::endl;
                Vizible::Endl(fp << cs.name);
                for(size_t i=0;i<cs.size;++i)
                {
                    const Decimal      d = Decimal(i);
                    const char * const id = d.c_str();
                    const String       sub = String(cs.name) + id;

                    fp << sub << "[label=\"" << id << "\"";
                    fp << ",shape=box,style=filled,fillcolor=" << cs[i];
                    Vizible::Endl(fp << "]");
                    Vizible::Endl(fp << cs.name << " -> " << sub);
                }
                Vizible::Leave(fp);
            }
            Vizible::DotToPng(fileName);

        }
    }


}
Y_UDONE()

