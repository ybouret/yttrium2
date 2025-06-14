
#include "y/ptr/ptr.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;


namespace Yttrium
{
    namespace Smart
    {

        template <class T> class Immediate
        {
        public:

            Y_ARGS_EXPOSE(T,Type);
            typedef Type *      ReturnType;
            typedef ConstType * ConstReturnType;


            inline virtual ~Immediate() noexcept {}
        protected:
            inline explicit Immediate() noexcept {}


            inline ReturnType      fetch(Type       *ptr)       noexcept { assert(0!=ptr); return ptr; }
            inline ConstReturnType fetch(const Type *ptr) const noexcept { assert(0!=ptr); return ptr; }

        private:
            Y_Disable_Copy_And_Assign(Immediate);
        };




        template <class T> class DrillDown
        {
        public:

            Y_ARGS_EXPOSE(T,Type);
            typedef Type &      ReturnType;
            typedef ConstType & ConstReturnType;


            inline virtual ~DrillDown() noexcept {}
        protected:
            inline explicit DrillDown() noexcept {}


            inline ReturnType      fetch(Type      *ptr)       noexcept { assert(0!=ptr); return *ptr; }
            inline ConstReturnType fetch(ConstType *ptr) const noexcept { assert(0!=ptr); return *ptr; }

        private:
            Y_Disable_Copy_And_Assign(DrillDown);
        };

        template <class T> class LockingProxy
        {
        public:
            Y_ARGS_EXPOSE(T,Type);
            inline LockingProxy(T * const ptr) : pointee((MutableType*)ptr)
            {
                assert(0!=pointee);
                pointee->lock();
            }

            inline ~LockingProxy() noexcept {
                assert(0!=pointee);
                pointee->unlock();
            }

            inline Type * operator->() noexcept {
                assert(0!=pointee);
                return pointee;
            }

        private:
            Y_Disable_Copy_And_Assign(LockingProxy);
            MutableType * const pointee;
        };

        template <class T> class FlashLock
        {
        public:
            Y_ARGS_EXPOSE(T,Type);
            typedef LockingProxy<Type>      ReturnType;
            typedef LockingProxy<ConstType> ConstReturnType;


            inline virtual ~FlashLock() noexcept {}
        protected:
            inline explicit FlashLock() noexcept {}

            inline ReturnType      fetch(Type      *ptr)       noexcept { assert(0!=ptr); return ReturnType(ptr); }
            inline ConstReturnType fetch(ConstType *ptr) const noexcept { assert(0!=ptr); return ConstReturnType(ptr); }
            
        private:
            Y_Disable_Copy_And_Assign(FlashLock);
        };

        template <typename T>
        class AcceptNull
        {
        public:

        private:

        };

        template <typename T>
        class RejectNull
        {
        public:

        private:

        };



    }

}

#if 0
namespace Yttrium
{

    template <typename T>
    class AutoPtr : public Ptr<T,AcceptingNull,Immediate>
    {
    public:
        explicit AutoPtr(T * const p = 0) noexcept :
        Ptr<T,AcceptingNull,Immediate>(p)
        {
        }

        virtual ~AutoPtr() noexcept
        {
            if(this->handle)
            {
                delete this->handle;
                this->handle = 0;
            }
        }

    private:
        Y_Disable_Copy_And_Assign(AutoPtr);
    };


    template <typename T>
    class StrictPtr : public Ptr<T,RejectingNull,Immediate>
    {
    public:
        explicit StrictPtr(T * const p) noexcept :
        Ptr<T,RejectingNull,Immediate>(p)
        {
        }

        virtual ~StrictPtr() noexcept
        {
            assert(0!=this->handle);
            delete this->handle;
            this->handle = 0;
        }

    private:
        Y_Disable_Copy_And_Assign(StrictPtr);
    };



}
#endif

Y_UTEST(ptr_auto)
{
    //{ AutoPtr<int> ip; Y_CHECK(ip.isEmpty()); std::cerr << ip << std::endl; }
    //{ StrictPtr<int> ip( new int(4) );  std::cerr << ip << std::endl; }

}
Y_UDONE()
