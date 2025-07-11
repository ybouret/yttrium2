

//! \file

#ifndef Y_Static_Workspace_Solitary_Included
#define Y_Static_Workspace_Solitary_Included 1

#include "y/static/workspace.hpp"
#include "y/type/args.hpp"

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
            Y_Args_Expose(T,Type);                //!< aliases
            typedef Workspace<T,1> WorkspaceType; //!< alias
            using   WorkspaceType::data;

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

        protected:
            //! setup  blank
            inline explicit Solitary()  :
            WorkspaceType()
            {
            }


        public:
            //! cleanup
            inline virtual ~Solitary() noexcept
            {
            }

            //! display
            /**
             \param os output stream
             \param self from derived class
             \return os
             */
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

