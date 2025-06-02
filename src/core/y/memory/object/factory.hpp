//! \file

#ifndef Y_Memory_Object_Factory_Included
#define Y_Memory_Object_Factory_Included 1

#include "y/singleton.hpp"
#include "y/concurrent/singleton/broad-lock-policy.hpp"
#include "y/memory/object/factory/api.hpp"

namespace Yttrium
{
    namespace Memory
    {
        namespace Object
        {

            class Guild;


            //__________________________________________________________________
            //
            //
            //
            //! Factory of objects for any kind of (locked) allocation
            //
            //
            //__________________________________________________________________
            class Factory : public FactoryAPI, public Singleton<Factory,BroadLockPolicy>
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                static const size_t PAGE_BYTES = 1000; //!< default page size

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                virtual void display(std::ostream &,size_t) const;

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! auto-locked acquisition through arena
                /**
                 \param blockSize block size
                 \return block address, clean
                 */
                void * acquireBlock(const size_t blockSize);

                //! auto-locked release through arena
                /**
                 \param blockAddr  previously acquired memory
                 \param blockSize block size
                 */
                void   releaseBlock(void * const blockAddr, const size_t blockSize) noexcept;

                //! alias to acquire a zombi block \return memory for one 'T'
                template <typename T> inline
                T *acquireBlockFor() { return static_cast<T *>(acquireBlock(sizeof(T))); }


                //! alias to release a zombi block \param zombi previously acquired block
                template <typename T> inline
                void releaseBlockFor( T * const zombi ) { releaseBlock(zombi,sizeof(T)); }



            private:
                Y_Disable_Copy_And_Assign(Factory); //!< discarding

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                explicit Factory();          //!< setup
                virtual ~Factory() noexcept; //!< cleanup

                friend class Singleton<Factory,BroadLockPolicy>;
                friend class Guild;
            };
        }
    }
}

#endif

