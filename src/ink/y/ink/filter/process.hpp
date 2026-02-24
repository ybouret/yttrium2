
//! \file

#ifndef Y_Ink_Filter_Process_Included
#define Y_Ink_Filter_Process_Included 1

#include "y/ink/filter.hpp"
#include "y/ink/ops.hpp"

namespace Yttrium
{
    namespace Ink
    {
        //! helper for Ops::Transform
        template <typename T, typename SCALAR>
        struct FilterImmediateOn
        {
            const Filter<T> & filter; //!< filter

            //! filter(target,source,origin)
            /**
             \param target target
             \param source scalar source
             \param origin probe point
             */
            inline void operator()(Pixmap<T> &target, const Pixmap<SCALAR> &source, const Point origin)
            {
                filter.template loadImmediate<SCALAR,SCALAR,1>(&target[origin],source,origin);
            }
        };

        //! helper for Ops::Transform
        template <typename T, typename SCALAR>
        struct FilterTransposeOn
        {
            const Filter<T> & filter; //!< filter

            //! filter(target,source,origin), tranpose
            /**
             \param target target
             \param source scalar source
             \param origin probe point
             */
            inline void operator()(Pixmap<T> &target, const Pixmap<SCALAR> &source, const Point origin)
            {
                filter.template loadTranspose<SCALAR,SCALAR,1>(&target[origin],source,origin);
            }
        };


        //! apply filter using Ops::Transform
        template <typename T>
        struct FilterProcess
        {
            //! immediate filter(target,source)
            /**
             \param broker broker
             \param filter filter
             \param target target
             \param source scalar source
             */
            template <typename SCALAR> static inline
            void ImmediateOn(Broker &broker, Pixmap<T> &target, const Filter<T> &filter, const Pixmap<SCALAR> &source)
            {
                FilterImmediateOn<T,SCALAR> F = { filter };
                Ops::Transform(broker,target,F,source);
            }

            //! tranpose filter(target,source)
            /**
             \param broker broker
             \param filter filter
             \param target target
             \param source scalar source
             */
            template <typename SCALAR> static inline
            void TransposeOn(Broker &broker, Pixmap<T> &target, const Filter<T> &filter, const Pixmap<SCALAR> &source)
            {
                FilterTransposeOn<T,SCALAR> F = { filter };
                Ops::Transform(broker,target,F,source);
            }
        };
    }

}

#endif // !Y_Ink_Filter_Process_Included
