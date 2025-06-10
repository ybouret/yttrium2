//! \file

#ifndef Y_Memory_Operating_Included
#define Y_Memory_Operating_Included 1

#include "y/memory/operative.hpp"
#include "y/type/args.hpp"
#include "y/type/copy-of.hpp"
#include "y/type/procedural.hpp"

namespace Yttrium
{
    namespace Memory
    {

        template <typename T>
        class Operating : public Operative
        {
        public:
            Y_ARGS_EXPOSE(T,Type);

            inline virtual ~Operating() noexcept {}

            //! initialize with default constructor
            inline Operating(void * const entry,
                             const size_t count) :
            Operative(entry, count, sizeof(T), Init0, 0, 0, Quit)
            {
            }


            //! initialize with same parameter
            template <typename ARG>
            inline Operating(const CopyOf_  &,
                             ARG &          arg,
                             void * const   entry,
                             const  size_t  count) :
            Operative(entry, count, sizeof(T), Init1<ARG>, (void*) &arg, 0,Quit)
            {

            }

            //!
            /**
             \param proc proc(target,indexx,args)
             \param args argument for proc
             */
            template <typename PROC, typename ARGS>
            inline Operating(const Procedural_ &,
                             PROC &proc,
                             ARGS &args,
                             void * const entry,
                             const size_t count) :
            Operative(entry, count, sizeof(T), Init2<PROC,ARGS>, (void*) &proc, (void *) &args, Quit)
            {

            }





        private:
            Y_Disable_Copy_And_Assign(Operating);
            static inline
            void Init0(void * const target,
                       void * const,
                       const size_t,
                       void * const)
            {
                assert(0!=target);
                new (target) Type();
            }

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
