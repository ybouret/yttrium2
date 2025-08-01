

//! \file

#ifndef Y_Protean_HeavyNode_Included
#define Y_Protean_HeavyNode_Included 1

#include "y/type/args.hpp"

namespace Yttrium
{

    namespace Protean
    {

        //______________________________________________________________________
        //
        //
        //
        //! node with full object inside
        //
        //
        //______________________________________________________________________
        template <typename T>
        class HeavyNode
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Declare(T,Type); //!< aliases

            //! check that two objects are the same
            /**
             \param lhs first  arg
             \param rhs second arg
             \return lhs == rhs
             */
            static inline bool Same(ParamType lhs, ParamType rhs)
            {
                return lhs == rhs;
            }

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! build with inner object \param arg passed to data constructor
            inline HeavyNode(ParamType arg) noexcept :
            next(0), prev(0), data(arg)
            {
            }

            //! cleanup
            inline ~HeavyNode() noexcept {}

            //! duplicate \param node another node
            inline HeavyNode(const HeavyNode &node)  :
            next(0), prev(0), data(node.data)
            {
            }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            inline Type &      operator*()       noexcept { return data; } //!< access \return content
            inline ConstType & operator*() const noexcept { return data; } //!< CONST access \return content

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            HeavyNode * next; //!< for list
            HeavyNode * prev; //!< for list
        private:
            MutableType data; //!< full object

            Y_Disable_Assign(HeavyNode); //!< discarding
        };


    }
}

#endif

