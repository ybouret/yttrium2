//! \file

#ifndef Y_Core_Linked_Included
#define Y_Core_Linked_Included 1

#include "y/core/setup.hpp"
#include "y/check/usual.hpp"

namespace Yttrium
{
    namespace Core
    {
        template <typename NODE>
        class Linked
        {
        public:
            typedef NODE NodeType;

            inline explicit Linked() noexcept : size(0), head(0) {}
            inline virtual ~Linked() noexcept {}

            inline bool owns(const NODE * const node) const noexcept
            {
                for(const NODE *mine=head;mine;mine=mine->next)
                {
                    if( node == mine ) return true;
                }
                return false;
            }


            const size_t size;
            NODE *       head;

        protected:
            inline void incr() noexcept { ++Coerce(size); }
            inline void decr() noexcept {
                assert(size>0 || Die("empty Linked") );
                --Coerce(size);
                assert(!(0==size&&0!=head) || Die("empty Linked with head!=NULL"));
            }

        private:
            Y_Disable_Copy_And_Assign(Linked);
        };
    }
}

#endif

