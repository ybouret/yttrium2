#include "y/system/program.hpp"
#include "y/color/rgb.hpp"


#include "y/stream/libc/input.hpp"
#include "y/string.hpp"
#include "y/string/tokenizer.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/container/algorithm/crop.hpp"
#include "y/exception.hpp"
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
    for(size_t i=2;i<=n;++i)
    {
        res += name[i];
    }


    return res;
}

Y_PROGRAM()
{
    //static const char * field[4] = { 0, "red", "blue", "green" };

    if(argc<=1) {
        std::cerr << "usage : " << program << " x11.txt" << std::endl;
        return 1;
    }


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
    }


}
Y_EXECUTE()
