//! \file

#ifndef Y_Memory_Object_Factory_Included
#define Y_Memory_Object_Factory_Included 1

#include "y/object.hpp"
#include "y/singleton.hpp"
#include "y/concurrent/singleton/class-lock-policy.hpp"
#include "y/calculus/integer-log2.hpp"

namespace Yttrium
{
    namespace Memory
    {
        class Pooled;

        namespace Object
        {

#if 0
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
                static const size_t   CONDENSATION_BYTES = 4;                                      //!< decrease complexity
                static const unsigned CONDENSATION_SHIFT = IntegerLog2<CONDENSATION_BYTES>::Value; //!< ensure power of two
                static const size_t   MEDIUM_LIMIT_BYTES;                                          //!< Segment::MaxSizeFor(DEFAULT_PAGE_SHIFT)

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

                //! auto-locked acquisition through Arena
                /**
                 \param blockSize POSITIVE block size
                 \return memory of EXACT blockSize, clean
                 */
                void * acquireBlock(const size_t blockSize);

                //! auto-locked release through Arena
                /**
                 \param blockAddr  previously acquired memory
                 \param blockSize block size
                 */
                void   releaseBlock(void * const blockAddr, const size_t blockSize) noexcept;

                //! use pooled allocator
                /**
                 \param blockSize POSITIVE block size
                 \return memory with >= blockSize bytes
                 */
                void   * acquireJoint(const size_t blockSize);

                //! use pooled allocator
                /**
                 \param blockAddr previously acquired memory
                 \param blockSize its block size
                 */
                void   releaseJoint(void * const blockAddr, const size_t blockSize) noexcept;


                void * acquireQuanta(const unsigned shift);
                void   releaseQuanta(const unsigned shift, void * const entry) noexcept;

                void * acquire(const size_t blockSize);
                void   release(void * const blockAddr, const size_t blockSize) noexcept;



                //! helper to generate no-arg object in two stages
                /**
                 \return a constructed object from inner arena memory
                 */
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

                //! helper to delete a created object
                /**
                 \param object pointer to createdBlockAs<T>(...) object
                 */
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
                const size_t * const condensation;
                Pooled &             pooled;

            };
#endif
        }
    }
}

#endif

