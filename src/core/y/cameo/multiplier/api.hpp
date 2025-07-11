
//! \file

#ifndef Y_Cameo_Multipler_Included
#define Y_Cameo_Multipler_Included 1

#include "y/type/args.hpp"

namespace Yttrium
{

    namespace Cameo
    {

        //______________________________________________________________________
        //
        //
        //
        //! Summator API
        //
        //
        //______________________________________________________________________
        template <typename T>
        class Multipler
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Declare(T,Type); //!< aliases

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
        protected:
            inline explicit Multipler() noexcept {} //!< setup
        public:
            inline virtual ~Multipler() noexcept {} //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void ldz() noexcept = 0; //!< clear
            virtual T    prod()         = 0; //!< must reset after computation \return sum

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! store/use data \param value data \return *this
            inline Multipler & operator<<(ParamType value) { mul(value); return *this; }

            //! load a range without reset
            /**
             \param  curr initial iterator
             \param  size range size
             \return *this
             */
            template <typename ITERATOR> inline
            Multipler & load(ITERATOR curr, size_t size)
            {
                while(size-- > 0) add( *(curr++) );
                return *this;
            }

            //! reset, load range and return sum
            /**
             \param  curr initial iterator
             \param  size range size
             \return sum
             */
            template <typename ITERATOR> inline
            T operator()(ITERATOR curr, const size_t size)
            {
                ldz(); return load(curr,size).prod();
            }

            //! \param seq sequence \return sum of sequence
            template <typename SEQUENCE> inline
            T operator()(SEQUENCE &seq)
            {
                return (*this)(seq.begin(),seq.size());
            }



        private:
            Y_Disable_Copy_And_Assign(Multipler); //!< discarding
            virtual void mul(ParamType) = 0;   //!< store/use data
        };

    }
}

#endif
