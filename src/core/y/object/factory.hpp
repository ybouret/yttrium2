//! \file

#ifndef Y_Object_Factory_Included
#define Y_Object_Factory_Included

#include "y/object.hpp"
#include "y/singleton.hpp"
#include "y/concurrent/life-time.hpp"

namespace Yttrium
{

    namespace Memory
    {
        namespace Object { class Blocks; }
        class Pooled;
        class Quanta;
    }
    
    class Object::Factory : public Singleton<Factory,ClassLockPolicy>
    {
    public:
        static const char * const CallSign; //!< "Object::Factory"
        static const Longevity    LifeTime = LifeTimeOf::ObjectFactory;
        static const size_t       CondensationBytes = 4;                                     //!< decrease complexity
        static const unsigned     CondensationShift = IntegerLog2<CondensationBytes>::Value; //!< ensure power of two

        virtual void display(std::ostream &,size_t) const;



        void * acquireSingle(const size_t blockSize);
        void   releaseSingle(void * const blockAddr, const size_t blockSize) noexcept;

        void * acquirePooled(const size_t blockSize);
        void   releasePooled(void * const blockAddr, const size_t blockSize) noexcept;

        void * acquireQuanta(const unsigned shift);
        void   releaseQuanta(const unsigned shift, void * const entry) noexcept;

        void * acquire(const size_t blockSize);
        void   release(void * const blockAddr, const size_t blockSize) noexcept;


    private:
        Y_Disable_Copy_And_Assign(Factory);
        friend class Singleton<Factory,ClassLockPolicy>;

        explicit Factory();
        virtual ~Factory() noexcept;

        const size_t * const condensation;
        Memory::Object::Blocks & blocks; //!< uses for small
        Memory::Pooled &         pooled; //!< used for medium
        Memory::Quanta &         quanta; //!< used for larger and special medium
       // Memory::System &         other;
    };
}

#endif

