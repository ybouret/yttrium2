
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

        //______________________________________________________________________
        //
        //
        //
        //! prototype for CxxWorkspace
        //
        //
        //______________________________________________________________________
        template <typename T, size_t N>
        class CxxWorkspaceProto : public Workspace<T,N>
        {
        public:
            inline virtual ~CxxWorkspaceProto() noexcept {} //!< cleanup

        protected:
            using Workspace<T,N>::data;

            //! setup
            inline explicit CxxWorkspaceProto() noexcept :
            Workspace<T,N>(),
            item( data - 1 )
            {
            }

            T * const item; //!< to access item[1..size()]
        private:
            Y_Disable_Copy_And_Assign(CxxWorkspaceProto); //!< discarding
        };

        //______________________________________________________________________
        //
        //
        //! helper to build workspace
        //
        //______________________________________________________________________
#define Y_Cxx_Workspace(CODE) do {\
size_t built = 0;\
try { while(built<Capacity) { CODE; ++built; } } \
catch(...) { releaseUpTo(built); throw; } \
} while(false)

        //______________________________________________________________________
        //
        //
        //
        //! static workspace
        //
        //
        //______________________________________________________________________
        template <typename T, size_t N=1>
        class CxxWorkspace : public CxxWorkspaceProto<T,N>, public Writable<T>
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef CxxWorkspaceProto<T,N> WorkspaceType; //!< alias
            Y_ARGS_DECL(T,Type);                  //!< aliases
            using WorkspaceType::Capacity;
            using WorkspaceType::data;
            using WorkspaceType::item;


            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            //! setup with default constructor
            inline explicit CxxWorkspace() : WorkspaceType()
            {
                Y_Cxx_Workspace( new (Coerce(data+built)) Type() );
            }

            //! setup with a specific constructor
            /**
             \param create must construct T at given address
             */
            template <typename CREATE>
            inline explicit CxxWorkspace(const Procedural_ &, CREATE &create)
            {
                Y_Cxx_Workspace(create(data+built));
            }

            //! setup with procedural constructor
            /**
             \param create must construct T at given address with offset argument
             \param offset initial offset, increased after each built item
             */
            template <typename CREATE>
            inline explicit CxxWorkspace(const Procedural_ &, CREATE &create, size_t offset)
            {
                Y_Cxx_Workspace(create(data+built,offset);++offset);
            }

            //! cleanup
            inline virtual ~CxxWorkspace() noexcept
            {
                release();
            }

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            inline virtual size_t size() const noexcept { return Capacity; }





        private:
            Y_Disable_Copy_And_Assign(CxxWorkspace); //!< disarding

            //! partial release \param built up to currently built
            inline void releaseUpTo(size_t built) noexcept
            {
                while(built>0)
                    Coerce( data[--built] ).~MutableType();
            }

            //! full release
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

