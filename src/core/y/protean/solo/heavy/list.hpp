

//! \file

#ifndef Y_Protean_SoloHeavyList_Included
#define Y_Protean_SoloHeavyList_Included 1

#include "y/protean/solo/list.hpp"
#include "y/protean/node/heavy.hpp"
#include "y/container/sequence.hpp"
#include "y/type/with-at-least.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! specific Protean List
    //
    //
    //__________________________________________________________________________
    template <typename T, typename ThreadingPolicy = SingleThreadedClass>
    class List : public Protean::SoloList< Protean::HeavyNode<T>,Sequence<T,Protean::CommonContainer>,ThreadingPolicy>
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        typedef Protean::HeavyNode<T>                                    NodeType;     //!< alias
        typedef Sequence<T,Protean::CommonContainer>                     SequenceType; //!< alias
        typedef Protean::SoloList<NodeType,SequenceType,ThreadingPolicy> BaseType;     //!< alias
        using BaseType::pool;


        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        inline explicit List() : BaseType() {} //!< setup emtpy
        inline virtual ~List() noexcept {}     //!< cleanup

        //! duplicate \param other another list
        inline List(const List &other) : BaseType(other)
        {
        }

        //! setup with capacity \param n memory for objects
        inline List(const WithAtLeast_ &, const size_t n) : BaseType()
        {
            pool.cache(n);
        }


    private:
        Y_Disable_Assign(List); //!< discarding

    };
 

}

#endif
