
//! \file

#ifndef Y_Container_Readable_Included
#define Y_Container_Readable_Included 1

#include "y/container.hpp"
#include "y/type/args.hpp"
#include <iostream>
#include <cassert>

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Readable container interface
    //
    //
    //__________________________________________________________________________
    template <typename T> class Readable : public virtual Container
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        Y_ARGS_EXPOSE(T,Type); //!< aliases

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
    protected:
        //! initialzie
        inline explicit Readable() noexcept : Container() {}

    public:
        //! cleanup
        inline virtual ~Readable() noexcept {}

        //! default display as Julia/Octave.. vector
        inline
        friend std::ostream & operator<<(std::ostream &os, const Readable &self)
        {
            os << LBRACK;
            const size_t n = self.size();
            if(n>0)
            {
                os << self[1];
                for(size_t i=2;i<=n;++i)
                    os << SEMICOLON << self[i];
            }
            return os << RBRACK;
        }

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        //! no throw CONST access
        /**
         \param indx in [1..size()]
         \return const reference
         */
        inline ConstType & operator[](const size_t indx) const noexcept
        {
            assert(indx>0); assert(indx<=size());
            return getItemAt(indx);
        }

    private:
        Y_Disable_Copy_And_Assign(Readable); //!< discarding

    protected:
        //______________________________________________________________________
        //
        //
        // Interface
        //
        //______________________________________________________________________
        //! get item at given index
        /**
         \param indx in [1..size()]
         \return const reference
         */
        virtual ConstType & getItemAt(const size_t indx) const noexcept = 0;
    };

}

#endif

