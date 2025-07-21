
//! \file

#ifndef Y_Cameo_ScalarSummator_Included
#define Y_Cameo_ScalarSummator_Included 1

#include "y/cameo/selector.hpp"
#include "y/cameo/summator/direct.hpp"
#include "y/cameo/summator/aproxy.hpp"
#include "y/cameo/summator/fpoint.hpp"
#include "y/mkl/api/adaptor.hpp"

namespace Yttrium
{

    namespace Cameo
    {
        //______________________________________________________________________
        //
        //
        //
        //! Choose summator for scalar type
        //
        //
        //______________________________________________________________________
        template <typename T>
        class ScalarSummator : public Select<T,DirectSummator<T>,AProxySummator<T>,FPointSummator<T> >::API
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Expose(T,Type); //!< aliases
            typedef typename Select<T,DirectSummator<T>,AProxySummator<T>,FPointSummator<T> >::API SummatorType; //!< alias
            typedef TypeToType<MutableType> MyTypeHint; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! default constructor
            inline explicit ScalarSummator() : SummatorType() { }

            //! optional for FPointSummator \param n minimal capacity
            inline explicit ScalarSummator(const size_t n) : SummatorType(n) {}

            //! cleanup
            inline virtual ~ScalarSummator() noexcept  {}

            //! add product \param u first arg \param v second arg
            template <typename U, typename V> inline
            void addProd(const U &u, const V &v)
            {
                static const MyTypeHint MyType = {};
                ConstType res = MKL::AdaptedTo(MyType,u) * MKL::AdaptedTo(MyType,v);
                add(res);
            }

            //! dot product of a range \param lhs first iterator \param rhs second iterator \param n range size
            template <typename LHS, typename RHS>
            inline void addProd(LHS lhs, RHS rhs, size_t n)
            {
                while(n-- > 0)
                    addProd( *(lhs++), *(rhs++) );
            }


        private:
            Y_Disable_Copy_And_Assign(ScalarSummator); //!< discaring
        };
    }

}

#endif


