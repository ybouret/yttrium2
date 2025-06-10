
//! \file

#ifndef Y_Concurrent_Live_List_Included
#define Y_Concurrent_Live_List_Included 1

#include "y/core/linked/list.hpp"
#include "y/type/ingress.hpp"
#include "y/ability/releasable.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        //! dynamic New/Delete/Copy...
        template <typename NODE>
        class LiveList :
        public Ingress< Core::ListOf<NODE> >,
        public Releasable
        {
        public:
            typedef Core::ListOf<NODE> CoreList;
            typedef Ingress<CoreList>  CoreListAPI;
            typedef NODE NodeType;
            Y_ARGS_DECL(typename NodeType::Type,Type);

            explicit LiveList() noexcept : CoreListAPI(), my() {}
            virtual ~LiveList() noexcept { release_(); }

            inline LiveList(const LiveList &other) : CoreListAPI(), my()
            {
                try {
                    for(const NodeType *node=other->head;node;node=node->next)
                    {
                        my.pushTail( NodeType::Copy(node) );
                    }
                }
                catch(...)
                {
                    release_(); throw;
                }
            }

            virtual void release() noexcept
            {
                release_();
            }

            inline LiveList & operator<<(ParamType value) {
                (void) my.pushTail( NodeType::New(value) );
                return *this;
            }

            inline LiveList & operator>>(ParamType value) {
                (void) my.pushHead( NodeType::New(value) );
                return *this;
            }


        private:
            Y_Disable_Assign(LiveList);
            CoreList my;

            typename CoreListAPI::ConstInterface & locus() const noexcept { return my; }

            inline void release_() noexcept
            {
                while(my.size>0)
                {
                    NodeType::Delete(my.popTail());
                }

            }
        };

    }
}

#endif
