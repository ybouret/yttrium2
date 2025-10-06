

#include "y/stream/libc/input.hpp"
#include "y/stream/libc/output.hpp"

#include "y/system/program.hpp"
#include "y/ascii/embedding.hpp"
#include "y/ascii/printable.hpp"
#include "y/pointer/auto.hpp"

using namespace Yttrium;

Y_PROGRAM()
{
    if(false)
    {
        OutputFile fp("256.bin");
        for(int i=0;i<256;++i)
        {
            fp.write( (char)i );
        }
    }
    AutoPtr<InputStream>  input  = new InputFile(  argc > 1 ? argv[1] : Y_STDIN  );
    AutoPtr<OutputStream> output = new OutputFile( argc > 2 ? argv[2] : Y_STDOUT );

    const size_t width = 8;
    size_t w = 0;
    char   c = 0;
    bool   nl = false;
    while(input->query(c))
    {
        (*output)("'%s'", ASCII::Printable::Text(c) );
        if(input->alive()) (*output) << ", ";
        if(++w>=width)
        {
            (*output) << '\n';
            nl = true;
            w = 0;
        }
        else
        {
            nl = false;
        }
    }
    if(!nl) (*output) << '\n';


}
Y_EXECUTE()
