
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
            std::cerr << "z=" << ASCII::Convert::To<apz>(argv[i],"z") << std::endl;
        }
        catch(const Exception &excp) { excp.show(std::cerr); }
        catch(...) { throw; }

        try
        {
            std::cerr << "n=" << ASCII::Convert::To<apn>(argv[i],"n") << std::endl;
        }
        catch(const Exception &excp) { excp.show(std::cerr); }
        catch(...) { throw; }

        try
        {
            std::cerr << "u=" << ASCII::Convert::To<uint16_t>(argv[i],"u") << std::endl;
        }
        catch(const Exception &excp) { excp.show(std::cerr); }
        catch(...) { throw; }

        try
        {
            std::cerr << "s=" << ASCII::Convert::To<signed char>(argv[i],"s") << std::endl;
        }
        catch(const Exception &excp) { excp.show(std::cerr); }
        catch(...) { throw; }

        try
        {
            std::cerr << "f=" << ASCII::Convert::To<float>(argv[i],"f") << std::endl;
        }
        catch(const Exception &excp) { excp.show(std::cerr); }
        catch(...) { throw; }

        try
        {
            std::cerr << "d=" << ASCII::Convert::To<double>(argv[i],"d") << std::endl;
        }
        catch(const Exception &excp) { excp.show(std::cerr); }
        catch(...) { throw; }

        try
        {
            std::cerr << "L=" << ASCII::Convert::To<long double>(argv[i],"L") << std::endl;
        }
        catch(const Exception &excp) { excp.show(std::cerr); }
        catch(...) { throw; }

    }
}
Y_UDONE()

