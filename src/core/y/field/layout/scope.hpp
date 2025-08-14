
//! \file

#ifndef Y_Field_Layout_Scope_Included
#define Y_Field_Layout_Scope_Included 1

#include "y/memory/stealth.hpp"
#include "y/type/shallow.hpp"

namespace Yttrium
{

    namespace Field
    {

        Y_Shallow_Decl(SubLayout); //!< helper

        //______________________________________________________________________
        //
        //
        //
        //! providing Zero Coord[1|2|3|4]D
        //
        //
        //______________________________________________________________________
        struct ZeroCount
        {
            //! \return fixed, pseudo zeroe coordinates
            template <typename T> static inline
            const T & Value() noexcept {
                assert( sizeof(T) <= Bytes() );
                return *static_cast<const T *>( Entry() );
            }

            static size_t       Bytes() noexcept; //!< \return inner bytes
            static const void  *Entry() noexcept; //!< \return inner entry
        };

        //______________________________________________________________________
        //
        //
        //
        //! Layout width and shift
        //
        //
        //______________________________________________________________________
        template <typename COUNT> class LayoutScope
        {
        public:
            typedef COUNT CountType; //!< alias

        protected:
            //! zero setup
            inline explicit LayoutScope() noexcept : 
            width( ZeroCount::Value<COUNT>() ),
            shift( ZeroCount::Value<COUNT>() )
            {}

            //! copy \param other another layout scope
            inline explicit LayoutScope(const LayoutScope &other) noexcept :
            width(other.width),
            shift(other.shift)
            {}

            //! sub-scope \param super super scope
            template <typename SUPER> inline
            explicit LayoutScope(const SubLayout_ &, const SUPER &super) noexcept :
            width( Memory::Stealth::Conv<const CountType,const typename SUPER::CountType>(super.width) ),
            shift( Memory::Stealth::Conv<const CountType,const typename SUPER::CountType>(super.shift) )
            {
            }


        public:
            //! cleanup
            inline virtual ~LayoutScope() noexcept {
                Y_Memory_VZero( Coerce(width) );
                Y_Memory_VZero( Coerce(shift) );
            }

            //! \return items from last shift coordinate
            inline size_t lastShift() const noexcept
            {
                static const size_t DIM = sizeof(COUNT)/sizeof(size_t);
                return * (Memory::Stealth::Cast<const size_t>(&shift) + (DIM-1));
            }

            const COUNT width; //!< the width
            const COUNT shift; //!< shift per dimension

        private:
            Y_Disable_Assign(LayoutScope); //!< discarding
        };
    }

}
#endif

