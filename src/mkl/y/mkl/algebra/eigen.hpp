//! \file

#ifndef Y_MKL_Eigen_Included
#define Y_MKL_Eigen_Included 1

#include "y/container/matrix.hpp"
#include "y/type/sign.hpp"

namespace Yttrium
{
    namespace MKL
    {
        //______________________________________________________________________
        //
        //
        //
        //! Eigen Methods
        //
        //
        //______________________________________________________________________
        struct Eigen
        {
            //__________________________________________________________________
            //
            //
            //! Balance
            //
            //__________________________________________________________________
            template <typename T>
            class Balance
            {
            public:
                explicit Balance();          //!< setup
                virtual ~Balance() noexcept; //!< cleanup

                void operator()(Matrix<T> &); //!< balance matrix

            private:
                class Code;
                Y_Disable_Copy_And_Assign(Balance); //!< discarding
                Code * const code;                  //!< inner algorithm
            };

            //__________________________________________________________________
            //
            //
            //! Reduction to Hessenberg Form
            //
            //__________________________________________________________________
            template <typename T>
            class Hessenberg
            {
            public:
                explicit Hessenberg();          //!< setup
                virtual ~Hessenberg() noexcept; //!< cleanup
                void operator()(Matrix<T> &);   //!< reduce maatirx

            private:
                class Code;
                Y_Disable_Copy_And_Assign(Hessenberg); //!< discarding
                Code * const code;                     //!< inner algorithm
            };


            template <typename T>
            class Jacobi
            {
            public:
                explicit Jacobi();
                virtual ~Jacobi() noexcept;

                bool operator()(Matrix<T> &v, Writable<T> &d, const Matrix<T> &a);

            private:
                class Code;
                Y_Disable_Copy_And_Assign(Jacobi);
                Code * const code;
            };
            
            template <typename T, typename PROC> static inline
            void Sort(Matrix<T> &v, Writable<T> &d, PROC &compare)
            {
                assert(v.isSquare());
                assert(d.size() == v.rows);
                const size_t n = v.rows;
                for(size_t i=1;i<n;++i)
                {
                    size_t k = i;
                    T      p = d[k];
                    for (size_t j=i+1;j<=n;j++)
                    {
                        switch( compare(p,d[j]) )
                        {
                            case Negative:  break;
                            case __Zero__:  break;
                            case Positive: p = d[k=j]; break;
                        }
                    }
                    if(k!=i)
                    {
                        d[k]=d[i];
                        d[i]=p;
                        v.swapCols(i,k);
                    }
                }
            }


        };
    }
}


#endif // !Y_MKL_Eigen_Included

