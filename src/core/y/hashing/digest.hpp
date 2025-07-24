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

        class Digest : public Contiguous< Writable<uint8_t> >, public Memory::ReadWriteBuffer
        {
        public:
            static const char * const CallSign;
            
            Digest(const size_t width);
            Digest(const Digest &);
            virtual ~Digest() noexcept;
            Digest(const char * const hex);

            virtual const void * ro()     const noexcept;
            virtual size_t       length() const noexcept;
            virtual size_t       size() const noexcept;
            friend std::ostream & operator<<(std::ostream &, const Digest &);

            String               str() const noexcept;

        private:
            class Code;
            Y_Disable_Assign(Digest);
            Code * const code;
            virtual ConstType & getItemAt(const size_t) const noexcept;
        };

    }
}

#endif

