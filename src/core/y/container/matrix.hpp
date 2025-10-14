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
#include "y/memory/stealth.hpp"
#include "y/container/light-array.hpp"


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
        typedef LightArray<Type> ArrayType; //!< alias


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
            // Methods
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

        //! setup as minor
        /**
         \param minor helper
         \param ir in M rows
         \param ic in M cols
         \param M extract minor from
         */
        template <typename U>
        inline Matrix(const MinorOf_ &minor,
                      const size_t ir,
                      const size_t ic,
                      const Matrix<U> &M) :
        MatrixMetrics(minor,M),
        Releasable(),
        code( newCode() ),
        rowp( newRows() )
        {

            copyMinor(ir,ic,M);
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

        //! assign minor
        /**
         \param ir in M rows
         \param ic in M cols
         \param M extract minor from
         \return *this
         */
        template <typename U> inline
        Matrix & assign(const MinorOf_ &, const size_t ir, const size_t ic, const Matrix<U> &M)
        {
            assert(1+rows==M.rows);
            assert(1+cols==M.cols);
            copyMinor(ir,ic,M);
            return *this;
        }

        //! \return first item of linear space
        inline ConstType * operator()(void) const noexcept
        {
            return code.isValid() ? code->entry : 0;
        }

        //! \return first item of linear space
        inline  Type * operator()(void)  noexcept
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

        //! swap rows \param lhs first row index \param rhs second row index
        inline void swapRows(const size_t lhs, const size_t rhs) noexcept
        {
            assert(lhs>0);
            assert(lhs<=rows);
            assert(rhs>0);
            assert(rhs<=rows);
            Memory::Stealth::Swap(& rowp->cxx[lhs][1], & rowp->cxx[rhs][1], sizeof(T) * cols);
        }

        //! swap cols \param lhs first col index \param rhs second col index
        inline void swapCols(const size_t lhs, const size_t rhs) noexcept
        {
            assert(lhs>0);
            assert(lhs<=cols);
            assert(rhs>0);
            assert(rhs<=cols);
            for(size_t i=rows;i>0;--i)
            {
                Row &r = rowp->cxx[i];
                Memory::Stealth::Swap(r[lhs],r[rhs]);
            }
        }



        //! \param nr required rows \param nc required cols \return same/new matrix
        inline Matrix & make(const size_t nr, const size_t nc)
        {
            if(nr!=rows||nc!=cols)
            {
                Matrix tmp(nr,nc);
                return xch(tmp);
            }
            else
                return *this;
        }

        //! \param arg set all items to arg \return *this
        Matrix & ld(ParamType arg)
        {
            size_t n = items;
            if(n>0)
            {
                MutableType *p = code->entry;
                while(n-- > 0) *(p++) = arg;
            }
            return *this;
        }

        //! \param arg multiply all items by arg \return *this
        inline Matrix & operator*=(ParamType arg)
        {
            size_t n = items;
            if(n>0)
            {
                MutableType *p = code->entry;
                while(n-- > 0) *(p++) *= arg;
            }
            return *this;
        }

        //! \param arg divide all items by arg \return *this
        inline Matrix & operator/=(ParamType arg)
        {
            size_t n = items;
            if(n>0)
            {
                MutableType *p = code->entry;
                while(n-- > 0) *(p++) /= arg;
            }
            return *this;
        }

        //! \return linear array
        inline ArrayType asArray() noexcept {
            Matrix &self = *this;
            return LightArray<Type>(self(),items);
        }

        //! \param  diag on diagonal \param extra out of diagonal \return *this
        inline Matrix & diagonal(ParamType diag, ParamType extra)
        {
            Matrix &self = *this;
            for(size_t i=rows;i>0;--i)
            {
                Row &r = self[i];
                r[i]   = diag;
                for(size_t j=cols;j>i;--j) r[j] = extra;
                for(size_t j=i-1;j>0;--j)  r[j] = extra;
            }
            return self;
        }



    private:

        //! Julia stype output \param os output stream \return os
        inline std::ostream & juliaPrint(std::ostream &os) const
        {
            if(items<=0) return os << EmptyMatrix;
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
            Memory::SchoolOf<T>(metrics.items),
            Memory::Operating<T>(entry,metrics.items)
            {
            }

            //! duplicate \param m another matrix
            template <typename U>
            inline Code(const Matrix<U> &m) :
            Object(),
            Memory::SchoolOf<T>(m.items),
            Memory::Operating<T>(entry,m(),m.items)
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
            return metrics.items > 0 ? new Code(metrics) : 0;
        }

        //! \param M source matrix \return new code from copied matrix
        template <typename U>
        inline Code * newCode(const Matrix<U> &M)
        {
            assert( gotSameMetricsThan(M) );
            return M.items >0 ? new Code(M) : 0;
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

        //! copy minor into
        /**
         \param ir in M rows
         \param ic in M cols
         \param M extract minor from
         */
        template <typename U> inline
        void copyMinor(const size_t ir, const size_t ic, const Matrix<U> &M)
        {
            assert(ir>0); assert(ir<=M.rows);
            assert(ic>0); assert(ic<=M.cols);
            Matrix &self = *this;
            size_t r=0;
            for(size_t i=1;i<=M.rows;++i)
            {
                if(ir==i) continue;
                ++r;
                size_t c=0;
                for(size_t j=1;j<=M.cols;++j)
                {
                    if(ic==j) continue;
                    self[r][++c] = M[i][j];
                }
             }
        }


    };

}

#endif

