

#include "y/stream/proc/input.hpp"
#include "y/system/program.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/string/tokenizer.hpp"
#include "y/container/algorithm/crop.hpp"
#include <cstring>
#include <cctype>

using namespace Yttrium;

typedef Vector<String> Strings;

struct Port
{

    static inline bool IsInstalled(const String &port)
    {
        Strings strings;
        {
            const String cmd = "port installed " + port;
            InputProcess::AppendTo(strings,cmd);
        }
        return strings.size() > 1;
    }


    static void QueryDeps(const String &root,
                          const String &data)
    {

        //std::cerr << "\t[+] '" << data << "'" << std::endl;
        const char * const init = strchr(data(),':'); if(!init) return;
        const String       list(init+1);
        Strings            dsub;
        Tokenizer::AppendTo(dsub,list,',');
        for(size_t i=1;i<=dsub.size();++i)
        {
            const String &dep = Algo::Crop(dsub[i], isblank);
            if(IsInstalled(dep)) continue;
            std::cerr << "[+] '" << dep << "'" << std::endl;
        }
    }

    static void ScanDeps(const String   &root,
                         const String   &port)
    {
        Strings strings;
        {
            const String cmd = "port deps " + port;
            InputProcess::AppendTo(strings,cmd);
        }
        strings.popHead();
        for(size_t i=1;i<=strings.size();++i)
        {
            QueryDeps(root,strings[i]);
        }

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

    String         root;
    Port::ScanDeps(root,port);


}
Y_EXECUTE()
