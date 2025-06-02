
//! \file

#ifndef Y_Memory_Workspace_Cxx_Included
#define Y_Memory_Workspace_Cxx_Included 1

#include "y/memory/workspace.hpp"
#include "y/type/args.hpp"
#include "y/type/procedural.hpp"
#include "y/container/writable.hpp"

namespace Yttrium
{
    namespace Memory
    {

#define Y_Cxx_Workspace(CODE) do {\
size_t built = 0;\
try { while(built<Capacity) { CODE; ++built; } } \
catch(...) { releaseUpTo(built); throw; } \
} while(false)

        template <typename T, size_t N=1>
        class CxxWorkspace : public Workspace<T,N>, public Writable<T>
        {
        public:
            typedef Workspace<T,N> WorkspaceType;
            using WorkspaceType::Capacity;
            using WorkspaceType::data;
            using WorkspaceType::item;

            Y_ARGS_DECL(T,Type);


            //! default
            inline explicit CxxWorkspace() : WorkspaceType()
            {
                Y_Cxx_Workspace( new (Coerce(data+built)) Type() );
            }

            template <typename CREATE>
            inline explicit CxxWorkspace(const Procedural_ &, CREATE &create)
            {
                Y_Cxx_Workspace(create(data+built));
            }

            template <typename CREATE>
            inline explicit CxxWorkspace(const Procedural_ &, CREATE &create, size_t offset)
            {
                Y_Cxx_Workspace(create(data+built,offset);++offset);
            }

            

            inline virtual size_t size() const noexcept { return Capacity; }



            inline virtual ~CxxWorkspace() noexcept
            {
                release();
            }

        private:
            Y_Disable_Copy_And_Assign(CxxWorkspace);
            inline void releaseUpTo(size_t built) noexcept
            {
                while(built>0)
                    Coerce( data[--built] ).~MutableType();
            }

            inline void release() noexcept
            {
                releaseUpTo(Capacity);
            }

            inline virtual ConstType & getItemAt(const size_t indx) const noexcept
            {
                assert(indx>0); assert(indx<=Capacity);
                return item[indx];
            }
        };

    }

}

#endif

