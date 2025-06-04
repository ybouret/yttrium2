
//! \file

#ifndef Y_Memory_Blocks_Included
#define Y_Memory_Blocks_Included 1

#include "y/memory/object/arena.hpp"
#include "y/core/linked/list.hpp"
#include "y/core/linked/pool.hpp"
#include "y/xml/element.hpp"

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
            //! Blocks handle multiple arenas
            //
            //
            //__________________________________________________________________
            class Blocks : public XML::Element
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                static const char * const   CallSign;                              //!< memory object blocks
                static const unsigned       TableSizeLn2 = 5;                      //!< for hash table
                static const size_t         TableSize = size_t(1) << TableSizeLn2; //!< alias
                static const size_t         TableMask = TableSize - 1;             //!< alias
                typedef Core::ListOf<Arena> Slot;                                  //!< alias

                //______________________________________________________________
                //
                //
                //! Arena+next, allocated by knots, stored in kpool
                //
                //______________________________________________________________
                class Knot
                {
                public:
                    typedef Core::PoolOf<Knot> Pool; //!< alias

                    //! setup \param blockSize block size \param pageBytes page size
                    Knot(const size_t blockSize, const size_t pageBytes);

                    //! cleanup
                    ~Knot() noexcept;

                    Arena  arena; //!< actual arena
                    Knot * next; //!< for pool
                private:
                    Y_Disable_Copy_And_Assign(Knot); //!< discarding
                };

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                explicit Blocks(const size_t userPageBytes); //!< setup \param userPageBytes page size hint
                virtual ~Blocks() noexcept;                  //!< cleanup


                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                virtual const char * callSign() const noexcept;
                virtual void         display(std::ostream &, size_t) const;

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! acquire a new block
                /**
                 use caching, look up or new arena
                 \param blockSize
                 \return clean block
                 */
                void * acquire(const size_t blockSize);

                //! release a previously acquired block
                /**
                 use caching or look up
                 \param blockAddr block address
                 \param blockSize block size
                 */
                void   release(void * const blockAddr, const size_t blockSize) noexcept;

                //! get/create specific arena
                /**
                 \warning must lock arena before call to its methods
                 \param blockSize requested block size
                 \return arena with blockSize
                 */
                Arena & getArenaFor(const size_t blockSize);

            private:
                Y_Disable_Copy_And_Assign(Blocks); //!< discarding

                //! return new acquiring
                /**
                 - use knots to create Knot, stored into kpool
                 - arena is stored in table
                 \param blockSize block size
                 \return acquiring pointing to proper arena
                 */
                Arena *        newAcquiring(const size_t blockSize);

                //! look up into table
                /**
                 - use hash of blockSize
                 - applies moveToFront heuristic
                 \param blockSize block size
                 \return proper arena if found, NULL otherwise
                 */
                Arena *        search(const size_t blockSize) noexcept;
                Arena *        acquiring;        //!< last acquiring
                Arena *        releasing;        //!< last releasing
                const unsigned pageShift;        //!< computed pageShift
                const size_t   pageBytes;        //!< 2^pageShift
                Knot::Pool     kpool;            //!< store Knots
                Arena          knots;            //!< tailored memory for Knot
                Slot           table[TableSize]; //!< hash table
            };
        }
    }

}

#endif

