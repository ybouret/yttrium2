//! \file

#ifndef Y_Field_Layout_Metrics_Included
#define Y_Field_Layout_Metrics_Included 1

#include "y/memory/stealth.hpp"
#include "y/type/shallow.hpp"

namespace Yttrium
{

    namespace Field
    {

        //______________________________________________________________________
        //
        //
        //
        //! Shared components for Layouts
        //
        //
        //______________________________________________________________________
        class LayoutMetrics
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            virtual ~LayoutMetrics()                      noexcept; //!< cleanup
            explicit LayoutMetrics(const LayoutMetrics &) noexcept; //!< copy

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const unsigned dimensions; //!< space dimension
            const size_t   items;      //!< items in field


        protected:
            //! setup with ordering and precomputations
            /**
             \param d dimensions
             \param lower lower coordinates address
             \param upper upper coordinates address
             \param width width coordinates address
             \param shift shift coordinates address
             */
            explicit LayoutMetrics(const unsigned d,
                                   unit_t * const lower,
                                   unit_t * const upper,
                                   size_t * const width,
                                   size_t * const shift) noexcept;
            
            //! setup \param d dimensions \param n items
            explicit LayoutMetrics(const unsigned d,
                                   const size_t   n) noexcept;


        private:
            Y_Disable_Assign(LayoutMetrics); //!< discarding
        };

      

      
    }
}

#endif
