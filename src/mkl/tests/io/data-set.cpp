
#include "y/mkl/io/data-set.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/container/sequence/list.hpp"
#include "y/stream/libc/input.hpp"

#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(io_data_set)
{
    Y_SIZEOF(MKL::DataColumn);

    Vector<double> X;
    List<float>    Y;
    Vector<int>    Z;

    {
        MKL::DataSet ds;
        ds.add(1,X);
        ds.add(3,Z);
        ds.add(2,Y);
        if(argc>1)
        {
            InputFile fp(argv[1]);
            ds.load(fp);
        }
    }

    std::cerr << "X=" << X << std::endl;
    std::cerr << "Y=" << Y << std::endl;
    std::cerr << "Z=" << Z << std::endl;


}
Y_UDONE()

