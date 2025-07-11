//! \file

#ifndef Y_Matrix_Included
#define Y_Matrix_Included 1

#include "y/container/matrix/metrics.hpp"
#include "y/object.hpp"
#include "y/object/school-of.hpp"
#include "y/memory/operating.hpp"
#include "y/pointer/auto.hpp"
#include "y/container/contiguous.hpp"
#include "y/type/copy-of.hpp"
#include "y/mkl/transpose-of.hpp"

namespace Yttrium
{


    //! helper to build rows
#define Y_Matrix_Rows() rowp( new Rows( getMetrics(), *code  ) )

    //! helper to initialize code and rows
#define Y_Matrix()                       \
code( new Code( getMetrics() ) ),        \
Y_Matrix_Rows()

    //__________________________________________________________________________
    //
    //
    //
    //! generic matrix
    //
    //
    //__________________________________________________________________________
    template <typename T>
    class Matrix : public MatrixMetrics
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        Y_Args_Declare(T,Type); //!< aliases


        //______________________________________________________________________
        //
        //
        //! Single row
        //
        //______________________________________________________________________
        class Row : public Contiguous< Writable<T> >
        {
        public:
            //__________________________________________________________________
            //
            // Definitions
            //__________________________________________________________________
            Y_Args_Expose(T,Type); //!< aliases

            //__________________________________________________________________
            //
            // C++
            //__________________________________________________________________

            //! setup \param p first iterm \param c columns
            inline explicit Row(T * const p, const size_t c) noexcept :
            Contiguous< Writable<T> >(), cols(c), addr( ((MutableType *)p)-1 )
            {
                assert(cols>0);
                assert(0!=addr);
            }

            //! cleanup
            inline virtual ~Row() noexcept {}

            //__________________________________________________________________
            //
            // Interface
            //__________________________________________________________________

            //! [Writable] \return columns
            inline virtual size_t size() const noexcept { return cols; }

            //__________________________________________________________________
            //
            // Interface
            //__________________________________________________________________

            //! display in Julia style \param os output stream \return os
            inline std::ostream & juliaPrint(std::ostream &os) const
            {
                assert(cols>0);
                os << addr[1];
                for(size_t j=2;j<=cols;++j) os << ' ' << addr[j];
                return os;
            }

            //__________________________________________________________________
            //
            // Members
            //__________________________________________________________________
            const size_t cols; //!< columns for this row

        private:
            Y_Disable_Copy_And_Assign(Row); //!< discarding
            MutableType * const addr;       //!< addr[1..cols]

            //! [Writable] \param icol column index \return addr[indx]
            inline virtual ConstType & getItemAt(const size_t icol) const noexcept {
                assert(icol>0);
                assert(icol<=cols);
                return addr[icol];
            }
        };


        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup empty
        inline Matrix() : MatrixMetrics(0,0), Y_Matrix() {}

        //! setup default \param nr rows \param nc cols
        inline Matrix(const size_t nr, const size_t nc) :
        MatrixMetrics(nr,nc), Y_Matrix() {}

        //! duplicate \param M another matrix
        inline Matrix(const Matrix &M) :
        MatrixMetrics(M), code( new Code( M ) ), Y_Matrix_Rows()
        {

        }

        //! duplicate \param M another compatible matrix
        template <typename U>
        inline Matrix(const CopyOf_ &, const Matrix<U> &M) :
        MatrixMetrics(M), code( new Code( M ) ), Y_Matrix_Rows()
        {

        }

        //! cleanup
        inline virtual ~Matrix() noexcept {}

        //! display \param os output stream \param self *this \return os
        inline friend std::ostream & operator<<(std::ostream &os, const Matrix &self)
        {
            return self.juliaPrint(os);
        }

        inline Matrix & operator=( const Matrix &M )
        {
            return assign(M);
        }

        template <typename U> inline
        Matrix & operator=(const Matrix<U> &M)
        {
            return assign(M);
        }


        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! no-throw exchange \param other another matrix \return *this;
        inline Matrix & xch( Matrix &other ) noexcept
        {
            _xch(other);          // metrics
            code.xch(other.code); // code
            rowp.xch(other.rowp); // rows
            return *this;
        }

        template <typename U> inline
        Matrix & assign(const Matrix<U> &other)
        {
            Matrix temp(CopyOf,other);
            return xch(temp);
        }


        //! \return first item of linear space
        inline ConstType * operator()(void) const noexcept
        {
            return code->entry;
        }


        //! \param irow row index \return irow-th row
        inline Row & operator[](const size_t irow) noexcept
        {
            assert(irow>0);
            assert(irow<=rows);
            return rowp->cxx[irow];
        }

        //! \param irow row index \return irow-th row
        inline const Row & operator[](const size_t irow) const noexcept
        {
            assert(irow>0);
            assert(irow<=rows);
            return rowp->cxx[irow];
        }

    private:

        //! Julia stype output \param os output stream \return os
        inline std::ostream & juliaPrint(std::ostream &os) const
        {
            if(count<=0) return os << EmptyMatrix;
            assert(rows>0);
            assert(cols>0);
            const bool        hcat = rows<=1 || cols<=1;
            const Row * const row  = rowp->cxx;
            if(hcat) os << L_HCAT;
            os << LBRACK;
            row[1].juliaPrint(os);
            for(size_t i=2;i<=rows;++i) row[i].juliaPrint(os << ROWSEP);
            os << RBRACK;
            if(hcat) os << R_HCAT;
            return os;
        }

        //______________________________________________________________________
        //
        //
        //! hold constructed objects
        //
        //______________________________________________________________________
        class Code : public Object, public Memory::SchoolOf<T>, public Memory::Operating<T>
        {
        public:
            using Memory::SchoolOf<T>::entry;


            //! setup \param metrics matrix metrics
            inline Code(const MatrixMetrics &metrics) :
            Object(),
            Memory::SchoolOf<T>(metrics.count),
            Memory::Operating<T>(entry,metrics.count)
            {
            }

            //! duplicate \param m another matrix
            template <typename U>
            inline Code(const Matrix<U> &m) :
            Object(),
            Memory::SchoolOf<T>(m.count),
            Memory::Operating<T>(entry,m(),m.count)
            {
            }


            //! cleanup
            inline virtual ~Code() noexcept { }

        private:
            Y_Disable_Copy_And_Assign(Code); //!< discarding
        };

        //______________________________________________________________________
        //
        //
        //! hold rows
        //
        //______________________________________________________________________
        class Rows : public Object, public Memory::SchoolOf<Row>
        {
        public:
            using Memory::SchoolOf<Row>::entry;

            //! setup \param metrics metrics \param objects associated code
            inline Rows(const MatrixMetrics & metrics,
                        Code &                objects) :
            Memory::SchoolOf<Row>(metrics.rows)
            {
                Row *        row  = entry;
                T   *        addr = objects.entry;
                const size_t nr   = metrics.rows;
                const size_t nc   = metrics.cols;
                for(size_t i=0;i<nr;++i, addr += nc)
                    new ( row++ ) Row(addr,nc);
            }

            //! cleanup
            inline virtual ~Rows() noexcept {}

        private:
            Y_Disable_Copy_And_Assign(Rows); //!< discarding
        };


        AutoPtr<Code> code; //!< current code
        AutoPtr<Rows> rowp; //!< current rows on code

        //! \return return *this as metrics
        inline MatrixMetrics getMetrics() const noexcept { return *this; }

    };

}

#endif

