
#ifndef Y_Ink_Broker_Included
#define Y_Ink_Broker_Included 1

#include "y/ink/area.hpp"
#include "y/concurrent/divide/2d.hpp"
#include "y/concurrent/api/simd/spawn.hpp"

namespace Yttrium
{
    namespace Ink
    {

        typedef Concurrent::Divide::Tiles2D<unit_t> Tiles;  //!< alias
        typedef Tiles::Tile                         Tile;   //!< alias
        typedef Tiles::BoxType                      Box;    //!< alias
        typedef Concurrent::Spawn<Tiles>            Tiling; //!< alias

        //______________________________________________________________________
        //
        //
        //
        //! prepare concurrent operations for a given area
        //
        //
        //______________________________________________________________________
        class Broker : public Tiling
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup for specific
            /**
             \param proc shared processor
             \param area fixed user's area
             */
            explicit Broker(const Concurrent::Processor &proc,
                            const Area                  &area);

            //! setup with empty tiles
            /**
             \param proc shared processor
             */
            explicit Broker(const Concurrent::Processor &proc);


            //! cleanup
            virtual ~Broker() noexcept;


            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! prepare for area with local memory conservation
            void     prep(const Area &);


        private:
            Y_Disable_Copy_And_Assign(Broker); //!< discarding
        };


    }

}

#endif // !Y_Ink_Broker_Included

