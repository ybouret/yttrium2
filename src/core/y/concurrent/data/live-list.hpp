
//! \file

#ifndef Y_Concurrent_Live_List_Included
#define Y_Concurrent_Live_List_Included 1

#include "y/container.hpp"
#include "y/ability/releasable.hpp"
#include "y/core/linked/list.hpp"
#include "y/threading/single-threaded-class.hpp"
#include "y/type/ingress.hpp"

namespace Yttrium
{
    template <typename NODE, typename THREADING_POLICY = SingleThreadedClass>
    class LiveList :
    public Container,
    public Ingress< const Core::ListOf<NODE> >,
    public THREADING_POLICY
    {
    public:
        typedef typename THREADING_POLICY::Lock Lock;
        typedef Core::ListOf<NODE>              ListType;
        typedef NODE                            NodeType;
        Y_ARGS_DECL(typename NodeType::Type,Type);

        inline explicit LiveList() : THREADING_POLICY(), list() {}

        inline virtual ~LiveList() noexcept
        {
            release_();
        }

        inline LiveList(const LiveList &other) : THREADING_POLICY(), list()
        {
            volatile Lock guard(other);
            try {
                for(const NODE *node=other.list.head;node;node=node->next)
                    list.pushTail( NODE::Copy(node) );
            }
            catch(...) { release_(); throw; }
        }

        LiveList & operator=( const LiveList &other )
        {
            volatile Lock self(*this), peer(other);
            LiveList temp(other);
            list.swapListFor(temp.list);
            return *this;
        }

        //! foward display
        inline friend std::ostream & operator<<(std::ostream &os, const LiveList &self)
        {
            return os << self.list;
        }

        inline LiveList & operator<<(ParamType value)
        {
            Y_Must_Lock();
            list.pushTail( NODE::New(value) );
            return *this;
        }

        inline LiveList & operator>>(ParamType value)
        {
            Y_Must_Lock();
            list.pushHead( NODE::New(value) );
            return *this;
        }

        inline void cutHead() noexcept
        {
            Y_Must_Lock();
            assert(list.size>0);
            NODE::Delete(list.popHead());
        }

        inline ConstType pullHead()
        {
            Y_Must_Lock();
            assert(list.head);
            ConstType res = **list.head;
            cutHead();
            return res;
        }

        inline void cutTail() noexcept
        {
            Y_Must_Lock();
            assert(list.size>0);
            NODE::Delete(list.popTail());
        }

        inline ConstType pullTail()
        {
            Y_Must_Lock();
            assert(list.head);
            ConstType res = **list.tail;
            cutTail();
            return res;
        }



        inline virtual size_t size() const noexcept { return list.size; }
        inline virtual void   release()    noexcept { release_(); }

    private:
        ListType list;

        inline virtual const ListType & locus() const noexcept { return list; }

        inline void release_() noexcept
        {
            Y_Must_Lock();
            while(list.size>0) NODE::Delete(list.popTail());
        }
    };
}

#endif
