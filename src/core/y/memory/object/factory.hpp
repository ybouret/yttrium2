//! \file

#ifndef Y_Memory_Object_Factory_Included
#define Y_Memory_Object_Factory_Included 1

#include "y/singleton.hpp"
#include "y/concurrent/singleton/broad-lock-policy.hpp"
#include "y/memory/object/factory/api.hpp"
#include "y/calculus/integer-log2.hpp"

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
                static const size_t   DEFAULT_PAGE_BYTES = 4096;                                   //!< default page size
                static const unsigned DEFAULT_PAGE_SHIFT = IntegerLog2<DEFAULT_PAGE_BYTES>::Value; //!< ensure power of two
                static const size_t   LIMIT_OBJECT_BYTES = 512;                                    //!< limit size
                static const unsigned LIMIT_OBJECT_SHIFT = IntegerLog2<LIMIT_OBJECT_BYTES>::Value; //!< ensure power of two
                
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

                
                template <typename T> inline
                T * createBlockAs() {
                    void * const p = acquireBlock(sizeof(T));
                    try {
                        return new (p) T();
                    }
                    catch(...)
                    {
                        releaseBlock(p,sizeof(T));
                        throw;
                    }
                }

                template <typename T> inline
                void deleteBlockAs(T * &object) noexcept
                {
                    assert(0!=object);
                    object->~T();
                    releaseBlock(object,sizeof(T));
                    object = 0;
                }



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

