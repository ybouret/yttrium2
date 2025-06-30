
//! \file

#ifndef Y_Apex_Transmogrify_Included
#define Y_Apex_Transmogrify_Included 1

#include "y/apex/block/block.hpp"
#include "y/type/sign.hpp"
#include "y/check/static.hpp"
namespace Yttrium
{
    namespace Apex
    {
        //! in-place conversion of different views with synchronized sizes
        struct Transmogrify
        {
            //! LARGE -> SMALL
            /**
             \param target output block
             \param source input block
             */
            template <typename SMALL, typename LARGE> static inline
            void Expand(Block<SMALL> &target, const Block<LARGE> &source) noexcept
            {
                Y_STATIC_CHECK(sizeof(SMALL)<sizeof(LARGE),BadSizes);
                assert(source.isValid());
                static const unsigned RHO = sizeof(LARGE)/sizeof(SMALL);
                static const unsigned SHR = sizeof(SMALL) * 8;
                SMALL *      small = target.data;
                const LARGE *large = source.data;
                for(size_t i=source.size;i>0;--i)
                {
                    const LARGE value = *(large++);
                    for(unsigned j=0;j<RHO;++j)
                    {
                        *(small++) = SMALL(value>>(j*SHR));
                    }
                }
                assert(target.isValid());
            }

            //! SMALL -> LARGE
            /**
             \param target output block
             \param source input block
             */
            template <typename LARGE, typename SMALL> static inline
            void Shrink(Block<LARGE> &target, const Block<SMALL> &source) noexcept
            {
                Y_STATIC_CHECK(sizeof(SMALL)<sizeof(LARGE),BadSizes);
                assert(source.isValid());
                static const unsigned RHO = sizeof(LARGE)/sizeof(SMALL);
                static const unsigned SHL = sizeof(SMALL) * 8;

                const size_t words = source.size;
                const SMALL *small = source.data;
                LARGE       *large = target.data;
                for(size_t i = (target.size = Alignment::To<LARGE>::Ceil(words*sizeof(SMALL))/sizeof(LARGE)), used=0;i>0;--i)
                {
                    LARGE value = *(small++); ++used;
                    for(unsigned j=1;j<RHO;++j)
                    {
                        const LARGE temp = *(small++);
                        value |= (temp << (j*SHL));
                        if(++used>=words) break;
                    }
                    *(large++) = value;
                    if(used>=words) break;
                }
                assert(target.isValid());
            }


            //! forward to expand \param target output block \param source input block
            template <typename SMALL, typename LARGE> static inline
            void To(Block<SMALL> &target, const Block<LARGE> &source, const IntToType<Negative> &) noexcept
            {
                Expand(target,source);
            }

            //!  forward to shrink \param target output block \param source input block
            template <typename LARGE, typename SMALL> static inline
            void To(Block<LARGE> &target, const Block<SMALL> &source, const IntToType<Positive> &) noexcept
            {
                Shrink(target,source);
            }

            //! do nothing upon same type
            template <typename T> static inline
            void To(Block<T> &, const Block<T> &, const IntToType<__Zero__> &) noexcept
            {

            }

            //! forward to matching procedure \param target output block \param source input block
            template <typename TARGET, typename SOURCE> static inline
            void To(Block<TARGET> &target, const Block<SOURCE> &source) noexcept
            {
                static const unsigned         TSize = sizeof(TARGET);
                static const unsigned         SSize = sizeof(SOURCE);
                static const SignType         Which = (TSize < SSize) ? Negative : (SSize<TSize ? Positive : __Zero__);
                static const IntToType<Which> choice = {};
                To(target,source,choice);
            }


        };
    }

}

#endif
