//! \file

#ifndef Y_Memory_Supply_Of_Included
#define Y_Memory_Supply_Of_Included 1


#include "y/singleton.hpp"
#include "y/memory/io/limbo.hpp"
#include "y/threading/multi-threaded-handle.hpp"

namespace Yttrium
{
    namespace Memory
    {

        template <typename T>
        class SupplyOf :
        public Singleton<SupplyOf<T>,ClassLockPolicy>,
        public Limbo<T, MultiThreadedHandle< SupplyOf<T> > >
        {
        public:
            static const System::AtExit::Longevity LifeTime = T::LifeTime;
            static const char * const              CallSign;

            inline virtual void display(std::ostream &os, size_t indent) const
            {
            }

        private:
            Y_Disable_Copy_And_Assign(SupplyOf);
            friend class Singleton< SupplyOf<T>, ClassLockPolicy>;

            inline explicit SupplyOf()
            {
            }

            inline virtual ~SupplyOf() noexcept
            {
            }
        };

        template <typename T>
        const char * const SupplyOf<T>::CallSign = T::CallSign;

    }
}

#endif
