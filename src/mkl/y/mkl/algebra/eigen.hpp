//! \file

#ifndef Y_MKL_Eigen_Included
#define Y_MKL_Eigen_Included 1

#include "y/container/matrix.hpp"

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


        };
    }
}


#endif // !Y_MKL_Eigen_Included

