//! \file

#ifndef Y_Core_Linked_Included
#define Y_Core_Linked_Included 1

#include "y/core/setup.hpp"
#include "y/check/usual.hpp"
#include "y/type/sign.hpp"
#include <iostream>

namespace Yttrium
{
    namespace Core
    {
        struct LinkedInfo
        {
            static const char OwnsNodeMsg[];
            static const char NullNodeMsg[];
            static const char UsedNextMsg[];
            static const char UsedPrevMsg[];
        };

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

            inline friend std::ostream & operator<<( std::ostream &os, const Linked &self)
            {
                os << '[';
                const NODE *node = self.head;
                if(node)
                {
                    os << **node;
                    for(node=node->next;node;node=node->next)
                        os << ';' << **node;
                }
                os << ']';
                return os;
            }

            bool warning(const char * const msg) const noexcept {
                try { std::cerr << msg << std::endl; }
                catch(...) {}
                return false;
            }

            template <typename COMPARE_NODES>
            bool isOrderedAccordingTo(COMPARE_NODES &compareNodes) const
            {
                return true;
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

            
            inline void swapLinkedFor(Linked &other) noexcept
            {
                CoerceSwap(size,other.size);
                CoerceSwap(head,other.head);
            }


        private:
            Y_Disable_Copy_And_Assign(Linked);
        };
    }
}

#endif

