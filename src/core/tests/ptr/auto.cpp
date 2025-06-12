
#include "y/ptr/ptr.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

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

Y_UTEST(ptr_auto)
{
    { AutoPtr<int> ip; Y_CHECK(ip.isEmpty()); std::cerr << ip << std::endl; }
    { StrictPtr<int> ip( new int(4) );  std::cerr << ip << std::endl; }

}
Y_UDONE()
