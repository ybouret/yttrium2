#include "y/system/program.hpp"
#include "y/rtld/dll.hpp"

using namespace Yttrium;

typedef double (*Proc)(double);

Y_PROGRAM()
{
    if(argc>1)
    {
        const DLL dll = argv[1];
        Proc   const    sine = dll.load<Proc>("Sine");
        if(sine)
        {
            for(unsigned i=0;i<8;++i)
            {
                std::cerr << i << " => " << sine( (double)i ) << std::endl;
            }
        }
    }
}
Y_EXECUTE()

