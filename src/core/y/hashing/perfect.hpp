//! \file

#ifndef Y_Hashing_Perfect_Included
#define Y_Hashing_Perfect_Included 1

#include "y/memory/buffer/ro.hpp"

namespace Yttrium
{

    class OutputStream;
    
    namespace Hashing
    {

        class Perfect
        {
        public:
            static const char * const CallSign; //!< "Hashing::Perfect"

            explicit Perfect();
            virtual ~Perfect() noexcept;

            void at(const void * const path, const size_t size, const int key);
            void at(const char * const, const int);
            void at(const Memory::ReadOnlyBuffer &, const int);

            int operator()(const void * const, const size_t) noexcept;
            int operator()(const char * const)               noexcept;
            int operator()(const Memory::ReadOnlyBuffer &)   noexcept;

            int operator()(const void * const, const size_t) const noexcept;
            int operator()(const char * const)               const noexcept;
            int operator()(const Memory::ReadOnlyBuffer &)   const noexcept;

            OutputStream & viz(OutputStream &) const;

        private:
            class Code;
            Y_Disable_Copy_And_Assign(Perfect);
            Code * const code;
        };
    }
}

#endif

