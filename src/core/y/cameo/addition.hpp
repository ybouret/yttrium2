
//! \file

#ifndef Y_Cameo_Addition_Included
#define Y_Cameo_Addition_Included 1

#include "y/cameo/summator/vectorial.hpp"
#include "y/mkl/api/scalar.hpp"

namespace Yttrium
{

    namespace Cameo
    {

        //______________________________________________________________________
        //
        //
        //
        //! Scalar/Vectorial summator selection
        //
        //
        //______________________________________________________________________
        template <typename T>
        struct SummatorFor
        {
            static const bool IsScalar = MKL::IsScalar<T>::Value;                                 //!< alias
            typedef typename Pick<IsScalar, ScalarSummator<T>, VectorialSummator<T> >::Type Type; //!< alias
        };

        //______________________________________________________________________
        //
        //
        //
        //! Addition with API based on type
        //
        //
        //______________________________________________________________________
        template <typename T>
        class Addition : public SummatorFor<T>::Type
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef typename SummatorFor<T>::Type SummatorType; //!< alias
            Y_Args_Declare(T,Type); //!< aliases
            typedef TypeToType<MutableType> MyTypeHint; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            //! setup
            inline explicit Addition() : SummatorType()  {}

            //! setup with summator accepting initializer \param n capacity
            inline explicit Addition(const size_t n) : SummatorType(n) {}

            //! cleanup
            inline virtual ~Addition() noexcept {}

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! helper to initialize \param value initial value \return *this
            inline Addition & operator=(ParamType value) { this->ldz(); this->add(value); return *this; }

            //! add product \param u first arg \param v second arg
            template <typename U, typename V> inline
            void addProd(const U &u, const V &v)
            {
                static const MyTypeHint MyType = {};
                ConstType res = MKL::AdaptedTo(MyType,u) * MKL::AdaptedTo(MyType,v);
                this->add(res);
            }

            //! dot product of a range \param lhs first iterator \param rhs second iterator \param n range size
            template <typename LHS, typename RHS>
            inline void addProd(LHS lhs, RHS rhs, size_t n)
            {
                while(n-- > 0)
                {
                    //std::cerr << "+(" << *lhs << ")*(" << *rhs << ")";
                    addProd( *(lhs++), *(rhs++) );
                }
                //std::cerr << std::endl;
            }

            //! add u^2 to the sum \param u compatible are
            template <typename U> inline
            void addSquared(const U &u)
            {
                static const MyTypeHint MyType = {};
                MutableType res = MKL::AdaptedTo(MyType,u);
                this->add(res*=res);
            }

            //! \param u first \param v second \param w third \return u+v+w
            template <typename U, typename V, typename W> inline
            T operator()(U &u, V &v, W &w)
            {
                this->ldz();
                this->add(u);
                this->add(v);
                this->add(w);
                return this->sum();
            }

        private:
            Y_Disable_Copy_And_Assign(Addition); //!< discarding
        };

    }

}

#endif
