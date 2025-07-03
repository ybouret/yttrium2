
#include "y/stream/libc/input.hpp"
#include "y/system/program.hpp"
#include "y/string.hpp"

using namespace Yttrium;

Y_PROGRAM()
{
    size_t nmin = 0;
    size_t nmax = nmin;

    switch(argc-1)
    {
        case 1: nmin = nmax = atol(argv[1]); break;
        case 2: nmin = atol(argv[1]); nmax = atol(argv[2]); break;
        default:
            std::cerr << "usage: " << program << " nmax | nmin nmax" << std::endl;
            return 1;
    }

    InputFile fp(StdIn);
    String    line;
    while( fp.gets(line) )
    {
        const size_t n = line.size();
        if(n>=nmin&&n<=nmax) std::cout << line << std::endl;
    }

}
Y_EXECUTE()
