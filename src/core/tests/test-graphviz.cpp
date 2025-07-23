#include "y/graphviz/vizible.hpp"
#include "y/utest/run.hpp"
#include "y/stream/libc/output.hpp"
#include "y/string.hpp"
#include <cctype>

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
                const char C = c;
                viz[c].name(fp) << '[';
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

    
}
Y_UDONE()

