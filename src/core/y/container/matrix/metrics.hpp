
//! \file

#ifndef Y_Matrix_Metrics_Included
#define Y_Matrix_Metrics_Included 1

#include "y/mkl/transpose-of.hpp"
#include "y/core/setup.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! common metrics elements for matrices
    //
    //
    //__________________________________________________________________________
    class MatrixMetrics
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        static const char * const CallSign;     //!< matrix
        static const char * const EmptyMatrix;  //!< "[]"
        static const char         LBRACK = '['; //!< alias
        static const char         RBRACK = ']'; //!< alias
        static const char         ROWSEP = ';'; //!< alias
        static const char * const L_HCAT;       //!< "hcat(";
        static const char * const R_HCAT;       //!< ")"
        
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        explicit MatrixMetrics(const size_t nr, const size_t nc);            //!< \param nr rows \param nc columns
        MatrixMetrics(const MatrixMetrics &) noexcept;                        //!< duplicate
        MatrixMetrics(const TransposeOf_ &, const MatrixMetrics &) noexcept; //!< duplicate transpoe
        virtual ~MatrixMetrics() noexcept;                                   //!< cleanup


        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        bool isSquare() const noexcept; //!< \return rows==cols
        bool sameMetricsThan(const MatrixMetrics &) const noexcept;
        
        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________
        const size_t rows;  //!< rows
        const size_t cols;  //!< columns
        const size_t count; //!< rows*cols

    private:
        Y_Disable_Assign(MatrixMetrics);  //!< discarding
    protected:
        void _xch( MatrixMetrics & ) noexcept; //!< exchange values
    };

}

#endif
