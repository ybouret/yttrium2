

//! \file

#ifndef Y_Protean_SoloHeavList_Included
#define Y_Protean_SoloHeavytList_Included 1

#include "y/protean/solo/list.hpp"
#include "y/protean/node/heavy.hpp"
#include "y/container/sequence.hpp"
#include "y/type/with-at-least.hpp"

namespace Yttrium
{


    template <typename T, typename ThreadingPolicy = SingleThreadedClass>
    class List : public Protean::SoloList< Protean::HeavyNode<T>,Sequence<T,Protean::CommonContainer>,ThreadingPolicy>
    {
    public:
        typedef Protean::HeavyNode<T>                                    NodeType;
        typedef Sequence<T,Protean::CommonContainer>                     SequenceType;
        typedef Protean::SoloList<NodeType,SequenceType,ThreadingPolicy> BaseType;
        using BaseType::pool;

        inline explicit List() : BaseType() {}
        inline virtual ~List() noexcept {}
        inline List(const List &other) : BaseType(other)
        {
        }

        inline List(const WithAtLeast_ &, const size_t n) : BaseType()
        {
            pool.cache(n);
        }


    private:
        Y_Disable_Assign(List);

    };
 

}

#endif
