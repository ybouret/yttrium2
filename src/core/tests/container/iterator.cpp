
#include "y/container/iter/linear.hpp"
#include "y/type/conversion.hpp"
#include "y/core/display.hpp"
#include "y/memory/stealth.hpp"
#include "y/utest/run.hpp"

#include "y/container/writable.hpp"
#include "y/check/static.hpp"
#include "y/core/display.hpp"
#include "y/type/alternative.hpp"

namespace Yttrium
{


    template <template <typename> class CONTAINER, typename T>
    class ContiguousCommon : public CONTAINER<T>
    {
    protected:
        typedef typename CONTAINER<T>::ConstType ConstType;
        using CONTAINER<T>::size;
        inline explicit ContiguousCommon() noexcept : CONTAINER<T>() {}

    public:
        inline virtual ~ContiguousCommon() noexcept   {}


    private:
        Y_Disable_Copy_And_Assign(ContiguousCommon);

    protected:
        inline ConstType * head() const noexcept {
            return (size()>0) ? & (*this)[1] : 0;
        }

        inline ConstType * last() const noexcept {
            const size_t sz = size();
            return  (sz>0) ? & (*this)[1]+sz : 0;
        }
    };

    template <template <typename> class CONTAINER, typename T>
    class ReadableContiguous : public ContiguousCommon<CONTAINER,T>
    {
    public:
        Y_ARGS_EXPOSE(T,Type);
        typedef Iter::Linear<Iter::Forward,ConstType> ConstIterator;

    protected:
        explicit ReadableContiguous() noexcept : ContiguousCommon<CONTAINER,T>()
        {
            Y_STATIC_CHECK(Y_Is_SuperSubClass(Readable<T>,CONTAINER<T>),BadBaseClass);
        }

    public:
        virtual ~ReadableContiguous() noexcept
        {
        }

        inline ConstIterator begin() const noexcept { return this->head(); }
        inline ConstIterator end()   const noexcept { return this->last(); }

    private:
        Y_Disable_Copy_And_Assign(ReadableContiguous);
    };


    template <template <typename> class CONTAINER, typename T>
    class WritableContiguous : public ContiguousCommon<CONTAINER,T>
    {
    public:
        Y_ARGS_EXPOSE(T,Type);
        typedef Iter::Linear<Iter::Forward,ConstType> ConstIterator;
        typedef Iter::Linear<Iter::Forward,ConstType> Iterator;

    protected:
        explicit WritableContiguous() noexcept : ContiguousCommon<CONTAINER,T>()
        {
            Y_STATIC_CHECK(Y_Is_SuperSubClass(Writable<T>,CONTAINER<T>),BadBaseClass);
        }

        inline ConstIterator begin() const noexcept { return this->head(); }
        inline ConstIterator end()   const noexcept { return this->last(); }
        

    public:
        virtual ~WritableContiguous() noexcept
        {
        }

    private:
        Y_Disable_Copy_And_Assign(WritableContiguous);
    };

#define Y_Contiguous_Class() \
Alternative\
<\
Y_Is_SuperSubClass(Writable<T>,CONTAINER<T>),\
WritableContiguous<CONTAINER,T>,\
Y_Is_SuperSubClass(Readable<T>,CONTAINER<T>),\
ReadableContiguous<CONTAINER,T>,\
NullType>::Type

    template <template <typename> class CONTAINER, typename T>
    class Contiguous : public Y_Contiguous_Class()
    {
    protected:
        typedef typename Y_Contiguous_Class() ContainerType;
        explicit Contiguous() noexcept : ContainerType() {}

    public:
        virtual ~Contiguous() noexcept {}
        
    private:
        Y_Disable_Copy_And_Assign(Contiguous);
    };






#if 1
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



    ReadableLightArray<int> arr(array,n);

    for(ReadableLightArray<int>::ConstIterator it=arr.begin();it!=arr.end();++it)
    {
        std::cerr << *it << std::endl;
    }


    std::cerr << arr << std::endl;
    Core::Display(std::cerr, arr.begin(), arr.size()) << std::endl;


}
Y_UDONE()
