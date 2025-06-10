//! \file

#ifndef Y_Memory_Operating_Included
#define Y_Memory_Operating_Included 1

#include "y/memory/operative.hpp"
#include "y/type/args.hpp"

namespace Yttrium
{
    namespace Memory
    {

        template <typename T>
        class Operating : public Operative
        {
        public:
            Y_ARGS_EXPOSE(T,Type);

            inline virtual ~Operating() noexcept {}

            //! initialize with default constructor
            inline Operating(void * const entry,
                             const size_t count) :
            Operative(entry, count, sizeof(T), Init0, 0, Quit)
            {
            }




        private:
            Y_Disable_Copy_And_Assign(Operating);
            static inline void Init0(void       * const target,
                                     const void * const,
                                     const size_t)
            {
                assert(0!=target);
                new (target) Type();
            }

            static inline void Quit(void * const addr) noexcept
            {
                assert(0!=addr);
                static_cast<MutableType *>(addr)->~MutableType();
            }
        };
    }

}

#endif
