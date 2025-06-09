
//! \file

#ifndef Y_Memory_Netherworld_Included
#define Y_Memory_Netherworld_Included 1


#include "y/memory/management/purgatory.hpp"
#include "y/memory/management/dead-pool.hpp"
#include "y/singleton.hpp"
#include "y/xml/attribute.hpp"
#include "y/type/destruct.hpp"

namespace Yttrium
{
    namespace Memory
    {
        template <typename T,const System::AtExit::Longevity LIFE_TIME>
        class Netherworld :
        public Singleton<Netherworld<T,LIFE_TIME>,ClassLockPolicy>,
        public Purgatory<T>
        {
        public:
            typedef Singleton<Netherworld<T,LIFE_TIME>,ClassLockPolicy> SingletonType;
            static const char * const              CallSign;
            static const System::AtExit::Longevity LifeTime = LIFE_TIME;
            using SingletonType::access;


            virtual void display(std::ostream &os, size_t indent) const
            {
#if 0
                const Caching &self = *inferno;;
                this->initProlog(os,indent)
                << XML::Attribute("cached",self.count());
                this->initEpilog(os,true);
#endif
            }

            virtual void zombify(T * const object) noexcept
            {
                Y_Lock(access);
                deadPool.store( Destructed(object) );
            }

            




        private:
            Y_Disable_Copy_And_Assign(Netherworld);
            friend class Singleton<Netherworld<T,LIFE_TIME>,ClassLockPolicy>;

            DeadPool deadPool;

            inline explicit Netherworld() :
            SingletonType(), deadPool( sizeof(T) )
            {
            }

            inline virtual ~Netherworld() noexcept
            {

            }


        };
    }
}

#endif

