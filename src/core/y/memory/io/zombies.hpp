//! \file

#ifndef Y_Memory_Zombies_Included
#define Y_Memory_Zombies_Included

#include "y/memory/page.hpp"
#include "y/ability/caching.hpp"
#include "y/type/destruct.hpp"

namespace Yttrium
{
    namespace Memory
    {

        //! pool of zombies of same block size
        class Zombies : public Caching
        {
        public:
            class Code;

            //! C++
            explicit Zombies(const size_t userBlockSize);
            virtual ~Zombies() noexcept;

#if 0
            template <typename T> inline
            T * conjure() {
                void * const addr = query();
                try { return new (addr) T(); }
                catch(...) { store(addr); throw; }
            }


            template <typename T> inline
            void banish(T * const object) noexcept
            {
                assert(0!=object);
                store( Destructed(object) );
            }
#endif

            // Interface
            virtual void   gc(uint8_t) noexcept;
            virtual size_t count() const noexcept;
            virtual void   cache(const size_t);

            // Methods
            size_t blockSize() const noexcept;

        protected:
            void *query();
            void  store(void * const addr) noexcept;

        private:
            Y_Disable_Copy_And_Assign(Zombies);
            Code * const code; //!< internal code, pool and metricss

        };

    }
}

#endif

