
#include "y/object/school-of.hpp"
#include "y/memory/operating.hpp"
#include "y/utest/run.hpp"
#include "y/type/destroy.hpp"
#include "y/container/expandable.hpp"

using namespace Yttrium;

namespace
{
    class MyChars : public Object, public Memory::SchoolOf<char>
    {
    public:
        inline explicit MyChars(const size_t n) : Object(), Memory::SchoolOf<char>(n)
        {
        }

        inline virtual ~MyChars() noexcept
        {
        }

    private:
        Y_Disable_Copy_And_Assign(MyChars);
    };
}

Y_UTEST(memory_school_of)
{

    {
        Memory::SchoolOf<int>  data(10);
        Memory::Operating<int> op(data.entry,data.count);
    }


#if 0
    MyChars *code  = 0;
    size_t   built = 0;
    for(size_t i=1;i<=1000;++i)
    {
        if(!code)
        {
            code = new MyChars(8);
        }
        else
        {
            Y_ASSERT(code);
            if(built>=code->count)
            {
                MyChars * temp = new MyChars( Expandable::NextCapacity(built) );
                memcpy(temp->entry,code->entry,built);
                delete code;
                code = temp;
            }
        }
        Y_ASSERT(0==code->entry[built]);
        code->entry[built++] = 'a';
    }


    if(code) Destroy(code);

#endif
    for(size_t i=1;i<=992;++i)
    {
        std::cerr << "@" << i << std::endl;
        MyChars * code = new MyChars(i);
        delete code;
        std::cerr << "done" << std::endl;
    }



}
Y_UDONE()

