
#include "y/container/matrix.hpp"
#include "y/utest/run.hpp"
#include "y/apex/rational.hpp"
#include "y/memory/stealth.hpp"

using namespace Yttrium;

Y_UTEST(container_matrix)
{

    {
        int arr[3] = { 1, 2, 3 };
        Matrix<int>::Row row( Memory::Stealth::Hide(arr),3);
        std::cerr << row << std::endl;
    }

    { Matrix<int> m; }

    {
        Matrix<int> m(2,3);

    }

    {
        Matrix<apq> m(5,6);
    }

    for(size_t nr=1;nr<=3;++nr)
    {
        for(size_t nc=1;nc<=3;++nc)
        {
            Matrix<int> m(nr,nc);
            std::cerr << "m" << nr << "x" << nc << " = " <<  m << std::endl;
        }
    }



}
Y_UDONE()
