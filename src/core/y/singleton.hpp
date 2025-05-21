

#ifndef Y_Singleton_Included
#define Y_Singleton_Included 1


#include "y/concurrent/singulet.hpp"
#include "y/concurrent/singleton/giant-lock-policy.hpp"
#include "y/concurrent/singleton/class-lock-policy.hpp"
#include "y/calculus/alignment.hpp"
#include "y/memory/stealth.hpp"


namespace Yttrium
{


    template <typename T, typename LOCK_POLICY = ClassLockPolicy>
    class Singleton : public Concurrent::Singulet, public LOCK_POLICY
    {
    public:

        static inline T & Instance()
        {
            static void *     workspace[ Alignment::WordsFor<T>::Count ];
            static bool       subscribe = true;
			static Lockable & giantLock = Lockable::Giant();
            
			Y_Lock(giantLock);
            if( 0 == Instance_ )
            {
				Y_Lock(giantLock);

                // subscribe to AtExit once
                if(subscribe)
                {
                    System::AtExit::Perform(Release,0,T::LifeTime);
                    subscribe = false;
                }

                // create
                if(Verbose) Display("+", T::CallSign, T::LifeTime);
                try
                {
                    Instance_ = new ( Y_Memory_BZero(workspace) ) T();
                }
                catch(...)
                {
                    (void) Y_Memory_BZero(workspace);
                    Instance_ = 0;
                    throw;
                }
            }

            return *Instance_;
        }

        inline virtual const char * callSign() const noexcept
        {
            return T::CallSign;
        }

        inline virtual Longevity lifeTime() const noexcept
        {
            return T::LifeTime;
        }

        inline virtual Lockable & access() noexcept
        {
            return this->policyLock;
        }

    private:
        Y_Disable_Copy_And_Assign(Singleton);
        static T * Instance_;

        static inline void Release(void*) noexcept
        {
            if(0!=Instance_)
            {
                if(Verbose) Display("~", T::CallSign, T::LifeTime);
                Instance_->~T();
                Memory::Stealth::Zero(Instance_, sizeof(T) );
                Instance_ = 0;
            }
        }

    protected:
        inline explicit Singleton()
        {
        }

        inline virtual ~Singleton() noexcept
        {
        }

    };

    template <typename T,typename LOCK_POLICY>
    T * Singleton<T,LOCK_POLICY>::Instance_ = 0;

}

#endif
