//! \file

#ifndef Y_Matrix_Included
#define Y_Matrix_Included 1

#include "y/container/matrix/metrics.hpp"
#include "y/object.hpp"
#include "y/object/school-of.hpp"
#include "y/memory/operating.hpp"
#include "y/pointer/auto.hpp"
#include "y/container/contiguous.hpp"

namespace Yttrium
{


#define Y_Matrix()                       \
code( new Code( getMetrics() ) ),        \
_row( new Rows( getMetrics(), *code  ) )

    template <typename T>
    class Matrix : public MatrixMetrics
    {
    public:
        Y_Args_Declare(T,Type);

        class Row : public Contiguous< Writable<T> >
        {
        public:
            Y_Args_Expose(T,Type);
            inline explicit Row(T * const p, const size_t c) noexcept :
            Contiguous< Writable<T> >(),
            cols(c), addr( ((MutableType *)p)-1 )
            {
                assert(cols>0);
                assert(0!=addr);
            }


            inline virtual ~Row() noexcept {}

            inline virtual size_t size() const noexcept { return cols; }

            inline std::ostream & juliaPrint(std::ostream &os) const
            {
                assert(cols>0);
                os << addr[1];
                for(size_t j=2;j<=cols;++j) os << ' ' << addr[j];
                return os;
            }

            const size_t cols;
        private:
            Y_Disable_Copy_And_Assign(Row);
            MutableType * const addr;

            inline virtual ConstType & getItemAt(const size_t icol) const noexcept {
                assert(icol>0);
                assert(icol<=cols);
                return addr[icol];
            }
        };


        inline Matrix() : MatrixMetrics(0,0), Y_Matrix() {}

        inline Matrix(const size_t nr, const size_t nc) :
        MatrixMetrics(nr,nc), Y_Matrix() {}


        inline virtual ~Matrix() noexcept {}

        inline friend std::ostream & operator<<(std::ostream &os, const Matrix &self)
        {
            return self.juliaPrint(os);
        }

        inline Row & operator[](const size_t irow) noexcept
        {
            assert(irow>0);
            assert(irow<=rows);
            return _row->cxx[irow];
        }

        inline const Row & operator[](const size_t irow) const noexcept
        {
            assert(irow>0);
            assert(irow<=rows);
            return _row->cxx[irow];
        }

    private:
        Y_Disable_Copy_And_Assign(Matrix);

        inline std::ostream & juliaPrint(std::ostream &os) const
        {
            if(count<=0) return os << EmptyMatrix;
            assert(rows>0);
            assert(cols>0);
            const bool        hcat = rows<=1 || cols<=1;
            const Row * const row  = _row->cxx;
            if(hcat) os << "hcat(";
            os << '[';
            row[1].juliaPrint(os);
            for(size_t i=2;i<=rows;++i)
                row[i].juliaPrint(os << ';');
            os << ']';
            if(hcat) os << ")";
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

            inline virtual ~Rows() noexcept {}

        private:
            Y_Disable_Copy_And_Assign(Rows);
        };


        AutoPtr<Code> code;
        AutoPtr<Rows> _row;

        inline MatrixMetrics getMetrics() const noexcept { return *this; }

    };

}

#endif

