
//! \file

#ifndef Y_Ink_Ops_Included
#define Y_Ink_Ops_Included 1

#include "y/ink/pixmap.hpp"
#include "y/ink/broker.hpp"

namespace Yttrium
{
    namespace Ink
    {

        //! Seq/Par operations wrapper
        struct Ops
        {
            //! apply unary operation to each pixel of pixmap
            /**
             \param broker par/seq broker
             \param proc   proc(pixel)
             \param pixmap source/taget pixmap
             */
            template <
            typename PIXMAP,
            typename PROC> static inline
            void Apply( Broker &broker, PROC &proc, PIXMAP &pixmap ) noexcept
            {
                broker.prep(pixmap);
                broker.run(proc,pixmap);
            }


            //! apply binary operation on each pixel of pixmap
            /**
             \param broker par/seq broker
             \param proc   proc(pixel,arg1)
             \param pixmap source/taget pixmap
             \param arg1   argument for proc
             */
            template <
            typename PIXMAP,
            typename PROC,
            typename ARG1> static inline
            void Apply( Broker &broker, PROC &proc, PIXMAP &pixmap, ARG1 &arg1 ) noexcept
            {
                broker.prep(pixmap);
                broker.run(proc,pixmap,arg1);
            }

            //! apply ternary operation on each pixel of pixmap
            /**
             \param broker par/seq broker
             \param proc   proc(pixel,arg1,arg2)
             \param pixmap source/target pixmap
             \param arg1   argument for proc
             \param arg2   argument for proc
             */
            template <
            typename PIXMAP,
            typename PROC,
            typename ARG1,
            typename ARG2> static inline
            void Apply( Broker &broker, PROC &proc, PIXMAP &pixmap, ARG1 &arg1, ARG2 &arg2) noexcept
            {
                broker.prep(pixmap);
                broker.run(proc,pixmap,arg1,arg2);
            }

            //! \param lhs lhs \param rhs rhs \return true iff same are
            template <typename LHS, typename RHS> static inline
            bool HaveSameArea(const LHS &lhs, const RHS &rhs) noexcept
            {
                const Area &la = lhs;
                const Area &ra = rhs;
                return la == ra;
            }

            //! target = convert(source) pixel-wise
            /**
             \param broker  broker
             \param pixmap  target
             \param convert pixel-wise function
             \param source  source
             */
            template <
            typename PIXMAP,
            typename CONVERT,
            typename SOURCE> static inline
            void Convert(Broker &broker, PIXMAP &pixmap, CONVERT &convert, SOURCE &source) noexcept
            {
                assert( HaveSameArea(pixmap,source) );
                broker.prep(pixmap);
                broker.run( ForEachPixel<PIXMAP,CONVERT,SOURCE>,pixmap,convert,source);
            }

            //! transform(target,source,origin)
            /**
             \param broker    broker
             \param target    target
             \param transform probe-point procedure
             \param source    source
             */
            template
            <
            typename TARGET,
            typename TRANSFORM,
            typename SOURCE> static inline
            void Transform(Broker &broker, TARGET &target, TRANSFORM &transform, SOURCE &source) noexcept
            {
                assert( HaveSameArea(target,source) );
                broker.prep(target);
                broker.run( ForEachPoint<TARGET,TRANSFORM,SOURCE>,target,transform,source);
            }




        private:
#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
            template <typename PIXMAP, typename CONVERT, typename SOURCE> static inline
            void ForEachPixel(Lockable &, const Tile &tile, PIXMAP &pixmap, CONVERT &convert, SOURCE &source)
            {
                for(unit_t j=tile.h;j>0;--j)
                {
                    const Segment               seg = tile[j];
                    const size_t                y   = (size_t)seg.start.y;
                    typename       PIXMAP::Row  & tgt = pixmap(y);
                    const typename SOURCE::Row  & src = source(y);
                    for(size_t x=seg.start.x,i=seg.width;i>0;--i,++x)
                        tgt(x) = convert(src(x));
                }
            }

            template <typename TARGET, typename TRANSFORM, typename SOURCE> static inline
            void ForEachPoint(Lockable &, const Tile &tile, TARGET &target, TRANSFORM &transform, SOURCE &source)
            {
                for(unit_t j=tile.h;j>0;--j)
                {
                    const Segment seg = tile[j];
                    Point         p   = seg.start;
                    for(unit_t i=seg.width;i>0;--i,++p.x)
                        transform(target,source,p);
                }
            }
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

        };

    }

}

#endif // !Y_Ink_Ops_Included
