
#include "y/ascii/convert.hpp"
#include "y/utest/run.hpp"
#include <cstring>
#include "y/format/hexadecimal.hpp"

using namespace Yttrium;

Y_UTEST(ascii_convert)
{
    for(int i=1;i<argc;++i)
    {
        try
        {
            const apz z = ASCII::Conversion::DirectParser<apz>::Get(argv[i], strlen(argv[i]));
            std::cerr << "z=" << z << std::endl;
        }
        catch(const Exception &excp) { excp.show(std::cerr); }
        catch(...) { throw; }

        try
        {
            const apn n = ASCII::Conversion::DirectParser<apn>::Get(argv[i], strlen(argv[i]));
            std::cerr << "n=" << n << std::endl;
        }
        catch(const Exception &excp) { excp.show(std::cerr); }
        catch(...) { throw; }

        try
        {
            const uint16_t u = ASCII::Conversion::AProxyParser<uint16_t>::Get(argv[i], strlen(argv[i]));
            std::cerr << "u=" << u << std::endl;
        }
        catch(const Exception &excp) { excp.show(std::cerr); }
        catch(...) { throw; }

        try
        {
            const signed char s = ASCII::Conversion::AProxyParser<signed char>::Get(argv[i], strlen(argv[i]));
            std::cerr << "s=" << s << std::endl;
        }
        catch(const Exception &excp) { excp.show(std::cerr); }
        catch(...) { throw; }

        try
        {
            bool   sg = false;
            String ip;
            String fp;
            apz    xp;
            ASCII::Conversion::Parsing::FPoint(sg,ip,fp,xp,argv[i],strlen(argv[i]));
            std::cerr << "ip='"; Hexadecimal::Display(std::cerr,ip(),ip.size()); std::cerr << "'" << std::endl;
            std::cerr << "fp='"; Hexadecimal::Display(std::cerr,fp(),fp.size()); std::cerr << "'" << std::endl;


            std::cerr << "xp='" << xp << "'" << std::endl;
        }
        catch(const Exception &excp) { excp.show(std::cerr); }
        catch(...) { throw; }


    }
}
Y_UDONE()

