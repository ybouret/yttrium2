

#include "y/jive/regexp.hpp"
#include "y/utest/run.hpp"
#include "y/stream/libc/output.hpp"
#include "y/stream/libc/input.hpp"

using namespace Yttrium;
using namespace Jive;

Y_UTEST(rx)
{
    if(argc>1)
    {

        std::cerr << "compiling '" << argv[1] << "'" << std::endl;
        const Motif motif = RegExp::Compile(argv[1],0);

        {
            const String dotName = "rx.dot";
            Vizible::Render(dotName,*motif);
        }

        {
            OutputFile fp("rx.bin");
            (void)motif->serialize(fp);
        }

        if(argc>2)
        {
            InputFile fp(argv[2]);
            String line;
            while(fp.gets(line))
            {
                Source source( Module::OpenData(line,line) );
                Token  token;
                std::cerr << "source='" << line << "' ";
                if( motif->accepts(token,source) )
                {
                    std::cerr << "[+] '" << token << "'";
                }
                else
                {
                    std::cerr << "[-]";
                }
                std::cerr << std::endl;

            }
        }

    }
}
Y_UDONE()
