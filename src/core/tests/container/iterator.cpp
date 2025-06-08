
#include "y/container/iterator/linear.hpp"
#include "y/type/conversion.hpp"
#include "y/core/display.hpp"
#include "y/memory/stealth.hpp"
#include "y/utest/run.hpp"

#include "y/container/writable.hpp"
#include "y/check/static.hpp"
#include "y/core/display.hpp"

namespace Yttrium
{


    template <template <typename> class CONTAINER, typename T>
    class ReadableContiguous : public CONTAINER<T>
    {
    public:
        Y_ARGS_EXPOSE(T,Type);
        explicit ReadableContiguous() noexcept : CONTAINER<T>()
        {
            Y_STATIC_CHECK(Y_Is_SuperSubClass(Readable<T>,CONTAINER<T>),BadBaseClass);
        }

        virtual ~ReadableContiguous() noexcept
        {
        }
    };


    template <template <typename> class CONTAINER, typename T>
    class WritableContiguous : public CONTAINER<T>
    {
    public:
        Y_ARGS_EXPOSE(T,Type);
        explicit WritableContiguous() noexcept : CONTAINER<T>()
        {
            Y_STATIC_CHECK(Y_Is_SuperSubClass(Writable<T>,CONTAINER<T>),BadBaseClass);
        }

        virtual ~WritableContiguous() noexcept
        {
        }
    };




#if 0
    template <template <typename> class CONTAINER, typename T>
    class Contiguous : public CONTAINER<T>
    {
    public:
        Y_ARGS_EXPOSE(T,Type);
        using CONTAINER<T>::size;

        static const bool IsReadable = Y_Is_SuperSubClass(Readable<T>,CONTAINER<T>);
        static const bool IsWritable = Y_Is_SuperSubClass(Writable<T>,CONTAINER<T>);

        typedef Iterator::Linear<Iterator::Forward,ConstType> ConstIterator;

        typedef typename Pick<IsWritable, Iterator::Linear<Iterator::Forward,Type>, NullType>::Type Iterator;

        explicit Contiguous() noexcept
        {
            Y_STATIC_CHECK(IsReadable||IsWritable,BadBaseClass);
        }

        virtual ~Contiguous() noexcept
        {
        }



        inline ConstIterator begin() const noexcept { return head(); }
        inline ConstIterator end()   const noexcept { return last(); }



    private:
        Y_Disable_Copy_And_Assign(Contiguous);
        inline ConstType * head() const noexcept {
            return (size()>0) ? & (*this)[1] : 0;
        }

        inline ConstType * last() const noexcept {
            const size_t sz = size();
            return  (sz>0) ? & (*this)[1]+sz : 0;
        }

    };

    template <typename T> class ReadableLightArray :
    public Contiguous<Readable,T>
    {
    public:
        Y_ARGS_EXPOSE(T,Type);
        inline ReadableLightArray(ConstType * const entry,
                                  const size_t      count) noexcept :
        bulk(count),
        item(entry-1)
        {
        }

        inline virtual ~ReadableLightArray() noexcept
        {
        }

        virtual size_t size() const noexcept { return bulk; }

    private:
        Y_Disable_Copy_And_Assign(ReadableLightArray);
        const size_t      bulk;
        ConstType * const item;

        virtual ConstType & getItemAt(const size_t indx) const noexcept
        {
            assert(bulk>0);
            assert(0!=item);
            return item[indx];
        }

    };
#endif

}

using namespace Yttrium;

Y_UTEST(container_iterator)
{

    int array[10];

    const size_t n = sizeof(array)/sizeof(array[0]);
    for(size_t i=0;i<n;++i) array[i] = int(i);


#if 0
    ReadableLightArray<int> arr(array,n);

    for(ReadableLightArray<int>::ConstIterator it=arr.begin();it!=arr.end();++it)
    {
        std::cerr << *it << std::endl;
    }

    Y_PRINTV(arr.IsWritable);
    Y_PRINTV(arr.IsReadable);
    std::cerr << arr << std::endl;
    Core::Display(std::cerr, arr.begin(), arr.size()) << std::endl;
#endif


}
Y_UDONE()
