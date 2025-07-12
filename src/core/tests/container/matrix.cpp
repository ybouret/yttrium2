
#include "y/container/matrix.hpp"
#include "y/utest/run.hpp"
#include "y/apex/rational.hpp"
#include "y/memory/stealth.hpp"
#include "y/random/park-miller.hpp"
#include "y/container/sequence/vector.hpp"

using namespace Yttrium;

namespace
{
    class Pair
    {
    public:
        Pair(const size_t first, const size_t second) noexcept :
        i(first),
        j(second)
        {
            assert(i!=j);
            if(i>j) CoerceSwap(i,j);
            assert(i<j);
        }

        Pair(const Pair &p) noexcept : i(p.i), j(p.j) { assert(i<j); }

        ~Pair() noexcept {}

        inline friend std::ostream & operator<< (std::ostream &os, const Pair &p)
        {
            os << "(" << p.i << "," << p.j << ")";
            return os;
        }

        inline SignType Compare(const Pair &lhs, const Pair &rhs) noexcept
        {
            switch( Sign::Of(lhs.i, rhs.i) )
            {
                case __Zero__: break;
                case Negative: return Negative;
                case Positive: return Positive;
            }
            return Sign::Of(lhs.j,rhs.j);
        }

        inline friend bool operator==(const Pair &lhs, const Pair &rhs) noexcept
        {
            return lhs.i == rhs.i && lhs.j == rhs.j;
        }


        const size_t i;
        const size_t j;
    private:
        Y_Disable_Assign(Pair);
    };

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





    for(size_t nr=1;nr<=4;++nr)
    {
        for(size_t nc=1;nc<=4;++nc)
        {
            if(nr==nc) continue;
            std::cerr << nr << " x " << nc << std::endl;
            Vector<Pair> pairs;
            for(size_t i=1;i<=nr;++i)
            {
                for(size_t j=1;j<=nc;++j)
                {
                    if(i!=j)
                    {
                        const Pair p(i,j);
                        std::cerr << "\tswp " << p << std::endl;
                        bool found = false;
                        for(size_t i=1;i<=pairs.size();++i)
                        {
                            if( pairs[i] == p)
                            {
                                found = true;
                                break;
                            }
                        }
                        if(!found) pairs << p;
                    }
                }
            }
            std::cerr << "pairs=" << pairs << std::endl;

        }
    }



}
Y_UDONE()
