

#include "y/mkl/algebra/ortho-space.hpp"
#include "y/mkl/algebra/rank.hpp"
#include "y/utest/run.hpp"
#include "y/random/mt19937.hpp"
#include "y/coven/analysis.hpp"

using namespace Yttrium;

namespace
{
    struct KeepLaws
    {

        inline size_t Get(XMLog &xml, const Coven::Survey &survey)
        {
            Y_XML_Section(xml, "KeepLaws");
            for(const Coven::QVector *v=survey->head;v;v=v->next)
            {
                Y_XMLog(xml,*v);
            }
            return 0;
        }
    };
}

Y_UTEST(algebra_coven)
{
    Random::MT19937 ran;
    bool            verbose = true;
    XMLog           xml(std::cerr,verbose);

    KeepLaws        keepLaws;
    Coven::Analyzer findLaws( &keepLaws, & KeepLaws::Get);

    {
        // H20, AH : H HO AH Am
        Matrix<int> Nu(2,4);
        Nu[1][1] = 1; Nu[1][2] = 1;
        Nu[2][1] = 1; Nu[2][3] = -1; Nu[2][4] = 1;

        std::cerr << "Nu=" << Nu << std::endl;

        Matrix<apz> Q = MKL::OrthoSpace::Of(Nu);
        std::cerr << "Q=" << Q << std::endl;

        Coven::Analysis(xml,Q,findLaws,false);
        
    }



}
Y_UDONE()


