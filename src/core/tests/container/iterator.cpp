
#include "y/container/contiguous.hpp"

#include "y/container/iter/linear.hpp"
#include "y/core/display.hpp"
#include "y/memory/stealth.hpp"
#include "y/utest/run.hpp"

#include "y/core/display.hpp"

namespace Yttrium
{

    template <typename CONTAINER>
    class LightArray : public Contiguous<CONTAINER>
    {
    public:
        typedef typename CONTAINER::Type      Type;
        typedef typename CONTAINER::ConstType ConstType;


        inline  LightArray(ConstType * const entry,
                           const size_t      count) noexcept :
        bulk(count),
        item((ConstType *)Memory::Stealth::Address(entry) - 1)
        {
        }

        inline virtual ~LightArray() noexcept {}


    public:
        virtual size_t size() const noexcept { return bulk; }


    private:
        Y_Disable_Copy_And_Assign(LightArray);
        const size_t      bulk;
        ConstType * const item;

        virtual ConstType & getItemAt(const size_t indx) const noexcept
        {
            assert(bulk > 0);
            assert(0 != item);
            return item[indx];
        }
    };


}

using namespace Yttrium;


Y_UTEST(container_iterator)
{


    int array[10];

    const size_t n = sizeof(array) / sizeof(array[0]);
    for (size_t i = 0; i < n; ++i) array[i] = int(i);

    typedef LightArray< Readable<int> > ReadOnlyArray;
    ReadOnlyArray arr(array, n);
    std::cerr << arr << std::endl;
    Core::Display(std::cerr, arr.begin(), arr.size()) << std::endl;
    Core::Display(std::cerr, arr.rbegin(), arr.size()) << std::endl;


}
Y_UDONE()
