//! \file

#ifndef Y_Random_Bits_Included
#define Y_Random_Bits_Included 1

#include "y/ability/serializable.hpp"
#include "y/ability/identifiable.hpp"

#include "y/type/alternative.hpp"
#include "y/type/traits.hpp"
#include "y/type/is-signed.hpp"

namespace Yttrium
{
    namespace Random
    {

        //______________________________________________________________________
        //
        //
        //
        //! interface to random bits
        //
        //
        //______________________________________________________________________
        class Bits : public Identifiable
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            class               Metrics;
            typedef long double Real;     //!< alias

        protected:
            //! setup \param highest32 higest reached 32-bits value
            explicit Bits(const uint32_t highest32) noexcept;

        public:
            virtual ~Bits() noexcept; //!< cleanup
            //__________________________________________________________________
            //
            //
            //  Interface
            //
            //__________________________________________________________________
            virtual uint32_t next32() noexcept = 0; //!< \return next 32-bits value

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            Real             real32() noexcept;                  //!< convert uint32_t \return floating point in ]0:1[
            uint64_t         fill64(const size_t nbit) noexcept; //!< \param nbit number of bits \return truncated uint64_t with nbit
            bool             choice() noexcept;                  //!< \return equiprobable choice

            //! \return any floating point in ]0:1[
            template <typename T> inline T toR() noexcept { return static_cast<T>( real32() ); }

            //! \return any unsigned integral value
            template <typename T> inline T toU() noexcept
            {
                return static_cast<T>( fill64(sizeof(T)*8) );
            }

            //! \return any signed integral value
            template <typename T> inline T toS() noexcept
            {
                const T u = static_cast<T>( fill64(sizeof(T)*8-1) );
                return choice() ? -u : u;
            }

        private:
            //! return type selection
            enum ReturnType
            {
                ReturnR, //!< return floating point
                ReturnU, //!< return unsigned integer
                ReturnS  //!< return signed   integer
            };

        public:

            //! \return return selected random type
            template <typename T>
            T to() noexcept
            {
                static const  typename Alternative<
                TypeTraits<T>::IsIsoFloatingPoint , IntToType<ReturnR>,
                IsSigned<T>::Value,                 IntToType<ReturnS>,
                /* unsigned integral */             IntToType<ReturnU> >::Type Choice = {};
                return to<T>(Choice);
            }






        private:
            Y_Disable_Copy_And_Assign(Bits); //!< discarding
            Metrics * const metrics;         //!< internal metrics

            template <typename T> inline T to( const IntToType<ReturnR> & ) noexcept { return toR<T>(); } //!< \return floating point
            template <typename T> inline T to( const IntToType<ReturnU> & ) noexcept { return toU<T>(); } //!< \return unsigned
            template <typename T> inline T to( const IntToType<ReturnS> & ) noexcept { return toS<T>(); } //!< \return signed

        };



    }
}

#endif

