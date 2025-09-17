

#include "y/stream/proc/input.hpp"
#include "y/system/program.hpp"
#include "y/container/sequence/vector.hpp"

using namespace Yttrium;


struct Port
{

    static inline bool IsInstalled(const String &port)
    {
        Vector<String> strings;
        {
            const String cmd = "port installed " + port;
            InputProcess::AppendTo(strings,cmd);
        }
        //std::cerr << strings << std::endl;
        return strings.size() > 1;
    }
};


Y_PROGRAM()
{
    if(argc<=1) return 0;

    String port = argv[1];
    for(int i=2;i<argc;++i) port << ' ' << argv[i];
    if( Port::IsInstalled(port) )
    {
        std::cerr << port << " is already installed!" << std::endl;
        return 0;
    }


}
Y_EXECUTE()
