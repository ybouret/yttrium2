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
        typedef ArcPtr<SIMD> Processor; //!< alias


        //______________________________________________________________________
        //
        //
        //
        //! call procedures over tiles
        //
        //
        //______________________________________________________________________
        template <typename TILES>
        class Spawn : public TILES
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef TILES    Tiles;                      //!< alias
            typedef typename Tiles::Parameter Parameter; //!< alias
            typedef typename Tiles::Tile      Tile;      //!< alias

            //! generic routine prototype
            typedef void (*Routine)(Lockable & , const Tile & , void * const);

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup one tile per processor context
            /**
             \param proc shared processor
             \param data tiles parameter
             */
            inline explicit Spawn(const Processor &proc,
                                  Parameter        data) :
            Tiles(proc->size(),data),
            call(0),
            args(0),
            processor(proc),
            kernel( me(), &Spawn::compute)
            {

            }

            //! cleanup
            inline virtual ~Spawn() noexcept {}


            //! \param code code(context.sync, self[context.indx]) over each tile
            template <typename CODE> inline
            void operator()(CODE &code)
            {
                assert(0==call);
                assert(0==args);
                const Temporary<Routine> tempCall(call, Stub<CODE>   );
                const Temporary<void*>   tempArgs(args, (void*)&code );
                (*processor)(kernel);
            }

            //! host.meth(context.sync, self[context.indx]) over each tile
            /**
             \param host object
             \param meth method
             */
            template <typename HOST, typename METH> inline
            void operator()(HOST &host, METH meth)
            {
                Wrapper0<HOST,METH> wrapper = { host, meth };
                (*this)(wrapper);
            }


            //! host.meth(context.sync, self[context.indx],arg1) over each tile
            /**
             \param host object
             \param meth method
             \param arg1 argument
             */
            template <typename HOST, typename METH, typename ARG1> inline
            void operator()(HOST &host, METH meth, ARG1 &arg1)
            {
                Wrapper1<HOST,METH,ARG1> wrapper = { host, meth, arg1 };
                (*this)(wrapper);
            }



            

        private:
            Y_Disable_Copy_And_Assign(Spawn); //!< discarding
            Routine   call;                   //!< routine
            void *    args;                   //!< arguments for routine
            Processor processor;              //!< shared processor
            Kernel    kernel;                 //!< call compute(...)
                
            inline Spawn* me() noexcept { return this;  }

            //! executed in a thread \param context processor context
            void compute(const Context &context) noexcept
            {
                assert(0!=call);
                assert(0!=args);
                const Tile & tile  = (*this)[context.indx];
                call(context.sync,tile,args);
            }

            //! decode call to CODE as code(sync,tile)
            /**
             \param sync for calls synchronization
             \param tile working tile
             \param args address of CODE
             */
            template <typename CODE> static inline
            void Stub(Lockable &sync, const Tile &tile, void * const args)
            {
                assert(0!=args);
                CODE & code = *(CODE*)(args);
                code(sync,tile);
            }

            //! alias to wrap host+method call
            template <typename HOST, typename METH>
            struct Wrapper0
            {
                HOST & host; //!< persistent host
                METH   meth; //!< host's method

                //! \param sync from context \param tile one of the tile 
                inline void operator()(Lockable &sync, const Tile &tile )
                {
                    (host.*meth)(sync,tile);
                }
            };


            //! alias to wrap host+method call
            template <typename HOST, typename METH, typename ARG1>
            struct Wrapper1
            {
                HOST & host; //!< persistent host
                METH   meth; //!< host's method
                ARG1 & arg1; //!< method extra argument

                //! \param sync from context \param tile one of the tile
                inline void operator()(Lockable &sync, const Tile &tile )
                {
                    (host.*meth)(sync,tile,arg1);
                }
            };






        };


    }
}

#endif // !Y_Concurrent_Spawn_Included

