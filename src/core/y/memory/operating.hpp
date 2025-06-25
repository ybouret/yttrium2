//! \file

#ifndef Y_Memory_Operating_Included
#define Y_Memory_Operating_Included 1

#include "y/memory/operative.hpp"
#include "y/type/args.hpp"
#include "y/type/copy-of.hpp"
#include "y/type/procedural.hpp"
#include <cassert>

namespace Yttrium
{
    namespace Memory
    {

        //______________________________________________________________________
        //
        //
        //
        //! Operating for blocks of T
        //
        //
        //______________________________________________________________________
        template <typename T>
        class Operating : public Operative
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Expose(T,Type); //!< aliases

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! cleanup
            inline virtual ~Operating() noexcept {}

            //! initialize with default constructor
            /**
             \param entry address of the with object
             \param count number of objects to create
             */
            inline Operating(void * const entry,
                             const size_t count) :
            Operative(entry, count, sizeof(T), Init0, 0, 0, Quit)
            {
            }


            //! initialize with same parameter
            /**
             call new (target) T(arg) for each object
             \param arg the argument
             \param entry address of first object
             \param count number of objects to build
             */
            template <typename ARG>
            inline Operating(const CopyOf_  &,
                             ARG &          arg,
                             void * const   entry,
                             const  size_t  count) :
            Operative(entry, count, sizeof(T), Init1<ARG>, (void*) &arg, 0,Quit)
            {

            }

            //! initialize with procedure
            /**
             \param proc  proc(target,indexx,args) create a procedural object @ target
             \param args  argument for proc
             \param entry address of first object
             \param count number of objects to build
             */
            template <typename PROC, typename ARGS>
            inline Operating(const Procedural_ &,
                             PROC &       proc,
                             ARGS &       args,
                             void * const entry,
                             const size_t count) :
            Operative(entry, count, sizeof(T), Init2<PROC,ARGS>, (void*) &proc, (void *) &args, Quit)
            {

            }

            //! initialize by duplication
            /**
             \param entry address of first target object
             \param other address of first source object
             \param count objects to build
             */
            template <typename U>
            inline Operating(void    * const entry,
                             const U * const other,
                             const size_t    count) :
            Operative(entry,count,sizeof(T), XCopy<U>, (void*)other, 0, Quit)
            {
            }


            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
        private:
            Y_Disable_Copy_And_Assign(Operating); //!< discardin

            //! simple constructor
            /**
             \param target address to place the new object
             */
            static inline
            void Init0(void * const target,
                       void * const,
                       const size_t,
                       void * const)
            {
                assert(0!=target);
                new (target) Type();
            }

            //! constructor with one argument
            /**
             new (target) Type(arg)
             \param target address to place the new object
             \param source address of the argument
             */
            template <typename ARG> static inline
            void Init1(void * const target,
                       void * const source,
                       const size_t,
                       void * const)
            {
                assert(0!=target);
                assert(0!=source);
                ARG &arg = *(ARG *)source;
                new (target) Type(arg);
            }

            //! procedural constructor
            /**
             proc(target,indexx,args)
             \param target address to place the new object
             \param source address of the procedure
             \param indexx [1..count] indexing
             \param params address of the argument
             */
            template <typename PROC, typename ARGS> static inline
            void Init2(void * const target,
                       void * const source,
                       const size_t indexx,
                       void * const params)
            {
                assert(0!=target);
                assert(0!=source);
                assert(0!=params);
                PROC & proc = *(PROC *)source;
                ARGS & args = *(ARGS *)params;
                proc(target,indexx,args);
            }

            //! procedural copy
            /**
             \param target
             \param source
             \param indexx [1..count] indexing
             */
            template <typename U> static inline
            void XCopy(void * const target,
                       void * const source,
                       const size_t indexx,
                       void * const  )
            {
                assert(0!=target);
                assert(0!=source);
                const U * const src = static_cast<const U *>(source)-1;
                new (target) Type(src[indexx]);
            }


            //! destructor wrapper
            /**
             \param addr address of internal object
             */
            static inline
            void Quit(void * const addr) noexcept
            {
                assert(0!=addr);
                static_cast<MutableType *>(addr)->~MutableType();
            }
        };
    }

}

#endif
