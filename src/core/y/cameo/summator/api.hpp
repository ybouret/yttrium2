//! \file

#ifndef Y_Cameo_Summator_Included
#define Y_Cameo_Summator_Included 1

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
        class Summator
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
            inline explicit Summator() noexcept {} //!< setup
        public:
            inline virtual ~Summator() noexcept {} //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void ldz() noexcept = 0; //!< clear
            virtual T    sum()          = 0; //!< must reset after computation \return sum

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! store/use data \param value data \return *this
            inline Summator & operator<<(ParamType value) { add(value); return *this; }

            //! load a range without reset
            template <typename ITERATOR> inline
            Summator & load(ITERATOR curr, size_t size)
            {
                while(size-- > 0) add( *(curr++) );
                return *this;
            }

            //! reset, load range and return sum
            template <typename ITERATOR> inline
            T operator()(ITERATOR curr, const size_t size)
            {
                ldz(); return load(curr,size).sum();
            }

            template <typename SEQUENCE> inline
            T operator()(SEQUENCE &seq)
            {
                return (*this)(seq.begin(),seq.size());
            }



        private:
            Y_Disable_Copy_And_Assign(Summator); //!< discarding
            virtual void add(ParamType) = 0;   //!< store/use data
        };

    }
}

#endif
