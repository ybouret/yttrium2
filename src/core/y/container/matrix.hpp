//! \file

#ifndef Y_Matrix_Included
#define Y_Matrix_Included 1

#include "y/container/matrix/metrics.hpp"
#include "y/object/school-of.hpp"
#include "y/memory/operating.hpp"
#include "y/pointer/auto.hpp"
#include "y/container/contiguous.hpp"
#include "y/type/copy-of.hpp"
#include "y/mkl/transpose-of.hpp"
#include "y/ability/releasable.hpp"

namespace Yttrium
{



    //__________________________________________________________________________
    //
    //
    //
    //! generic matrix
    //
    //
    //__________________________________________________________________________
    template <typename T>
    class Matrix : public MatrixMetrics, public Releasable
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
        inline Matrix() noexcept :
        MatrixMetrics(0,0),
        Releasable(),
        code(0),
        rowp(0)
        {}


        //! setup default \param nr rows \param nc cols
        inline Matrix(const size_t nr, const size_t nc) :
        MatrixMetrics(nr,nc),
        Releasable(),
        code( newCode() ),
        rowp( newRows() )
        {

        }

        //! duplicate \param M another matrix
        inline Matrix(const Matrix &M) :
        MatrixMetrics(M),
        Releasable(),
        code( newCode(M) ),
        rowp( newRows()  )
        {

        }

        //! duplicate \param M another compatible matrix
        template <typename U>
        inline Matrix(const CopyOf_ &, const Matrix<U> &M) :
        MatrixMetrics(M),
        Releasable(),
        code( newCode(M) ),
        rowp( newRows()  )
        {

        }

        //! duplicate \param transpose helper \param M another compatible matrix
        template <typename U>
        inline Matrix(const TransposeOf_ &transpose, const Matrix<U> &M) :
        MatrixMetrics(transpose,M),
        Releasable(),
        code( newCode()  ),
        rowp( newRows()  )
        {
            copyTranspose(M);
        }


        //! cleanup
        inline virtual ~Matrix() noexcept {}

        //! display \param os output stream \param self *this \return os
        inline friend std::ostream & operator<<(std::ostream &os, const Matrix &self)
        {
            return self.juliaPrint(os);
        }

        //! assign \param M another matrix \return *this
        inline Matrix & operator=( const Matrix &M )
        {
            return assign(M);
        }

        //! assign \param M another compatible matrix \return *this
        template <typename U> inline
        Matrix & operator=(const Matrix<U> &M)
        {
            return assign(M);
        }

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________

        inline virtual void release() noexcept { Matrix _; xch(_); }

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

        //! assign by copy/swap \param other compatible matrix \return *this
        template <typename U> inline
        Matrix & assign(const Matrix<U> &other)
        {
            Matrix temp(CopyOf,other);
            return xch(temp);
        }

        //! duplicate
        /**
         \param transpose helper
         \param M another compatible matrix
         \return *this
         */
        template <typename U> inline
        Matrix & assign(const TransposeOf_ &transpose, const Matrix<U> &M)
        {
            Matrix temp(transpose,M);
            return xch(temp);
        }

        //! \return first item of linear space
        inline ConstType * operator()(void) const noexcept
        {
            return code.isValid() ? code->entry : 0;
        }


        //! \param irow row index \return irow-th row
        inline Row & operator[](const size_t irow) noexcept
        {
            assert(irow>0);
            assert(irow<=rows);
            assert(rowp.isValid());
            return rowp->cxx[irow];
        }

        //! \param irow row index \return irow-th row
        inline const Row & operator[](const size_t irow) const noexcept
        {
            assert(irow>0);
            assert(irow<=rows);
            assert(rowp.isValid());
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

        //! \return new code according to metrics
        inline Code * newCode() {
            const MatrixMetrics & metrics = *this;
            return count > 0 ? new Code(metrics) : 0;
        }

        //! \param M source matrix \return new code from copied matrix
        template <typename U>
        inline Code * newCode(const Matrix<U> &M)
        {
            assert( gotSameMetricsThan(M) );
            return M.count >0 ? new Code(M) : 0;
        }


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
                        Code         &        objects) :
            Memory::SchoolOf<Row>(metrics.rows)
            {

                Row *        row  = entry;
                T   *        addr = objects.entry;
                const size_t nc   = metrics.cols;
                const size_t nr = metrics.rows;
                for(size_t i=0;i<nr;++i, addr += nc)
                    new ( row++ ) Row(addr,nc);

            }

            //! cleanup
            inline virtual ~Rows() noexcept {}

        private:
            Y_Disable_Copy_And_Assign(Rows); //!< discarding
        };


        //! \return rows for code
        inline Rows * newRows()
        {
            const MatrixMetrics & metrics = *this;
            return code.isValid() ? new Rows(metrics,*code) : 0 ;
        }


        AutoPtr<Code> code; //!< current code
        AutoPtr<Rows> rowp; //!< current rows on code

        //! copy the transpose matrix data \param M source matrix
        template <typename U> inline
        void copyTranspose(const Matrix<U> &M)
        {
            Matrix &self = *this;
            assert( transposeMetricsOf(M) );
            for(size_t i=rows;i>0;--i)
            {
                Matrix::Row &self_i = self[i];
                for(size_t j=cols;j>0;--j)
                {
                    self_i[j] = M[j][i];
                }
            }
        }


    };

}

#endif

