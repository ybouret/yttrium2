
//! \file

#ifndef Y_HASHING_MAC_INCLUDED
#define Y_HASHING_MAC_INCLUDED 1


#include "y/hashing/hmac.hpp"
#include "y/string/length.hpp"

namespace Yttrium
{
    namespace Hashing
    {
        //! helper for constructor
#define Y_HMAC_ON_PROLOG() \
Function( FUNCTION::__length, FUNCTION::__window), H(), M(H,

        //! helper for constructor
#define Y_HMAC_ON_EPILOG() \
), id(String(HashMAC::Prefix)+H.callSign())

        //______________________________________________________________________
        //
        //
        //! assembling HMAC function
        //
        //______________________________________________________________________
        template <typename FUNCTION>
        class HMAC : public Function
        {
        public:
            //__________________________________________________________________
            //
            // C++
            //__________________________________________________________________

            //! setup \param key_addr key \param key_size length
            inline explicit HMAC(const void * const key_addr, const size_t key_size) :
            Y_HMAC_ON_PROLOG() key_addr,key_size Y_HMAC_ON_EPILOG() {}

            //! setup \param usr user buffer
            inline explicit HMAC(const Memory::ReadOnlyBuffer &usr) :
            Y_HMAC_ON_PROLOG() usr  Y_HMAC_ON_EPILOG() {}

            //! setup \param k user C-string key
            inline explicit HMAC(const char * const k) :
            Y_HMAC_ON_PROLOG() k,StringLength(k) Y_HMAC_ON_EPILOG() {}

            //! cleanup
            inline virtual ~HMAC() noexcept {}

            //__________________________________________________________________
            //
            // function interface
            //__________________________________________________________________

            //! prepare function
            inline virtual void set() noexcept { M.set(H); }

            //! run function \param block_addr block \param block_size length
            inline virtual void run(const void * const block_addr, size_t block_size) noexcept
            {
                H.run(block_addr,block_size);
            }

            //! get function from hmac \param output buffer \param outlen length
            inline virtual void get(void * const output, const size_t outlen) noexcept
            {
                const Memory::ReadOnlyBuffer &md = M.get(H);
                fill(output,outlen,md.ro(),md.length());
            }

            //! \return compound name
            virtual const char *callSign() const noexcept { return id.c_str(); }

            //__________________________________________________________________
            //
            // members
            //__________________________________________________________________
            FUNCTION H; //!< base hashing function
            HashMAC  M; //!< base hash mac creator
            
        private:
            Y_Disable_Copy_And_Assign(HMAC); //!< discarding
            const String id; //!< compound name
        };

    }

}

#endif
