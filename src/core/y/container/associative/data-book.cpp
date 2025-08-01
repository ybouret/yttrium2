
#include "y/container/associative/data-book.hpp"
#include "y/container/associative/hash/map.hpp"
#include "y/type/destroy.hpp"


namespace Yttrium
{

    namespace
    {
        typedef HashMap<uint64_t,uint64_t> MapType;

    }

    class DataBook:: Code : public Object, public MapType
    {
    public:


        explicit Code()
        {
        }

        virtual ~Code() noexcept
        {
        }


    private:
        Y_Disable_Copy_And_Assign(Code);
    };

    DataBook:: ~DataBook() noexcept
    {
        assert(code);
        Destroy(code);
    }

}
