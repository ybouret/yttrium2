
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
        class Multiplier
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
            inline explicit Multiplier() noexcept {} //!< setup
        public:
            inline virtual ~Multiplier() noexcept {} //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void ld1() noexcept = 0; //!< clear
            virtual T    product()      = 0; //!< must reset after computation \return product

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! store/use data \param value data \return *this
            inline Multiplier & operator<<(ParamType value) { mul(value); return *this; }

            //! syntax helper \param value data \return *this
            inline Multiplier & operator*=(ParamType value) { mul(value); return *this; }

            inline Multiplier & ipower(ParamType value, size_t n)
            {
                mul(value,n);
                return *this;
            }



            //! load a range without reset
            /**
             \param  curr initial iterator
             \param  size range size
             \return *this
             */
            template <typename ITERATOR> inline
            Multiplier & load(ITERATOR curr, size_t size)
            {
                while(size-- > 0) mul( *(curr++) );
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
                ld1(); return load(curr,size).product();
            }

            //! \param seq sequence \return sum of sequence
            template <typename SEQUENCE> inline
            T operator()(SEQUENCE &seq)
            {
                return (*this)(seq.begin(),seq.size());
            }

        protected:
            virtual void mul(ParamType) = 0;        //!< store/use data
            virtual void mul(ParamType,size_t) = 0; //!< store/use data

        private:
            Y_Disable_Copy_And_Assign(Multiplier);  //!< discarding

        };

    }
}

#endif
