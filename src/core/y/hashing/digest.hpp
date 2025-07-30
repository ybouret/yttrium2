//! \file

#ifndef Y_Hashing_Digest_Included
#define Y_Hashing_Digest_Included 1

#include "y/container/contiguous.hpp"
#include "y/memory/buffer/rw.hpp"
#include "y/string.hpp"

namespace Yttrium
{
    namespace Hashing
    {
        //______________________________________________________________________
        //
        //
        //
        //! fixed-size digest for hashing operations
        //
        //
        //______________________________________________________________________
        class Digest : public Contiguous< Writable<uint8_t> >, public Memory::ReadWriteBuffer
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign; //!< "Hashing::Digest"


            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            Digest(const size_t width); //!< setup \param width exact fixed width
            Digest(const Digest &);     //!< duplicate
            virtual ~Digest() noexcept; //!< cleanup
            Digest(const char * const); //!<  setup from hexadecimal string

            //! display \return output stream
            friend std::ostream & operator<<(std::ostream &, const Digest &);

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual const void * ro()     const noexcept;
            virtual size_t       length() const noexcept;
            virtual size_t       size()   const noexcept; //!< \return width

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            String               str() const noexcept; //!< \return converted to string
            void                 ldz()       noexcept; //!< set to zero


        private:
            class Code;
            Y_Disable_Assign(Digest); //!< discarding
            Code * const code;        //!< inner code

            //! \return byte at given index
            virtual ConstType & getItemAt(const size_t) const noexcept;
        };

    }
}

#endif

