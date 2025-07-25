//! \file

#ifndef Y_Hashing_Perfect_Included
#define Y_Hashing_Perfect_Included 1

#include "y/memory/buffer/ro.hpp"

namespace Yttrium
{

    class OutputStream;
    
    namespace Hashing
    {

        //______________________________________________________________________
        //
        //
        //
        //! Perfect Hashing function based on internal suffix tree
        //
        //
        //______________________________________________________________________
        class Perfect
        {
        public:
            static const char * const CallSign; //!< "Hashing::Perfect"

            explicit Perfect();          //!< setup
            virtual ~Perfect() noexcept; //!< cleanup

            //! register key
            /**
             \param path path
             \param size path size
             \param key  key>0
             */
            void at(const void * const path, const size_t size, const int key);
            void at(const char * const, const int);              //!< wrapper
            void at(const Memory::ReadOnlyBuffer &, const int);  //!< wrapper

            int operator()(const void * const, const size_t) noexcept; //!< \return stored value, <=0 if not
            int operator()(const char * const)               noexcept; //!< \return stored value, <=0 if not
            int operator()(const Memory::ReadOnlyBuffer &)   noexcept; //!< \return stored value, <=0 if not

            int operator()(const void * const, const size_t) const noexcept; //!< \return stored value, <=0 if not, prefetching
            int operator()(const char * const)               const noexcept; //!< \return stored value, <=0 if not, prefetching
            int operator()(const Memory::ReadOnlyBuffer &)   const noexcept; //!< \return stored value, <=0 if not, prefetching

            OutputStream & viz(OutputStream &) const; //!< \return emitted grapvhiz code

        private:
            class Code;
            Y_Disable_Copy_And_Assign(Perfect); //!< discarding
            Code * const code; //!< inner code
        };
    }
}

#endif

