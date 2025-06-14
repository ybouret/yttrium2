

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

        //______________________________________________________________________
        //
        //
        //
        //! Multiple Blocks Prototype
        //
        //
        //______________________________________________________________________
        template <typename T,size_t N>
        class MultipleProto :
        public Workspace<T,N>,
        public Contiguous< Writable<T> >
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_ARGS_EXPOSE(T,Type); //!< aliases

            //__________________________________________________________________
            //
            //
            // interface
            //
            //___________________________________________________________________
            inline virtual size_t size() const noexcept { return N; } //!< \return number of objects

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            inline virtual ~MultipleProto() noexcept {} //!< cleanup

        protected:
            using Workspace<T,N>::data;

            //! setup item from workspace
            inline explicit MultipleProto() noexcept :
            Workspace<T,N>(),
            item( data - 1 )
            {
            }

            T * const item; //!< to access item[1..size()]
        private:
            Y_Disable_Copy_And_Assign(MultipleProto); //!< discarding

            //! [Readable]
            /**
             \param indx in [1:N]
             \return const reference to internal object
             */
            inline virtual ConstType & getItemAt(const size_t indx) const noexcept
            {
                assert(indx>0); assert(indx<=N);
                return item[indx];
            }
        };


        //______________________________________________________________________
        //
        //
        //
        //! Multiple Blocks
        //
        //
        //______________________________________________________________________
        template <typename T, size_t N>
        class Multiple :
        public MultipleProto<T,N>,
        public Memory::Operating<T>
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef Memory::Operating<T> Ops; //!< alias
            using Workspace<T,N>::data;
            
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup with default constructor
            inline explicit Multiple() : Ops(data,N) {}

            //! setup with same argument
            /**
             for each object address=target
             call new (target) T(arg)
             \param copyOf indicator
             \param arg    argument
             */
            template <typename ARG>
            inline explicit Multiple(const CopyOf_ & copyOf,
                                     ARG &          arg) :
            Ops(copyOf,arg,data,N) {}


            //! setup with procedural construction
            /**
             for each object address=target
             call proc(target,indexx=[1:N],args)
             \param procedural indicator
             \param proc  procedure which MUST construct an object
             \param args  arguments
             */
            template <typename PROC, typename ARGS>
            inline explicit Multiple(const Procedural_ & procedural,
                                     PROC &              proc,
                                     ARGS &              args) :
            Ops(procedural,proc,args,data,N)
            {}


            //! cleanup
            inline virtual ~Multiple() noexcept {}

        private:
            Y_Disable_Copy_And_Assign(Multiple); //!< discarding

        };



    }

}

#endif

