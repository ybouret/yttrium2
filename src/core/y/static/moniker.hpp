// !\file

#ifndef Y_Type_Moniker_Included
#define Y_Type_Moniker_Included 1

#include "y/type/args.hpp"
#include "y/calculus/alignment.hpp"
#include "y/memory/stealth.hpp"
#include "y/type/copy-of.hpp"
#include "y/type/destruct.hpp"

namespace Yttrium
{

    namespace Static
    {
        //__________________________________________________________________________
        //
        //
        //
        //! forcing type to aligned boundaries
        //
        //
        //__________________________________________________________________________
        template <typename T>
        class Moniker
        {
        public:
            //______________________________________________________________________
            //
            //
            // Definitions
            //
            //______________________________________________________________________
            Y_ARGS_DECL(T,Type); //!< aliases
            
            //______________________________________________________________________
            //
            //
            // C++
            //
            //______________________________________________________________________
            
            //! setup with default constructor
            inline Moniker() :
            wksp(), data( new ( Y_Memory_BZero(wksp) ) MutableType() )
            {
            }
            
            //! cleanup
            inline ~Moniker() noexcept
            {
                Memory::Stealth::Zero( Destructed(data), sizeof(wksp) );
            }
            
            //! setup with given argument \param arg parameter type
            inline Moniker(ParamType arg) :
            wksp(), data( new ( Y_Memory_BZero(wksp) ) MutableType(arg) )
            {
            }
            
            //! duplicate \param other another moniker
            inline Moniker(const Moniker &other) :
            wksp(),
            data( new ( Y_Memory_BZero(wksp) ) MutableType(*other) )
            {
            }
            
            //! setup with a copy of any argument \param arg any valid argument
            template <typename ARG>
            inline Moniker(const CopyOf_ &, ARG &arg) :
            wksp(),
            data( new ( Y_Memory_BZero(wksp) ) MutableType(arg) )
            {
            }
            
            //! forward display
            /**
             \param os output stream
             \param self moniker
             \return os
             */
            inline friend
            std::ostream & operator<<(std::ostream &os, const Moniker &self)
            {
                return os << *self;
            }
            
            //______________________________________________________________________
            //
            //
            // Methos
            //
            //______________________________________________________________________
            
            //! const access \return const internal data
            inline ConstType & operator*() const noexcept { assert(0!=data); return *data; }
            
            //! access \return internal data
            inline Type      & operator*()       noexcept { assert(0!=data); return *data; }
            
            
            
        private:
            Y_Disable_Assign(Moniker);                                    //!< discarding
            void *              wksp[ Alignment::WordsFor<Type>::Count ]; //!< aligned memory
            MutableType * const data;                                     //!< alias
            
        };
        
    }
}

#endif

