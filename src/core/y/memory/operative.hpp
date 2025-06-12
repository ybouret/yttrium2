
//! \file

#ifndef Y_Memory_Operative_Included
#define Y_Memory_Operative_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Memory
    {

        //______________________________________________________________________
        //
        //
        //
        //! generic construction/destruction of objects on memory
        //
        //
        //______________________________________________________________________
        class Operative
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________

            //! generic object constructor
            typedef void (*InitProc)(void * const target,
                                     void * const source,
                                     const size_t indexx,
                                     void * const params);

            //! object destructor wrapper
            typedef void (*QuitProc)(void * const target);

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! initialize
            /**
             for each address, call onInit(target,source,indexx,params)
             with indexx in [1:count]
             \param entry  base address
             \param count  number of objects to build
             \param width  bytes per object
             \param onInit generic constructor
             \param source source for onInit
             \param params params for onInit
             \param onQuit destructor for each object
             */
            explicit Operative(void * const       entry,
                               const size_t       count,
                               const size_t       width,
                               InitProc const     onInit,
                               void * const       source,
                               void * const       params,
                               QuitProc const     onQuit);

            //! cleanup
            virtual ~Operative() noexcept;

            uint8_t * const workspace; //!< first byte of first object
            const size_t    numBlocks; //!< number of objects
            const size_t    blockSize; //!< bytes per object

        private:
            Y_Disable_Copy_And_Assign(Operative); //!< discarding
            QuitProc const  quit;                 //!< saved destructor function
            void release_() noexcept;             //!< destruct all objects

        };
    }

}

#endif
