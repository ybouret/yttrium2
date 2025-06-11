
//! \file

#ifndef Y_List_Included
#define Y_List_Included 1

#include "y/container.hpp"
#include "y/memory/io/limbo.hpp"
#include "y/threading/single-threaded-class.hpp"
#include "y/core/linked/list.hpp"

namespace Yttrium
{

    namespace Core
    {
        template <typename T>
        class ListNode
        {
        public:
            Y_ARGS_DECL(T,Type);
            inline  ListNode(ParamType value) : next(0), prev(0), data(value) {}
            inline ~ListNode() noexcept {}

            ListNode *next;
            ListNode *prev;

        private:
            Y_Disable_Copy_And_Assign(ListNode);
            MutableType data;

        };

    }

    template <typename T,typename THREADING_POLICY = SingleThreadedClass>
    class List : public Container
    {
    public:
        inline explicit List();

    private:
        Y_Disable_Copy_And_Assign(List);
    };

}

#endif
