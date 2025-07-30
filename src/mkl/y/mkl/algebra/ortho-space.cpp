


#include "y/mkl/algebra/ortho-space.hpp"
#include "y/mkl/algebra/lu.hpp"
#include "y/mkl/tao/3.hpp"
#include "y/system/exception.hpp"

namespace Yttrium
{
    namespace MKL
    {
        Matrix<apz> OrthoSpace:: Compute(const Matrix<apz> &P)
        {
            static const char    fn[] = "OrthoSpace";
            const size_t         cols = P.cols; if(cols<=0)   throw Specific::Exception(fn,"empty space");
            const size_t         rows = P.rows; 
            Matrix<apz>          P2(rows,rows);
            Cameo::Addition<apz> xadd;
            Tao::Gram(xadd,P2,P);

            apz         dP2;
            Matrix<apz> aP2(rows,rows);
            {
                LU<apq> lu(rows);
                dP2 = lu.determinant(P2); if(__Zero__==dP2.s) throw Specific::Exception(fn,"singular space");
                lu.adjoint(aP2,P2);
            }


            Matrix<apz> Q(cols,cols);
            {
                Matrix<apz> aP3(rows,cols);
                Tao::MMul(xadd,aP3,aP2,P);
                Matrix<apz> tP(TransposeOf,P);
                Tao::MMul(xadd,Q,tP,aP3);
            }

            for(size_t i=cols;i>0;--i)
            {
                Writable<apz> &Q_i = Q[i];
                Q_i[i] = dP2 - Q_i[i];
                for(size_t j=i-1;j>0;--j)
                {
                    const apz q = -Q_i[j];
                    Q_i[j]  = Q[j][i] = q;
                }

            }
            return Q;
        }
    }

}


