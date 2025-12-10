#include "y/system/program.hpp"
#include "y/color/rgb.hpp"


#include "y/stream/libc/input.hpp"
#include "y/stream/libc/output.hpp"

#include "y/string.hpp"
#include "y/string/tokenizer.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/container/algorithm/crop.hpp"
#include "y/exception.hpp"
#include "y/container/associative/hash/map.hpp"
#include <cctype>

using namespace Yttrium;


static inline bool isBad(const char C)
{
    switch(C)
    {
        case ' ':
        case '\t':
        case '_':
            return true;

        default:
            break;
    }
    return false;
}

static inline
String MakeName(String &name)
{
    Algo::Crop(name,isBad);
    const size_t n = name.size();
    if(name.size()<=0) throw Exception("empty name");
    String res = toupper(name[1]);
    for(size_t i=2;i<n;++i)
    {
        const char c = name[i];
        if(c!='_')
            res += name[i];
        else
        {
            res += toupper(name[++i]);
        }
    }
    res += name[n];


    return res;
}

#include "y/ascii/convert.hpp"
#include "y/core/utils.hpp"

typedef Color::RGB<uint8_t> rgb;

static inline uint8_t GetField(const char * const uuid,
                               String &           data)
{
    Algo::Crop(data,isspace);
    return ASCII::Convert::To<uint8_t>(data,uuid);
}

Y_PROGRAM()
{
    static const char * field[4] = { 0, "red", "blue", "green" };

    if(argc<=1) {
        std::cerr << "usage : " << program << " x11.txt" << std::endl;
        return 1;
    }
    typedef HashMap<String,rgb>  CMap;
    CMap   cmap;
    size_t nmax = 0;
    {
        InputFile in(argv[1]);
        String         line;
        Vector<String> words;
        while(in.gets(line))
        {
            words.free();
            Tokenizer::AppendTo(words,line," \t",2);
            if(words.size()<=4) continue;
            std::cerr << words << std::endl;
            const String name = MakeName(words[1]);
            std::cerr << "name='" << name << "'" << std::endl;
            if(cmap.search(name)) continue;
            words.popHead();
            rgb c;
            for(size_t i=1;i<=3;++i)
                c[i] = GetField(field[i],words[i]);
            std::cerr << "c=" << c << std::endl;
            if(!cmap.insert(name,c)) throw Exception("couldn't insert '%s'", name.c_str());
            InSituMax(nmax,name.size());
        }
        cmap.sortKeysWith(String::Compare);
    }

    std::cerr << "#color = " << cmap.size() << std::endl;

    {
        OutputFile fp("defs.hxx");
        for(CMap::Iterator it=cmap.begin();it!=cmap.end();++it)
        {
            const String &name  = it->key;
            const rgb    &color = *it;
            fp << "#define Y_" << name;
            for(size_t i=name.size();i<nmax;++i) fp << ' ';
            fp << " (Yttrium::Color::RGBA<uint8_t>(";
            fp("0x%02x,0x%02x,0x%02x",color.r,color.g,color.b);
            fp << "))\n";
        }
    }

    {
        OutputFile fp("incl.hxx");
        size_t k=1;
        for(CMap::Iterator it=cmap.begin();it!=cmap.end();++it,++k)
        {
            const String &name  = it->key;
            const rgb    &color = *it;
            fp << "  { \"" << name;
            fp << "\"";
            for(size_t i=name.size();i<nmax;++i) fp << ' ';
            for(size_t i=1;i<=3;++i)
                fp(", %3d", (int) color[i]);
            fp << "}";
            if(k<cmap.size()) fp << ',';
            fp << "\n";
        }
    }

}
Y_EXECUTE()
