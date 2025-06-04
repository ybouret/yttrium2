
//! \file

#ifndef Y_Core_Linked_Convert_List_To_Pool_Included
#define Y_Core_Linked_Convert_List_To_Pool_Included 1

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
        //! converting list to pool
        //
        //
        //______________________________________________________________________
        struct ListToPool
        {
            //__________________________________________________________________
            //
            //
            //! one-pass list to pool
            /**
             \param pool an empty Linked::POOL
             \param list a Linked::LIST
             */
            //__________________________________________________________________
            template <typename POOL, typename LIST> static inline
            void Convert(POOL &pool, LIST &list) noexcept
            {
                typedef typename LIST::NodeType NODE;

                assert(0==pool.size);
                assert(0==pool.head);

                switch(list.size)
                {
                    case 0:
                        assert(0==list.head);
                        assert(0==list.tail);
                        return;

                    case 1:
                        assert(0!=list.head); assert(list.tail==list.head);
                        Coerce(pool.head) = list.head;
                        Coerce(pool.size) = 1;
                        goto ZSET_LIST;

                    default:
                        break;
                }

                assert(list.size>=2);
                {
                    NODE * curr = Coerce(pool.head) = list.head;
                    {
                    NEXT:
                        NODE * const next = curr->next;
                        if(0!=next)
                        {
                            next->prev = 0;
                            curr = next;
                            goto NEXT;
                        }
                    }
                    assert(list.tail==curr);
                }
                Coerce(pool.size) = list.size;

            ZSET_LIST:
                Coerce(list.head) = 0;
                Coerce(list.tail) = 0;
                Coerce(list.size) = 0;
            }
        };

    }

}

#endif
