

#include "y/information/bwt/transformer.hpp"
#include "y/information/stream/move-to-front.hpp"

#include "y/stream/libc/input.hpp"
#include "y/stream/libc/output.hpp"

#include "y/utest/run.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/information/entropy.hpp"

using namespace Yttrium;

Y_UTEST(info_bwt_mtf)
{

    Information::BWT_Transformer      bwt;
    Information::MoveToFront::Encoder mtf;
    Vector<char>                      source;
    Information::Entropy              S;

    if( argc > 1 )
    {
        S.ldz();
        {
            InputFile fp(argv[1]);
            char c = 0;
            while( fp.query(c) )
            {
                source << c;
                S << c;
            }
        }

        std::cerr << "source entropy=" << S() << std::endl;

        const size_t length = source.size();
        Vector<char> target(length,0);
        const size_t primary = bwt.encode( target(), source(), length);
        std::cerr << "primary=" << primary << "/" << length << std::endl;

        S.ldz();
        S.frame(target(),length);
        std::cerr << "target entropy=" << S() << std::endl;


        {
            OutputFile fp("bwt-mtf.dat");
            mtf.restart();
            mtf.transform(target(),target(),length);
            fp.frame(target(),length);
        }
        S.ldz();
        S.frame(target(),length);
        std::cerr << "final  entropy=" << S() << std::endl;
        
    }
}
Y_UDONE()

