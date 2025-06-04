
//! \file

#ifndef Y_Core_Linked_Convert_Pool_To_List_Included
#define Y_Core_Linked_Convert_Pool_To_List_Included 1

#include "y/core/setup.hpp"
#include <cassert>

namespace Yttrium
{
    namespace Core
    {

        //______________________________________________________________________
        //
        //
        //
        //! converting pool to list
        //
        //
        //______________________________________________________________________
        struct PoolToList
        {
            //__________________________________________________________________
            //
            //
            //! one-pass pool to list
            /**
             \param list an empty Linked::LIST
             \param pool a Linked::POOL
             */
            //__________________________________________________________________
            template <typename LIST, typename POOL> static inline
            void Convert(LIST &list, POOL &pool) noexcept
            {
                typedef typename POOL::NodeType NODE;
                assert(0==list.size);
                assert(0==list.head);
                assert(0==list.tail);

                switch(pool.size)
                {
                    case 0: assert(0==pool.head); return;
                    case 1:
                        Coerce(list.head) = Coerce(list.tail) = pool.head;
                        Coerce(list.size) = 1;
                        goto ZSET_POOL;

                    default:
                        break;
                }
                assert(pool.size>=2);
                {

                    NODE *       curr = Coerce(list.head) = pool.head;
                NEXT:
                    {
                        NODE * const next = curr->next;
                        if(0!=next)
                        {
                            next->prev = curr;
                            curr = next;
                            goto NEXT;
                        }
                        assert(0==next);
                    }
                    assert(0!=curr);
                    Coerce(list.tail) = curr;
                    Coerce(list.size) = pool.size;
                }

            ZSET_POOL:
                Coerce(pool.head) = 0;
                Coerce(pool.size) = 0;
                return;
            }

        };

    }

}

#endif

