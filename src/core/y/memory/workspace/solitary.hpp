
//! \file

#ifndef Y_Memory_Workspace_Cxx_Included
#define Y_Memory_Workspace_Cxx_Included 1

#include "y/memory/workspace.hpp"
#include "y/type/args.hpp"

namespace Yttrium
{
    namespace Memory
    {

        template <typename T>
        class Solitary : public Workspace<T,1>
        {
        public:
            Y_ARGS_EXPOSE(T,Type);
            typedef Workspace<T,1> WorkspaceType;
            using   WorkspaceType::data;

        protected:
            inline explicit Solitary() noexcept : WorkspaceType() {}
        public:
            inline virtual ~Solitary() noexcept {}

            inline ConstType & operator*() const noexcept { return *data; }
            inline Type &      operator*()       noexcept { return *data; }


        private:
            Y_Disable_Copy_And_Assign(Solitary);
        };

    }

}

#endif

