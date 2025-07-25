
//! \file

#ifndef Y_Apex_Ortho_Metrics_Included
#define Y_Apex_Ortho_Metrics_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Apex
    {
        namespace Ortho
        {

            //! Quality of size w.r.t dimensions
            enum Quality
            {
                Basis,      //!< size == dimensions
                HyperPlane, //!< size == hyperplane
                Generating  //!< size < hyperplane
            };

            //__________________________________________________________________
            //
            //
            //
            //! metrics for derived objects
            //
            //
            //__________________________________________________________________
            class Metrics
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                Metrics(const size_t dims);        //!< setup with dimensions \param dims user's dimensions
                virtual ~Metrics() noexcept;       //!< cleanup
                Metrics(const Metrics &) noexcept; //!< duplicate

                //______________________________________________________________
                //
                //
                // Methords
                //
                //______________________________________________________________

                static const char * HumanReadableQuality(const Quality) noexcept; //!< \return quality
                Quality      qualify(const size_t size) const noexcept; //!< \param size current size \return quality of size

                const size_t dimensions; //!< ambient space dimensions
                const size_t hyperplane; //!< hyperplane dimension


            private:
                Y_Disable_Assign(Metrics); //!< discarding
            };
        }

    }
}

#endif

