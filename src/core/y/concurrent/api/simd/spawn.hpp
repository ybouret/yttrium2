//! \file

#ifndef Y_Concurrent_Spawn_Included
#define Y_Concurrent_Spawn_Included 1

#include "y/concurrent/api/simd.hpp"
#include "y/concurrent/type/resources.hpp"
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
        //! call procedures over computed tiles
        //
        //
        //______________________________________________________________________
        template <typename TILES>
        class Spawn : public CountedObject, public TILES, public Resources
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
            typedef ArcPtr< Spawn<TILES> >    Pointer;   //!< alias

            //! generic routine prototype
            typedef void (*Routine)(Lockable & , Tile & , void * const);

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
            CountedObject(),
            Tiles(proc->size(),data),
            call(0),
            args(0),
            processor(proc),
            kernel( me(), &Spawn::compute)
            {

            }

            //! setup one (empty) tile per processor context
            /**
             \param proc shared processor
             */
            inline explicit Spawn(const Processor &proc) :
            CountedObject(),
            Tiles(proc->size()),
            call(0),
            args(0),
            processor(proc),
            kernel(me(),&Spawn::compute)
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


            //! run 1-argument code
            /**
             \param code code(context.sync, self[context.indx], arg1)
             \param arg1 persistent argument
             */
            template <typename CODE, typename ARG1> inline
            void run(CODE &code, ARG1 &arg1)
            {
                Stub1<CODE,ARG1> instr = { code, arg1 };
                (*this)(instr);
            }

            //! run 2-arguments code
            /**
             \param code code(context.sync, self[context.indx], arg1, arg2)
             \param arg1 persistent argument
             \param arg2 persistent argument
             */
            template <typename CODE, typename ARG1, typename ARG2> inline
            void run(CODE &code, ARG1 &arg1, ARG2 &arg2)
            {
                Stub2<CODE,ARG1,ARG2> instr = { code, arg1, arg2 };
                (*this)(instr);
            }

            //! run 3-arguments code
            /**
             \param code code(context.sync, self[context.indx], arg1, arg2, arg3)
             \param arg1 persistent argument
             \param arg2 persistent argument
             \param arg3 persistent argument
             */
            template <typename CODE, typename ARG1, typename ARG2, typename ARG3> inline
            void run(CODE &code, ARG1 &arg1, ARG2 &arg2, ARG3 &arg3)
            {
                Stub3<CODE,ARG1,ARG2,ARG3> instr = { code, arg1, arg2, arg3 };
                (*this)(instr);
            }

            //! run 4-arguments code
            /**
             \param code code(context.sync, self[context.indx], arg1, arg2, arg3,arg4)
             \param arg1 persistent argument
             \param arg2 persistent argument
             \param arg3 persistent argument
             \param arg4 persistent argument
             */
            template <typename CODE, typename ARG1, typename ARG2, typename ARG3, typename ARG4> inline
            void run(CODE &code, ARG1 &arg1, ARG2 &arg2, ARG3 &arg3, ARG4 &arg4)
            {
                Stub4<CODE,ARG1,ARG2,ARG3,ARG4> instr = { code, arg1, arg2, arg3, arg4 };
                (*this)(instr);
            }

            //! run 5-arguments code
            /**
             \param code code(context.sync, self[context.indx], arg1, arg2, arg3,arg4, arg5)
             \param arg1 persistent argument
             \param arg2 persistent argument
             \param arg3 persistent argument
             \param arg4 persistent argument
             \param arg5 persistent argument
             */
            template <typename CODE, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5> inline
            void run(CODE &code, ARG1 &arg1, ARG2 &arg2, ARG3 &arg3, ARG4 &arg4, ARG5 &arg5)
            {
                Stub5<CODE,ARG1,ARG2,ARG3,ARG4,ARG5> instr = { code, arg1, arg2, arg3, arg4, arg5 };
                (*this)(instr);
            }





            //! host.meth(context.sync, self[context.indx]) over each tile
            /**
             \param host object
             \param meth method
             */
            template <typename HOST, typename METH> inline
            void operator()(HOST &host, METH meth)
            {
                CxxWrapper0<HOST,METH> wrapper = { host, meth };
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
                CxxWrapper1<HOST,METH,ARG1> wrapper = { host, meth, arg1 };
                (*this)(wrapper);
            }

            //! host.meth(context.sync, self[context.indx],arg1,arg2) over each tile
            /**
             \param host object
             \param meth method
             \param arg1 first argument
             \param arg2 second argument
             */
            template <typename HOST, typename METH, typename ARG1, typename ARG2> inline
            void operator()(HOST &host, METH meth, ARG1 &arg1, ARG2 &arg2)
            {
                CxxWrapper2<HOST,METH,ARG1,ARG2> wrapper = { host, meth, arg1, arg2 };
                (*this)(wrapper);
            }

            //! host.meth(context.sync, self[context.indx],arg1,arg2,arg3) over each tile
            /**
             \param host object
             \param meth method
             \param arg1 first  argument
             \param arg2 second argument
             \param arg3 third  argument
             */
            template <typename HOST, typename METH, typename ARG1, typename ARG2, typename ARG3> inline
            void operator()(HOST &host, METH meth, ARG1 &arg1, ARG2 &arg2, ARG3 &arg3)
            {
                CxxWrapper3<HOST,METH,ARG1,ARG2,ARG3> wrapper = { host, meth, arg1, arg2, arg3 };
                (*this)(wrapper);
            }


            //! acquire local memory for each tile \param bytes minimal bytes
            /** memory is always zeroed */
            inline void acquireLocalMemory(const size_t bytes)
            {
                acquireEachTileOf(*this,bytes);
            }

            
            //! release all local memory
            inline void releaseLocalMemory() noexcept
            {
                releaseEachTileOf(*this);
            }


            //! acquire local memory for a given type
            template <typename T> inline
            void acquireLocalMemoryFor()
            {
                acquireLocalMemory( sizeof(T) );
            }

            //! deliver equal parts of memory to each tile
            inline void deliverLocalMemory() noexcept
            {
                deliverEachTileOf(*this);
            }

            //! link a node to each tile
            /**
             \param node first node
             */
            template <typename NODE> inline
            void link(NODE *node) noexcept
            {
                assert(node);
                acquireLocalMemory( sizeof(NODE*) );
                const size_t n = this->size();
                for(size_t i=1;i<=n;++i,node=node->next)
                {
                    assert(node);
                    (*this)[i].template as<NODE *>() = node;
                }
            }

            //! unlink previously linked nodes
            inline void unlink() noexcept
            {
                const size_t n = this->size();
                for(size_t i=1;i<=n;++i)
                {
                    (*this)[i].template as<void *>() = 0;
                }
            }



        private:
            Y_Disable_Copy_And_Assign(Spawn); //!< discarding
            Routine   call;                   //!< routine
            void *    args;                   //!< arguments for routine
            Processor processor;              //!< shared processor
            Kernel    kernel;                 //!< call compute(...)

            //! \return this, helper for MSC
            inline Spawn* me() noexcept { return this;  }

            //! executed in a thread \param context processor context
            void compute(const Context &context) noexcept
            {
                assert(0!=call);
                assert(0!=args);
                Tile & tile  = (*this)[context.indx];
                call(context.sync,tile,args);
            }

            //! decode call to CODE as code(sync,tile)
            /**
             \param sync for calls synchronization
             \param tile working tile
             \param args address of CODE
             */
            template <typename CODE> static inline
            void Stub(Lockable &sync, Tile &tile, void * const args)
            {
                assert(0!=args);
                CODE & code = *(CODE*)(args);
                code(sync,tile);
            }

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            template <typename CODE, typename ARG1>
            struct Stub1
            {
                CODE &code;
                ARG1 &arg1;

                inline void operator()(Lockable &sync, Tile &tile) {
                    code(sync,tile,arg1);
                }
            };

            template <typename CODE, typename ARG1, typename ARG2>
            struct Stub2
            {
                CODE &code;
                ARG1 &arg1;
                ARG2 &arg2;

                inline void operator()(Lockable &sync, Tile &tile) {
                    code(sync,tile,arg1,arg2);
                }
            };

            template <typename CODE, typename ARG1, typename ARG2, typename ARG3>
            struct Stub3
            {
                CODE &code;
                ARG1 &arg1;
                ARG2 &arg2;
                ARG3 &arg3;

                inline void operator()(Lockable &sync, Tile &tile) {
                    code(sync,tile,arg1,arg2,arg3);
                }
            };

            template <typename CODE, typename ARG1, typename ARG2, typename ARG3, typename ARG4>
            struct Stub4
            {
                CODE &code;
                ARG1 &arg1;
                ARG2 &arg2;
                ARG3 &arg3;
                ARG4 &arg4;

                inline void operator()(Lockable &sync, Tile &tile) {
                    code(sync,tile,arg1,arg2,arg3,arg4);
                }
            };

            template <typename CODE, typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
            struct Stub5
            {
                CODE &code;
                ARG1 &arg1;
                ARG2 &arg2;
                ARG3 &arg3;
                ARG4 &arg4;
                ARG5 &arg5;

                inline void operator()(Lockable &sync, Tile &tile) {
                    code(sync,tile,arg1,arg2,arg3,arg4,arg5);
                }
            };


#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

            //! alias to wrap host+method call
            template <typename HOST, typename METH>
            struct CxxWrapper0
            {
                HOST & host; //!< persistent host
                METH   meth; //!< host's method

                //! \param sync from context \param tile one of the tile 
                inline void operator()(Lockable &sync, Tile &tile )
                {
                    (host.*meth)(sync,tile);
                }
            };


            //! alias to wrap host+method call with one arg
            template <typename HOST, typename METH, typename ARG1>
            struct CxxWrapper1
            {
                HOST & host; //!< persistent host
                METH   meth; //!< host's method
                ARG1 & arg1; //!< method extra argument

                //! \param sync from context \param tile one of the tile
                inline void operator()(Lockable &sync, Tile &tile )
                {
                    (host.*meth)(sync,tile,arg1);
                }
            };


            //! alias to wrap host+method call with two args
            template <typename HOST, typename METH, typename ARG1, typename ARG2>
            struct CxxWrapper2
            {
                HOST & host; //!< persistent host
                METH   meth; //!< host's method
                ARG1 & arg1; //!< method extra argument
                ARG2 & arg2; //!< method extra argument

                //! \param sync from context \param tile one of the tile
                inline void operator()(Lockable &sync, Tile &tile )
                {
                    (host.*meth)(sync,tile,arg1,arg2);
                }
            };

            //! alias to wrap host+method call with three args
            template <typename HOST, typename METH, typename ARG1, typename ARG2, typename ARG3>
            struct CxxWrapper3
            {
                HOST & host; //!< persistent host
                METH   meth; //!< host's method
                ARG1 & arg1; //!< method extra argument
                ARG2 & arg2; //!< method extra argument
                ARG3 & arg3; //!< method extra argument

                //! \param sync from context \param tile one of the tile
                inline void operator()(Lockable &sync, Tile &tile )
                {
                    (host.*meth)(sync,tile,arg1,arg2,arg3);
                }
            };






        };


    }
}

#endif // !Y_Concurrent_Spawn_Included

