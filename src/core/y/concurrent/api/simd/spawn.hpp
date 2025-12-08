//! \file

#ifndef Y_Concurrent_Spawn_Included
#define Y_Concurrent_Spawn_Included 1

#include "y/concurrent/api/simd.hpp"
#include "y/pointer/arc.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        typedef ArcPtr<SIMD> Processor;

        template <typename TILES>
        class Spawn : public TILES
        {
        public:
            typedef TILES    Tiles;
            typedef typename Tiles::Parameter Parameter;

            inline explicit Spawn(const Processor &proc,
                                  Parameter        data) :
            Tiles(proc->size(),data),
            processor(proc),
            kernel(this, & Spawn::compute)
            {

            }

            inline virtual ~Spawn() noexcept
            {

            }

            void run()
            {
                (*processor)(kernel);
            }


        private:
            Y_Disable_Copy_And_Assign(Spawn);
            Processor processor;
            Kernel    kernel;

            //! executed in a thread
            void compute(const Context &context) noexcept
            {
                { Y_Giant_Lock(); (std::cerr << "in " << context << std::endl).flush(); };
            }

        };


    }
}

#endif // !Y_Concurrent_Spawn_Included

