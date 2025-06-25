
//! \file

#ifndef Y_Protean_LightNode_Included
#define Y_Protean_LightNode_Included 1

#include "y/type/args.hpp"

namespace Yttrium
{
    
    namespace Protean
    {
        //______________________________________________________________________
        //
        //
        //
        //! node with only reference to PERSISTENT object
        //
        //
        //______________________________________________________________________
        template <typename T>
        class LightNode
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Expose(T,Type);         //!< alias
            typedef ConstType & ParamType; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param arg will be internal inner reference
            inline LightNode(ParamType arg) noexcept :
            next(0), prev(0), data( (MutableType &)arg )
            {
            }

            //! cleanup
            inline ~LightNode() noexcept {}

            //! duplicate \param node another node
            inline LightNode(const LightNode &node) noexcept :
            next(0), prev(0), data(node.data)
            {
            }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            inline Type &      operator*()       noexcept { return data; } //!< access \return referenced object
            inline ConstType & operator*() const noexcept { return data; } //!< CONST access \return referenced object


            LightNode * next; //!< for list
            LightNode * prev; //!< for list

        private:
            MutableType &data; //!< reference to PERSISTENT object
            Y_Disable_Assign(LightNode); //!< discarding
        };
    }
}

#endif

