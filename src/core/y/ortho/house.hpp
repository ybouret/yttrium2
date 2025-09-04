
//! \file

#ifndef Y_Apex_Ortho_House_Included
#define Y_Apex_Ortho_House_Included 1

#include "y/ortho/family.hpp"

namespace Yttrium
{
    namespace Ortho
    {

        //______________________________________________________________________
        //
        //
        //
        //! Common Info to build House
        //
        //
        //______________________________________________________________________
        class HouseInfo
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit HouseInfo(const size_t dims); //!< setup \param dims dimensions
            virtual ~HouseInfo() noexcept;         //!< cleanup

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const Metrics metrics; //!< metrics
            Vector::Pool  vecPool; //!< shared pool with metrics

        private:
            Y_Disable_Copy_And_Assign(HouseInfo); //!< discarding
        };

        //______________________________________________________________________
        //
        //
        //
        //! standalone family for basis construction/extraction
        //
        //
        //______________________________________________________________________
        class House : public HouseInfo,  public Family
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit House(const size_t dims); //!< setup \param dims dimensions
            virtual ~House() noexcept;         //!< cleanup

        private:
            Y_Disable_Copy_And_Assign(House); //!< discarding
        };
    }

}

#endif

