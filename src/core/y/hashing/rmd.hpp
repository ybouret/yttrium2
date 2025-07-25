//! \file
#ifndef Y_HASHING_RMD_INCLUDED
#define Y_HASHING_RMD_INCLUDED 1


#include "y/core/setup.hpp"

namespace Yttrium
{
    
    namespace Hashing
    {

        //! interface class for rmd
        class RMD
        {
        public:
            RMD() noexcept;  //!< setup
            ~RMD() noexcept; //!< destructor
            
          
            //! reset all fields
            void reset() noexcept;
            
            //! store in bytes, then in words
            /**
             \return true when 16 * 4 bytes are ready
             */
            bool store(uint8_t) noexcept;
            
            //! \return a full block
            const uint32_t *block() const noexcept;
            
            //! \return assemble the last block
            const uint8_t *flush() noexcept;

            //! internal length
            const size_t   length;
            
            uint32_t lswlen() const noexcept; //!< \return least significant word len
            uint32_t mswlen() const noexcept; //!< \return  most signigicant word len

        private:
            size_t   nx;     //!< current state
            size_t   nb;     //!< current state
            uint32_t X[16];  //!< words store
            uint8_t  B[4];   //!< bytes store
            Y_Disable_Copy_And_Assign(RMD); //!< discarding

        };
        
    }
    
}

#endif
