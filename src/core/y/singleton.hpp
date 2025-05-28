

#ifndef Y_Singleton_Included
#define Y_Singleton_Included 1


#include "y/concurrent/singulet.hpp"
#include "y/concurrent/singleton/class-lock-policy.hpp"
#include "y/calculus/alignment.hpp"
#include "y/memory/stealth.hpp"
#include <new>

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Singleton implementation
    //
    //
    //__________________________________________________________________________
    template <typename T, typename LOCK_POLICY = ClassLockPolicy>
    class Singleton : public Concurrent::Singulet, public LOCK_POLICY
    {
    public:

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! get/create instance
        /**
         \return the unique instance
         */
        static inline T & Instance()
        {
            static void *     workspace[ Alignment::WordsFor<T>::Count ];
            static bool       subscribe = true;
			static Lockable & giantLock = Lockable::Giant();
            
			Y_Lock(giantLock);
            if( 0 == Instance_ )
            {
				Y_Lock(giantLock);

                //--------------------------------------------------------------
                // subscribe to AtExit once
                //--------------------------------------------------------------

                if(subscribe)
                {
                    System::AtExit::Perform(Release,0,T::LifeTime);
                    subscribe = false;
                }

                //--------------------------------------------------------------
                // create
                //--------------------------------------------------------------
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

        //! check existence
        /** \return true iff instantiated */
        static inline bool Exists() noexcept
        {
            Y_Giant_Lock();
            return 0 != Instance_;
        }

        //! location of instantiated singleton
        /** \return previously setup singleton */
        static inline T & Location() noexcept
        {
            assert(0!=Instance_);
            return *Instance_;
        }

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________

        //! [Identifiable]
        /** \return CallSign */
        inline virtual const char * callSign() const noexcept
        {
            return T::CallSign;
        }

        //! [Singulet]
        /** \return LifeTime */
        inline virtual Longevity lifeTime() const noexcept
        {
            return T::LifeTime;
        }

        

    private:
        Y_Disable_Copy_And_Assign(Singleton); //!< discarding
        static T * Instance_;                 //!< instance location

        //! release singleton and its resources
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
        //! initialize
        inline explicit Singleton() {}

        //! cleanup
        inline virtual ~Singleton() noexcept {}

    };

    template <typename T,typename LOCK_POLICY>
    T * Singleton<T,LOCK_POLICY>::Instance_ = 0;

}

#endif
