
//! \file

#ifndef Y_Memory_Workspace_Cxx_Included
#define Y_Memory_Workspace_Cxx_Included 1

#include "y/memory/management/workspace.hpp"
#include "y/type/args.hpp"

namespace Yttrium
{
    namespace Memory
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
        protected:
            inline explicit Solitary() noexcept : WorkspaceType() {} //!< setup
        public:
            inline virtual ~Solitary() noexcept {}                   //!< cleanup

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

