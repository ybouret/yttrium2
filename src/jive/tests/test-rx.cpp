

#include "y/jive/regexp.hpp"
#include "y/utest/run.hpp"
#include "y/stream/libc/output.hpp"
#include "y/stream/libc/input.hpp"
#include "y/ascii/boolean.hpp"
#include "y/pointer/auto.hpp"

using namespace Yttrium;
using namespace Jive;

Y_UTEST(rx)
{
    {
        String root = "root";
        AutoPtr<Pattern> lhs = Pattern::Exact(root);
        const String     rx  = Pattern::ToRegExp(root);
        std::cerr << root << "->" << rx << std::endl;
        AutoPtr<Pattern> rhs = RegExp::Compile(rx);
        Vizible::Render("lhs.dot",*lhs);
        Vizible::Render("rhs.dot",*rhs);
        Y_ASSERT(lhs->toBinary() == rhs->toBinary());
    }

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


        const FirstChars fc = motif->firstChars();
        std::cerr << "fc       : " << fc << std::endl;
        std::cerr << "strong   : " << ASCII::Boolean::Text( motif->strong() ) << std::endl;
        std::cerr << "univocal : " << ASCII::Boolean::Text( motif->univocal() ) << std::endl;




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
