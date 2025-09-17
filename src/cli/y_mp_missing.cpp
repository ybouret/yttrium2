

#include "y/stream/proc/input.hpp"
#include "y/system/program.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/string/tokenizer.hpp"
#include "y/container/algorithm/crop.hpp"
#include "y/container/associative/suffix/set.hpp"
#include <cstring>
#include <cctype>

using namespace Yttrium;

typedef Vector<String>           Strings;
typedef SuffixSet<String,String> PDB;

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


    static void QueryDeps(PDB          &pdb,
                          const String &root,
                          const String &data)
    {

        //std::cerr << "\t[+] '" << data << "'" << std::endl;
        const char * const origin = strchr(data(),':'); if(!origin) return;
        const String       source(origin+1);
        Strings            target;
        Tokenizer::AppendTo(target,source,',');
        for(size_t i=1;i<=target.size();++i)
        {
            const String &dep   = Algo::Crop(target[i], isblank);
            if(pdb.search(dep))  continue;
            if(!pdb.insert(dep)) throw Specific::Exception("QueryDeps","couldn't insert '%s'", dep.c_str());
            if(IsInstalled(dep)) continue;
            const String  child = root + '.' + dep;
            std::cerr <<  child << std::endl;
            ScanDeps(pdb,child,dep);
        }
    }

    static void ScanDeps(PDB            &pdb,
                         const String   &root,
                         const String   &port)
    {
        Strings strings;
        {
            const String cmd = "port deps " + port;
            InputProcess::AppendTo(strings,cmd);
        }
        strings.popHead();
        for(size_t i=1;i<=strings.size();++i)
            QueryDeps(pdb,root,strings[i]);
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

    String         root = port;
    PDB            pdb;
    Port::ScanDeps(pdb,root,port);


}
Y_EXECUTE()
