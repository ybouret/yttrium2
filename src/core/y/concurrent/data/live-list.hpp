
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

    //__________________________________________________________________________
    //
    //
    //
    //! list of live objects
    //
    //
    //__________________________________________________________________________
    template <typename NODE, typename THREADING_POLICY = SingleThreadedClass>
    class LiveList :
    public Container,
    public Releasable,
    public Ingress< const Core::ListOf<NODE> >,
    public THREADING_POLICY
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        typedef typename THREADING_POLICY::Lock Lock;        //!< alias
        typedef Core::ListOf<NODE>              ListType;    //!< alias
        typedef NODE                            NodeType;    //!< alias
        typedef Ingress<const ListType>         IngressType; //!< alias
        Y_ARGS_DECL(typename NodeType::Type,Type);           //!< aliases

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup emptu
        inline explicit LiveList() :
        Container(),
        Releasable(),
        IngressType(),
        THREADING_POLICY(),
        list() {}

        //! cleanup
        inline virtual ~LiveList() noexcept { release_(); }

        //! duplicate with NODE::Copy \param other another list
        inline LiveList(const LiveList &other) :
        Container(),
        Releasable(),
        IngressType(),
        THREADING_POLICY(),
        list()
        {
            volatile Lock guard(other);
            try {
                for(const NODE *node=other.list.head;node;node=node->next)
                    list.pushTail( NODE::Copy(node) );
            }
            catch(...) { release_(); throw; }
        }

        //! assign with copy/swap \param other another list \return *this*
        LiveList & operator=( const LiveList &other )
        {
            volatile Lock self(*this), peer(other);
            LiveList temp(other);
            list.swapListFor(temp.list);
            return *this;
        }

        //! foward display
        /**
         \param os output stream
         \param self *this
         \return os << self.list
         */
        inline friend std::ostream & operator<<(std::ostream &os, const LiveList &self)
        {
            return os << self.list;
        }


        //! push tail \param value new appended value \return *this
        inline LiveList & operator<<(ParamType value)
        {
            Y_Must_Lock();
            list.pushTail( NODE::New(value) );
            return *this;
        }

        //! push head \param value new prepended value \return *this
        inline LiveList & operator>>(ParamType value)
        {
            Y_Must_Lock();
            list.pushHead( NODE::New(value) );
            return *this;
        }


        //! pop and delete head with NODE::Deletes
        inline void cutHead() noexcept
        {
            Y_Must_Lock();
            assert(list.size>0);
            NODE::Delete(list.popHead());
        }

        //! pop and delete head \return old head value
        inline ConstType pullHead()
        {
            Y_Must_Lock();
            assert(list.head);
            ConstType res = **list.head;
            cutHead();
            return res;
        }

        //! pop and delete tail with NODE::Delete
        inline void cutTail() noexcept
        {
            Y_Must_Lock();
            assert(list.size>0);
            NODE::Delete(list.popTail());
        }

        //! pop and delete tail \return old tail value
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
        ListType list; //!< my list

        inline virtual const ListType & locus() const noexcept { return list; }

        //! release all nodes with NODE::Delete
        inline void release_() noexcept
        {
            Y_Must_Lock();
            while(list.size>0) NODE::Delete(list.popTail());
        }
    };
}

#endif
