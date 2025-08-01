

#include "y/mkl/algebra/ortho-space.hpp"
#include "y/mkl/algebra/rank.hpp"
#include "y/utest/run.hpp"
#include "y/random/mt19937.hpp"
#include "y/coven/analysis.hpp"
#include "y/string/env.hpp"

using namespace Yttrium;

namespace
{

    static inline bool KeepLaw(const Coven::QVector &v)
    {
        return (v.npos>=2 && v.nneg<=0);
    }

    static inline bool KeepComb(const Coven::QVector &v)
    {
        return v.ncof >= 2;
    }



    static inline void analyze(XMLog &xml,
                               const Matrix<int> &Nu,
                               const bool optimize)
    {
        std::cerr << "Nu=" << Nu << std::endl;
        Coven::Survey laws;
        {
            Matrix<apz> Q = MKL::OrthoSpace::Of(Nu);
            std::cerr << "Q=" << Q << std::endl;
            Coven::Analysis::Run(xml,Q,KeepLaw,laws,Coven::Analysis::AcceptRoot,optimize);
        }

#if 1
        Coven::Survey comb;
        const Matrix<int> NuT(TransposeOf,Nu);
        {
            Coven::Analysis::Run(xml,NuT,KeepComb,comb,Coven::Analysis::RejectRoot,optimize);
        }

        
        for(const Coven::QVector *v=comb->head;v;v=v->next)
        {

        }

#endif
    }

}



Y_UTEST(algebra_coven)
{
    Random::MT19937 ran;
    bool            verbose = true;
    XMLog           xml(std::cerr,verbose);
    const bool      optimize = Environment::Flag("OPTIMIZE");

    {
        // H20, AH : H HO AH Am
        Matrix<int> Nu(2,4);
        Nu[1][1] = 1; Nu[1][2] = 1;
        Nu[2][1] = 1; Nu[2][3] = -1; Nu[2][4] = 1;
        analyze(xml,Nu,optimize);
    }

    {
        // H20, AH : H HO AH Am NH4 NH3
        Matrix<int> Nu(3,6);
        Nu[1][1] = 1; Nu[1][2] = 1;
        Nu[2][1] = 1; Nu[2][3] = -1; Nu[2][4] = 1;
        Nu[3][1] = 1; Nu[3][5] = -1; Nu[3][6] = 1;

        analyze(xml,Nu,optimize);
    }





}
Y_UDONE()


