//! \file

#ifndef Y_Concurrent_Spawn_Included
#define Y_Concurrent_Spawn_Included 1

#include "y/concurrent/api/simd.hpp"
#include "y/pointer/arc.hpp"
#include "y/type/temporary.hpp"

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
            typedef typename Tiles::Tile      Tile;
            typedef void (*Routine)(Lockable & , const Tile & , void * const);

            inline explicit Spawn(const Processor &proc,
                                  Parameter        data) :
            Tiles(proc->size(),data),
            call(0),
            args(0),
            processor(proc),
            kernel(this, & Spawn::compute)
            {

            }

            inline virtual ~Spawn() noexcept {

            }


            template <typename CODE> inline
            void operator()(CODE &code)
            {
                assert(0==call);
                assert(0==args);
                const Temporary<Routine> tempCall(call, Stub<CODE>   );
                const Temporary<void*>   tempArgs(args, (void*)&code );
                (*processor)(kernel);
            }

            template <typename HOST, typename METH> inline
            void operator()(HOST &host, METH meth)
            {
                Wrapper<HOST,METH> wrapper = { host, meth };
                (*this)(wrapper);
            }



            

        private:
            Y_Disable_Copy_And_Assign(Spawn);
            Routine   call;
            void *    args;
            Processor processor;
            Kernel    kernel;

            //! executed in a thread
            void compute(const Context &context) noexcept
            {
                assert(0!=call);
                assert(0!=args);
                const Tile   tile  = (*this)[context.indx];
                call(context.sync,tile,args);
            }



            template <typename CODE> static inline
            void Stub(Lockable &sync, const Tile &tile, void * const args)
            {
                assert(0!=args);
                CODE & code = *(CODE*)(args);
                code(sync,tile);
            }

            template <typename HOST, typename METH>
            struct Wrapper
            {
                HOST & host;
                METH   meth;
                inline void operator()(Lockable &sync, const Tile &tile )
                {
                    (host.*meth)(sync,tile);
                }
            };




        };


    }
}

#endif // !Y_Concurrent_Spawn_Included

