
//! \file

#ifndef Y_Memory_Studio_Included
#define Y_Memory_Studio_Included 1


#include "y/memory/management/inferno.hpp"
#include "y/singleton.hpp"
#include "y/xml/attribute.hpp"

namespace Yttrium
{
    namespace Memory
    {
        template <typename T,const System::AtExit::Longevity LIFE_TIME>
        class Studio : public Singleton<Studio<T,LIFE_TIME>,ClassLockPolicy>
        {
        public:
            typedef Singleton<Studio<T,LIFE_TIME>,ClassLockPolicy> SelfType;
            static const char * const              CallSign;
            static const System::AtExit::Longevity LifeTime = LIFE_TIME;


            virtual void display(std::ostream &os, size_t indent) const
            {
                const Caching &self = *inferno;;
                this->initProlog(os,indent)
                << XML::Attribute("cached",self.count());
                this->initEpilog(os,true);
            }




        private:
            Y_Disable_Copy_And_Assign(Studio);
            friend class Singleton<Studio<T,LIFE_TIME>,ClassLockPolicy>;

            Inferno<T> inferno;

            inline explicit Studio() :
            //Singleton<Studio<T,LIFE_TIME>,ClassLockPolicy>(),
            SelfType(),
            inferno()
            {
            }

            inline virtual ~Studio() noexcept
            {

            }


        };
    }
}

#endif

