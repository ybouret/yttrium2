//! \file

#ifndef Y_Memory_Purgatory_Included
#define Y_Memory_Purgatory_Included 1

#include "y/ability/caching.hpp"

namespace Yttrium
{
    namespace Memory
    {
        template <typename T>
        class Purgatory : public Caching
        {
        protected:
            inline explicit Purgatory() noexcept {}
            inline virtual ~Purgatory() noexcept {}

        public:
            virtual void zombify(T * const object) noexcept    = 0;
            virtual T *  recover()                             = 0;
            virtual T *  reenact(const T &object)              = 0;

        private:
            Y_Disable_Copy_And_Assign(Purgatory);
            virtual T *  produce(T * (*proc)(void *, void *), void *) = 0;

        };

        
    }
}

#endif
