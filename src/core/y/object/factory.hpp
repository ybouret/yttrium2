//! \file

#ifndef Y_Object_Factory_Included
#define Y_Object_Factory_Included

#include "y/object.hpp"
#include "y/singleton.hpp"
#include "y/concurrent/life-time.hpp"
#include "y/memory/allocator.hpp"

namespace Yttrium
{

    namespace Memory
    {
        namespace Object { class Blocks; }
        class Pooled;
        class Quanta;
    }

    //__________________________________________________________________________
    //
    //
    //
    //! Factory for global Object allocation
    //
    //
    //__________________________________________________________________________
    class Object::Factory :
    public Singleton<Factory,ClassLockPolicy>,
    public Memory:: Allocator
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        static const char * const CallSign;                                                  //!< "Object::Factory"
        static const Longevity    LifeTime = LifeTimeOf::ObjectFactory;                      //!< life time
        static const size_t       CondensationBytes = 4;                                     //!< decrease complexity
        static const unsigned     CondensationShift = IntegerLog2<CondensationBytes>::Value; //!< ensure power of two

        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        virtual void display(std::ostream &,size_t) const;


        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        void * acquireSingle(const size_t blockSize);
        void   releaseSingle(void * const blockAddr, const size_t blockSize) noexcept;

        void * acquirePooled(const size_t blockSize);
        void   releasePooled(void * const blockAddr, const size_t blockSize) noexcept;

        void * acquireQuanta(const unsigned shift);
        void   releaseQuanta(const unsigned shift, void * const entry) noexcept;

        void * acquire(const size_t blockSize);
        void   release(void * const blockAddr, const size_t blockSize) noexcept;


    private:
        Y_Disable_Copy_And_Assign(Factory);  //!< discarding
        friend class Singleton<Factory,ClassLockPolicy>;

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        explicit Factory();
        virtual ~Factory() noexcept;

        virtual void * acquireBlock(size_t &);
        virtual void   releaseBlock(void * const,const size_t) noexcept;

        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________
        const size_t * const    condensation; //!< [1..LimitObjectBytes]

    public:
        Memory::Object::Blocks & blocks; //!< used for small
        Memory::Pooled &         pooled; //!< used for medium
        Memory::Quanta &         quanta; //!< used for larger and special medium
       // Memory::System &         other;
    };
}

#endif

