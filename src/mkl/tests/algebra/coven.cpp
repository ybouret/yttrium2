

#include "y/mkl/algebra/ortho-space.hpp"
#include "y/mkl/algebra/rank.hpp"
#include "y/utest/run.hpp"
#include "y/random/mt19937.hpp"
#include "y/coven/analysis.hpp"
#include "y/string/env.hpp"
#include "y/container/ordered/data-book.hpp"
#include "y/container/algorithm/for-each.hpp"

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

        Coven::Survey comb;
        const Matrix<int> NuT(TransposeOf,Nu);
        {
            Coven::Analysis::Run(xml,NuT,KeepComb,comb,Coven::Analysis::RejectRoot,optimize);
        }

        const size_t  N = Nu.rows;
        const size_t  M = Nu.cols;
        CxxArray<apz> stoi(M);
       // DataPool      dpool;

        for(const Coven::QVector *v=comb->head;v;v=v->next)
        {
            const Coven::QVector &coef = *v;
            //DataBook              inp(dpool);
            Algo::ForEach(stoi, & apz::ldz );
            for(size_t i=1;i<=N;++i)
            {
                const apz &           cf = coef[i]; if(__Zero__==cf.s) continue;
                const Readable<int> & nu = Nu[i];
                for(size_t j=M;j>0;--j)
                {
                    const int n = nu[j];
                    if(!n) continue;
                    //inp |= j;
                    stoi[j] += n * cf;
                }
            }
            //DataBook out(dpool);
            //for(size_t j=M;j>0;--j) if( stoi[j].s != __Zero__ ) out += j;
            //const bool     effective = out->size() < inp->size();
           // const DataBook missing = inp-out;
            const bool effective = true;
            Y_XMLog(xml, (effective ? "[+]" : "[-]") << " stoi=" << stoi);// << "  #" << inp << "->" << out << " : missing=" << missing << " @" << coef);
            //if( !inp.includes(out) ) throw Exception("new indices in output!!");
        }

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


