

//! \file

#ifndef Y_Static_Workspace_Solitary_Included
#define Y_Static_Workspace_Solitary_Included 1

#include "y/static/workspace.hpp"
#include "y/type/args.hpp"
#include "y/type/destruct.hpp"

namespace Yttrium
{
    namespace Static
    {

        //______________________________________________________________________
        //
        //
        //
        //! 1-item workspace with access operator
        /**
         must be constructed/destructed by derived class
         */
        //
        //______________________________________________________________________
        template <typename T>
        class Solitary : public Workspace<T,1>
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_ARGS_EXPOSE(T,Type);                //!< aliases
            typedef Workspace<T,1> WorkspaceType; //!< alias
            using   WorkspaceType::data;

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup with default
            inline explicit Solitary()  :
            WorkspaceType()
            {
                new (data) MutableType();
            }

            template <typename ARG>
            inline explicit Solitary(ARG &arg) :
            WorkspaceType()
            {
                new (data) MutableType(arg);
            }

            inline virtual ~Solitary() noexcept
            {
                Destruct(data);
            }

            inline friend std::ostream & operator<<(std::ostream &os, const Solitary &self)
            {
                return os << *self.data;
            }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            inline ConstType & operator*() const noexcept { return *data; } //!< \return CONST content
            inline Type &      operator*()       noexcept { return *data; } //!< \return content


        private:
            Y_Disable_Copy_And_Assign(Solitary); //!< discarding
        };

    }

}

#endif

