

#ifndef Y_Singleton_Included
#define Y_Singleton_Included 1


#include "y/concurrent/singulet.hpp"
#include "y/calculus/alignment.hpp"
#include "y/memory/stealth.hpp"
#include "y/type/destruct.hpp"


namespace Yttrium
{

    template <typename T>
    class Singleton : public Concurrent::Singulet
    {
    public:


        static inline T & Instance()
        {
            static void * workspace[ Alignment::WordsFor<T>::Count ];
            static bool   subscribe = true;

            if( 0 == Instance_ )
            {
                if(subscribe)
                {

                }
            }
        }

        virtual const char * callSign() const noexcept
        {
            return T::CallSign;
        }

        virtual Longevity lifeTime() const noexcept
        {
            return T::LifeTime;
        }

    private:
        Y_Disable_Copy_And_Assign(Singleton);
        static T * Instance_;
        static inline void Release(void*) noexcept
        {
            if(0!=Instance_)
            {
                Memory::Stealth( Destructed(Instance_), sizeof(T) );
            }
        }

        inline explicit Singleton()
        {
        }

        inline virtual ~Singleton() noexcept
        {
        }

    };

}

#endif
