
//! \file

#ifndef Y_Cameo_Multipler_FP_List_Included
#define Y_Cameo_Multipler_FP_List_Included 1

#include "y/cameo/multiplier/synod/fp-unit.hpp"
#include "y/core/linked/list.hpp"

namespace Yttrium
{
    namespace Cameo
    {

        namespace Synod
        {
            template <typename T>
            class FPList : public FPUnit<T>::Cache
            {
            public:
                typedef FPUnit<T>            Unit;
                typedef typename Unit::Cache Cache;
                typedef Core::ListOf<Unit>   UnitList;

                inline explicit FPList() : Cache(), list()
                {
                }

                inline virtual ~FPList() noexcept
                {
                    while(list.size>0) this->remove( list.popTail() );
                }

                inline void free() noexcept {
                    while(list.size) this->banish( list.popTail() );
                }

                
                inline void push(const T &value) {
                    UnitList temp;
                    temp.pushTail( this->summon(value) );
                    insert(temp);
                }

                inline void push(const T &value, size_t n) {
                    UnitList temp;
                    try {
                        while(n-- > 0)
                            temp.pushTail( this->summon(value) );
                        insert(temp);
                    }
                    catch(...)
                    {
                        while(temp.size) this->banish( temp.popTail() );
                        throw;
                    }
                }

                inline const UnitList & operator*() const noexcept { return list; }

                inline T product()
                {
                    if(list.size<=0) return T(0);
                    while(true)
                    {
                        assert(list.size>=2);
                        const T lhs = pullHead();
                        const T rhs = pullTail();
                        const T tmp = lhs * rhs;
                        if(list.size<=0) return tmp;
                        push(tmp);
                    }
                }


            private:
                Y_Disable_Copy_And_Assign(FPList);
                UnitList list;

                inline T  pullHead()
                {
                    assert(list.size>=1);
                    const T res = list.head->data;
                    this->banish( list.popHead() );
                    return res;
                }

                inline T  pullTail()
                {
                    assert(list.size>=1);
                    const T res = list.tail->data;
                    this->banish( list.popTail() );
                    return res;
                }

                inline void insert(Core::ListOf<Unit> &temp) noexcept
                {
                    UnitList target;
                    target.fusion(list,temp,Unit::Compare);
                    assert(0==list.size);
                    assert(0==temp.size);
                    list.swapListFor(target);
                }

            };
        }

    }

}

#endif

