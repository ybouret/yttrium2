
//! \file

#ifndef Y_Memory_Object_Guild_Included
#define Y_Memory_Object_Guild_Included 1

#include "y/ability/lockable.hpp"

namespace Yttrium
{
    namespace Memory
    {
        namespace Object
        {

            //__________________________________________________________________
            //
            //
            //
            //! dedicated Arena with autolocking from Factory
            //
            //
            //__________________________________________________________________
            class Guild
            {
            public:
                class Code;

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                explicit Guild(const size_t userBlockSize); //!< setup \param userBlockSize fixed block size
                virtual ~Guild() noexcept;                  //!< cleanup

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                size_t blockSize() const noexcept;          //!< \return internal block size
                void * acquireBlock();                      //!< \return a new block
                void   releaseBlock(void * const) noexcept; //!< release a previously acquired block

            private:
                Y_Disable_Copy_And_Assign(Guild); //!< discarding
                Code * const code;                //!< access+arena
            };

            
        }
    }

}

#endif

