//! \file

#ifndef Y_MKL_DataSet_Included
#define Y_MKL_DataSet_Included 1

#include "y/ascii/convert.hpp"
#include "y/container/sequence.hpp"
#include "y/container/associative/hash/set.hpp"
#include "y/pointer/arc.hpp"
#include "y/pointer/keyed.hpp"

#include "y/stream/input.hpp"

namespace Yttrium
{
    namespace MKL
    {
        class DataColumn : public CountedObject
        {
        public:
            typedef Keyed< size_t,ArcPtr<DataColumn> > Pointer;
            typedef void (*Grow)(void * const, const String &, const char * const);

            template <typename T, typename CONTAINER>
            explicit DataColumn(const size_t           idx,
                                Sequence<T,CONTAINER> & col) :
            indx(  idx ),
            addr( &col ),
            grow( Grow_<T,CONTAINER> ),
            name()
            {
                format();
            }

            virtual ~DataColumn() noexcept;

            const size_t & key() const noexcept;

            void append(const String &data);



            const size_t indx;
            void * const addr;
            Grow   const grow;
            const char   name[32]; //!< variable name

        private:
            Y_Disable_Copy_And_Assign(DataColumn);

            void format();

            template <typename T, typename CONTAINER> static inline
            void Grow_(void * const       pcol,
                       const String &     data,
                       const char * const varName)
            {
                assert(0!=pcol);
                const T value = ASCII::Convert::To<T>(data,varName);
                static_cast<Sequence<T,CONTAINER> *>(pcol)->pushTail(value);
            }


        };

        typedef HashSet<size_t,DataColumn::Pointer> DataColumns;

        class DataSet : public DataColumns
        {
        public:
            static const char * const CallSign;

            explicit DataSet();
            virtual ~DataSet() noexcept;

            template <typename T, typename CONTAINER> inline
            DataSet & add(const size_t            idx,
                          Sequence<T,CONTAINER> & col)
            {
                return add( new DataColumn(idx,col) );
            }

            void load(InputStream &fp);


        private:
            Y_Disable_Copy_And_Assign(DataSet);
            DataSet & add(DataColumn * const);
        };
    }
}

#endif // !Y_MKL_DataSet_Included

