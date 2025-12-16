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
        //______________________________________________________________________
        //
        //
        //
        //! indexed data column
        //
        //
        //______________________________________________________________________
        class DataColumn : public CountedObject
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef Keyed< size_t,ArcPtr<DataColumn> > Pointer; //!< alias
            typedef void (*Grow)(void * const, const String &, const char * const); //!< push converted string

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param idx column index \param col PERSISTENT column
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

            //! cleanup
            virtual ~DataColumn() noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            const size_t & key() const noexcept; //!< \return indx
            void append(const String &data);     //!< \param data converted and pushed into column


            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const size_t indx;     //!< column index
        private:
            void * const addr;     //!< column address
            Grow   const grow;     //!< dedicated grow
        public:
            const char   name[32]; //!< variable name

        private:
            Y_Disable_Copy_And_Assign(DataColumn); //!< discarding

            void format(); //!< format name

            //! grow function
            /**
             \param pcol    pointer to column
             \param data    data as string
             \param varName variable name for Convert
             */
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

        typedef HashSet<size_t,DataColumn::Pointer> DataColumns; //!< alias

        //______________________________________________________________________
        //
        //
        //
        //! Database of indexed columns
        //
        //
        //______________________________________________________________________
        class DataSet : public DataColumns
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign; //!< "MKL::DataSet"

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit DataSet();          //!< setup
            virtual ~DataSet() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! helper to insert new column
            /**
             \param idx column index
             \param col persistent column
             \return *this
             */
            template <typename T, typename CONTAINER> inline
            DataSet & add(const size_t            idx,
                          Sequence<T,CONTAINER> & col)
            {
                return add( new DataColumn(idx,col) );
            }

            //! fill columns
            void load(InputStream &);


        private:
            Y_Disable_Copy_And_Assign(DataSet); //!< discarding
            DataSet & add(DataColumn * const);  //!< helper \return *this
        };
    }
}

#endif // !Y_MKL_DataSet_Included

