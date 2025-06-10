

//! \file

#ifndef Y_Static_Workspace_Multiple_Included
#define Y_Static_Workspace_Multiple_Included 1

#include "y/static/workspace.hpp"
#include "y/container/contiguous.hpp"
#include "y/type/procedural.hpp"
#include "y/memory/operating.hpp"

namespace Yttrium
{
    namespace Static
    {

        template <typename T,size_t N>
        class MultipleProto :
        public Workspace<T,N>,
        public Contiguous<Writable,T>
        {
        public:
            // Definitions
            Y_ARGS_EXPOSE(T,Type);

            // interface
            inline virtual size_t size() const noexcept { return N; }

            // C++
            inline virtual ~MultipleProto() noexcept {}

        protected:
            using Workspace<T,N>::data;
            inline explicit MultipleProto() noexcept :
            Workspace<T,N>(),
            item( data - 1 )
            {
            }

            T * const item; //!< to access item[1..size()]
        private:
            Y_Disable_Copy_And_Assign(MultipleProto);
            inline virtual ConstType & getItemAt(const size_t indx) const noexcept
            {
                assert(indx>0); assert(indx<=N);
                return item[indx];
            }
        };


        template <typename T, size_t N>
        class Multiple :
        public MultipleProto<T,N>,
        public Memory::Operating<T>
        {
        public:
            typedef Memory::Operating<T> Ops;
            using Workspace<T,N>::data;
            
            inline explicit Multiple() : Ops(data,N) {}

            inline virtual ~Multiple() noexcept {}

        private:
            Y_Disable_Copy_And_Assign(Multiple);

        };



    }

}

#endif

