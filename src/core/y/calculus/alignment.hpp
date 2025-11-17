
//! \file

#ifndef Y_Calculus_Alignment_Included
#define Y_Calculus_Alignment_Included 1

#include "y/calculus/integer-log2.hpp"
#include "y/type/ints.hpp"
#include <cassert>

namespace Yttrium
{

    //! helper to produced result
#define Y_AlignmentOnLog2_Value() ( (N+Mask) & Not2 )

    //__________________________________________________________________________
    //
    //
    //
    //! Alignment templates and functions
    //
    //
    //__________________________________________________________________________
    struct Alignment
    {

        //______________________________________________________________________
        //
        //
        //! using log2 of requested size to align
        //
        //______________________________________________________________________
        template <unsigned LN2>
        struct OnLog2
        {
            static const size_t One      = 1;                                         //!< One
            static const size_t Byte     = One << LN2;                                //!< 2^LN2
            static const size_t Mask     = Byte-One;                                  //!< 2^LN2-1
            static const size_t Not2     = ~Mask;                                     //!< 2-complement of Mask
            static const size_t Maximum  = (IntegerFor<size_t>::Maximum/Byte) * Byte; //!< alias

            //! template ceil
            template <size_t N> struct CeilOf
            {
                 static const size_t Value = Y_AlignmentOnLog2_Value(); //!< result
            };

            //! function ceil
            /**
             \param  N guess value
             \return aligned value
             */
            static inline size_t Ceil(const size_t N) noexcept
            {
                assert(N<=Maximum);
                return Y_AlignmentOnLog2_Value();
            }
        };

        //______________________________________________________________________
        //
        //
        //! alignment on a power of two
        //
        //______________________________________________________________________
        template <size_t POWER_OF_TWO>
        struct On
        {
            typedef  OnLog2< IntegerLog2<POWER_OF_TWO>::Value > Inner;   //!< alias
            static const size_t Maximum = Inner::Maximum;                //!< alias

            //! template ceil
            template <size_t N> struct CeilOf
            {
                typedef typename Inner::template CeilOf<N> InnerCeilOf; //!< alias
                static const size_t Value = InnerCeilOf::Value;         //!< result
            };

            //! function ceil
            /**
             \param  N guess value
             \return aligned value
             */
            static inline size_t Ceil(const size_t N) noexcept
            {
                return Inner::Ceil(N);
            }
        };

        //______________________________________________________________________
        //
        //
        //! aligment on a size of a type, must be a power of two
        //
        //______________________________________________________________________
        template <typename T>
        struct To
        {
            typedef On<sizeof(T)> Outer; //!< alias
            static const size_t   Maximum = Outer::Maximum; //!< alias

            //! template ceil
            template <size_t N> struct CeilOf
            {
                typedef typename Outer::template CeilOf<N> OuterCeilOf; //!< alias
                static const size_t Value = OuterCeilOf::Value;         //!< result
            };

            

            //! function ceil
            /**
             \param  N guess value
             \return aligned value
             */
            static inline size_t Ceil(const size_t N) noexcept
            {
                return Outer::Ceil(N);
            }
        };

        typedef void *               SystemMemoryWord; //!< alias
        typedef To<SystemMemoryWord> SystemMemory;     //!< alias

        //______________________________________________________________________
        //
        //
        //! Compute number of SystemMemoryWord to hold BYTES
        //
        //______________________________________________________________________
        template <size_t BYTES> struct WordsGEQ
        {
            //! computation
            static const size_t Count = (SystemMemory:: template CeilOf<BYTES>::Value) / sizeof(SystemMemoryWord);
        };

        //______________________________________________________________________
        //
        //
        //! Compute number of SystemMemoryWord to hold T
        //
        //______________________________________________________________________
        template <typename T> struct WordsFor
        {
            //! computation
            static const int Count = WordsGEQ<sizeof(T)>::Count;
        };

    };

    
}

#endif // !Y_Calculus_Alignment_Included

