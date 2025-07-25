//! \file

#ifndef Y_HASHING_TO_KEY_INCLUDED
#define Y_HASHING_TO_KEY_INCLUDED 1


#include "y/hashing/to.hpp"
#include "y/hashing/key/variety.hpp"

namespace Yttrium
{

    namespace Hashing
    {
        //______________________________________________________________________
        //
        //
        //
        //! convert a Hashing::Function to a key hasher
        //
        //
        //______________________________________________________________________
        template <typename T, typename FUNCTION>
        class ToKey : public FUNCTION
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            inline explicit ToKey() noexcept : FUNCTION() {} //!< setup
            inline virtual ~ToKey() noexcept {}              //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! \param obj admissible object \return type dependent conversion hash
            template <typename U> inline
            T operator()(U &obj) noexcept
            {
                static const IntToType< KeyVariety::Cull<U>::Kind > which = {};
                return compute<U>(obj,which);
            }

        private:
            Y_Disable_Copy_And_Assign(ToKey); //!< discarding

            //! \param buf memory buffer \return its hash
            template <typename U>
            inline T compute( const U &buf, const KeyVariety::MemoryBuffer & ) noexcept
            { return To<T>(*this,buf); }

            //! \param pod integral data \return its hash
            template <typename U>
            inline T compute( const U &pod, const KeyVariety::IntegralType &) noexcept
            { return To<T>(*this,&pod,sizeof(U)); }

            //! \param buf C-string \return its hash
            template <typename U>
            inline T compute(const U &buf, const KeyVariety::LegacyString &) noexcept
            { return To<T>(*this,buf); }
        };
    }

}

#endif

