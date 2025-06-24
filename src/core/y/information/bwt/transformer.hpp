
//! \file

#ifndef Y_Information_BWT_Transformer_Included
#define Y_Information_BWT_Transformer_Included 1


#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Information
    {

        //______________________________________________________________________
        //
        //
        //
        //! perform BWT transforms
        //
        //
        //______________________________________________________________________
        class BWT_Transformer
        {
        public:
            class Code;
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit BWT_Transformer() noexcept; //!< setup
            virtual ~BWT_Transformer() noexcept; //!< cleanu[

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! encode
            /**
             \param target target[length]
             \param source source[length]
             \param length number of bytes
             \return primary index
             */
            size_t encode(void * const       target,
                          const void * const source,
                          const size_t       length);

            //! encode
            /**
             \param target target[length]
             \param source source[length]
             \param length number of bytes
             \param primary primary index
             */
            void   decode(void * const       target,
                          const void * const source,
                          const size_t       length,
                          const size_t       primary);

        private:
            Y_Disable_Copy_And_Assign(BWT_Transformer); //!< discardin
            Code *code; //!< internal memory
            void make(const size_t); //!< adjust internal memory
        };
    }

}

#endif

