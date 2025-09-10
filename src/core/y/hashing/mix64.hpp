//! \file


#ifndef Y_Hashing_Mix64_Included
#define Y_Hashing_Mix64_Included 1

#include "y/core/setup.hpp"
#include "y/check/static.hpp"
#include "y/ability/identifiable.hpp"
#include "y/type/traits.hpp"

namespace Yttrium
{
    namespace Hashing
    {
        //______________________________________________________________________
        //
        //
        //
        //! Mixing 64 bits integer
        //
        //
        //______________________________________________________________________
        class Mix64 : public Identifiable
        {
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
        protected: explicit Mix64() noexcept; //!< setup
        public:    virtual ~Mix64() noexcept; //!< cleanup


            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void         operator()(uint32_t &, uint32_t &) const noexcept = 0; //!< mix left/right words

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! output a mixed value, for any unsigned integers
            /**
             \param value any unsigned integer
             \return its mixed value
             */
            template <typename T,typename U> inline
            U mix(T & value) const noexcept
            {
                Y_STATIC_CHECK(sizeof(T)<=sizeof(uint64_t),InputTooBig);
                Y_STATIC_CHECK(sizeof(U)<=sizeof(uint64_t),OutputTooBig);
                typedef typename TypeTraits<T>::MutableType MutableT;
                typedef typename TypeTraits<U>::MutableType MutableU;

                union {
                    uint64_t qw;
                    uint32_t dw[2];
                    MutableT xx;
                    MutableU yy;
                } alias = { 0 };
                alias.xx = (MutableT)value;
                (*this)(alias.dw[0],alias.dw[1]);
                return alias.yy;
            }



        private:
            Y_Disable_Copy_And_Assign(Mix64); //!< discareding
        };

    }
}

#endif

