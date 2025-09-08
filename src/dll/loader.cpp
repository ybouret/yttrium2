#include "y/system/program.hpp"
#include "y/rtld/dll.hpp"
#include "y/core/display.hpp"

using namespace Yttrium;

typedef double (*Proc)(double);

Y_PROGRAM()
{
    if(argc>1)
    {
        const DLL    dll = argv[1];
        Proc   const sine = dll.load<Proc>("Sine");
        if(sine)
        {
            for(unsigned i=0;i<8;++i)
            {
                std::cerr << i << " => " << sine( (double)i ) << std::endl;
            }
        }
        else
        {
            std::cerr << "Sine not found..." << std::endl;
        }

        uint32_t * const data = dll.load<uint32_t *>("Data");
        if( data )
        {
            Core::Display(std::cerr << "Data=", data, 4) << std::endl;
        }
        else
            std::cerr << "No Data..." << std::endl;

    }
}
Y_EXECUTE()

