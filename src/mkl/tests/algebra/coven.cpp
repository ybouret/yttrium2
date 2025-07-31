

#include "y/mkl/algebra/ortho-space.hpp"
#include "y/mkl/algebra/rank.hpp"
#include "y/utest/run.hpp"
#include "y/random/mt19937.hpp"
#include "y/coven/analysis.hpp"
#include "y/string/env.hpp"

using namespace Yttrium;

namespace
{
    struct KeepLaws
    {

        inline size_t Get(XMLog &xml, Coven::Survey &survey)
        {
            Y_XML_Section(xml, "KeepLaws");
            for(const Coven::QVector *v=survey->head;v;v=v->next)
            {
                if(v->npos>=2 && v->nneg<=0)
                {
                    Y_XMLog(xml, "[+] " << *v);
                }
                else
                {
                    //Y_XMLog(xml, "[-] " << *v);
                }
            }
            return 0;
        }
    };

    static inline void analyze(XMLog &xml,
                                 const Matrix<int> &Nu,
                                 const bool optimize)
    {
        std::cerr << "Nu=" << Nu << std::endl;
        KeepLaws        keepLaws;
        Coven::Analyzer findLaws( &keepLaws, & KeepLaws::Get);
        Matrix<apz> Q = MKL::OrthoSpace::Of(Nu);
        std::cerr << "Q=" << Q << std::endl;
        Coven::Analysis(xml,Q,findLaws,optimize);
    }

}



Y_UTEST(algebra_coven)
{
    Random::MT19937 ran;
    bool            verbose = true;
    XMLog           xml(std::cerr,verbose);
    const bool      optimize = Environment::Flag("OPTIMIZE");
    KeepLaws        keepLaws;
    Coven::Analyzer findLaws( &keepLaws, & KeepLaws::Get);

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


