//! \file

#ifndef Y_Memory_Supply_Of_Included
#define Y_Memory_Supply_Of_Included 1


#include "y/singleton.hpp"
#include "y/memory/io/limbo.hpp"
#include "y/threading/multi-threaded-handle.hpp"
#include "y/xml/attribute.hpp"

namespace Yttrium
{
    namespace Memory
    {

        template <typename T>
        class SupplyOf :
        public Singleton<SupplyOf<T>,ClassLockPolicy>,
        public Limbo<T,MultiThreadedHandle>
        {
        public:
            static const System::AtExit::Longevity LifeTime = T::LifeTime;
            static const char * const              CallSign;

            inline virtual void display(std::ostream &os, size_t indent) const
            {
                const size_t blockSize = this->zombies.blockSize();
                this->initProlog(os,indent) << Y_XML_Attr(blockSize);
                this->initEpilog(os,true);
            }

        private:
            Y_Disable_Copy_And_Assign(SupplyOf);
            friend class Singleton< SupplyOf<T>, ClassLockPolicy>;

            inline explicit SupplyOf() :
            Singleton<SupplyOf<T>,ClassLockPolicy>(),
            Limbo<T,MultiThreadedHandle>( this->access )
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
