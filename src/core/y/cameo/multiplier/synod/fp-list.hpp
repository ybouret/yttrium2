
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
            //__________________________________________________________________
            //
            //
            //
            //! Ordered List + Cache of FPUnit
            //
            //
            //__________________________________________________________________
            template <typename T>
            class FPList : public FPUnit<T>::Cache
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef FPUnit<T>            Unit;     //!< alias
                typedef typename Unit::Cache Cache;    //!< alias
                typedef Core::ListOf<Unit>   UnitList; //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup
                inline explicit FPList() : Cache(), list()
                {
                }

                //! cleanup
                inline virtual ~FPList() noexcept
                {
                    while(list.size>0) this->remove( list.popTail() );
                }

                //! free content, keep memory
                inline void free() noexcept {
                    while(list.size) this->banish( list.popTail() );
                }


                //! \param value pushed in ordered position
                inline void push(const T &value) {
                    UnitList temp;
                    temp.pushTail( this->summon(value) );
                    insert(temp);
                }

                //! \param value pushed in ordered position \param n number of copies
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

                //! \return internal list, mostly for debug
                inline const UnitList & operator*() const noexcept { return list; }

                //! \return product algorithm
                inline T product()
                {
                    if(list.size<=0) return T(1);
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
                Y_Disable_Copy_And_Assign(FPList); //!< discarding
                UnitList list; //!< all unit to make product of

                //! \return lowest exponent value
                inline T  pullHead()
                {
                    assert(list.size>=1);
                    const T res = list.head->data;
                    this->banish( list.popHead() );
                    return res;
                }

                //! \return highest exponent value
                inline T  pullTail()
                {
                    assert(list.size>=1);
                    const T res = list.tail->data;
                    this->banish( list.popTail() );
                    return res;
                }

                //! \param temp temporary list, merged within list
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

