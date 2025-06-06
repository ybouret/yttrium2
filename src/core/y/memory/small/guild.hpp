
//! \file

#ifndef Y_Memory_Object_Guild_Included
#define Y_Memory_Object_Guild_Included 1

#include "y/ability/lockable.hpp"
#include "y/type/ingress.hpp"

namespace Yttrium
{
    namespace Memory
    {
        namespace Small
        {

            //__________________________________________________________________
            //
            //
            //
            //! dedicated Arena with autolocking from Blocks
            //
            //
            //__________________________________________________________________
            class Guild : public Ingress<Lockable>
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
                size_t getBlockSize() const noexcept;       //!< \return internal block size
                void * acquireBlock();                      //!< locked \return a new block
                void   releaseBlock(void * const) noexcept; //!< unlocked release of a previous block

                void  *acquireBlockUnlocked();                      //!< unlocked \return new block
                void   releaseBlockUnlocked(void * const) noexcept; //!< unlocked release of a previous block


            private:
                Y_Disable_Copy_And_Assign(Guild); //!< discarding
                Y_Ingress_Decl();                 //!< interface
                Code * const code;                //!< access+arena
            };

            
        }
    }

}

#endif

