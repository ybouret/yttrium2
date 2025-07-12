
#include "y/container/matrix.hpp"
#include "y/utest/run.hpp"
#include "y/apex/rational.hpp"
#include "y/memory/stealth.hpp"
#include "y/random/park-miller.hpp"
#include "y/container/sequence/vector.hpp"

using namespace Yttrium;

namespace
{
    

}

Y_UTEST(container_matrix)
{

    Random::ParkMiller ran;

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
            for(size_t i=1;i<=nr;++i)
            {
                for(size_t j=1;j<=nc;++j)
                {
                    m[i][j] = ran.in<int>(-5,5);
                }
            }
            std::cerr << "m0_" << nr << "x" << nc << " = " <<  m << std::endl;
            {
                Matrix<int> m1(m);
                std::cerr << "m1_" << nr << "x" << nc << " = " <<  m1 << std::endl;
            }

            {
                Matrix<apq> m2(CopyOf,m);
                std::cerr << "m2_" << nr << "x" << nc << " = " <<  m2 << std::endl;
            }

            {
                Matrix<apz> m2t(TransposeOf,m);
                std::cerr << "m2t_" << nr << "x" << nc << " = " <<  m2t << std::endl;

            }

            {
                Matrix<int> m3;
                m3 = m;
                std::cerr << "m3_" << nr << "x" << nc << " = " <<  m3 << std::endl;
            }

            {
                Matrix<apz> m4;
                m4 = m;
                std::cerr << "m4_" << nr << "x" << nc << " = " <<  m4 << std::endl;
            }


        }
    }









}
Y_UDONE()
