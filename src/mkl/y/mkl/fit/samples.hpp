
//! \file

#ifndef Y_Fit_Samples_Included
#define Y_Fit_Samples_Included 1

#include "y/mkl/fit/sample.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {
            class SamplesCommon
            {
            public:
                static const char * const CallSign; //!< "Fit::Samples"
                explicit SamplesCommon() noexcept;
                virtual ~SamplesCommon() noexcept;

                static void ErrorMultipleName(const String &);

            private:
                Y_Disable_Copy_And_Assign(SamplesCommon);
            };

            //__________________________________________________________________
            //
            //
            //
            //! Samples
            //
            //
            //__________________________________________________________________
            template <typename ABSICISSA,typename ORDINATE>
            class Samples :
            public SuffixSet<String, typename Sample<ABSICISSA,ORDINATE>::Pointer>,
            public SamplesCommon
            {
            public:
                typedef Sample<ABSICISSA,ORDINATE>   SampleType;
                typedef typename SampleType::Pointer SamplePointer;

                inline explicit Samples() :
                SuffixSet<String,SamplePointer>(),
                SamplesCommon()
                {}

                inline virtual ~Samples() noexcept {}

                template <typename SAMPLE> inline
                SAMPLE & operator()(SAMPLE * const sample)
                {
                    assert(sample);
                    {
                        const SamplePointer p = sample;
                        if(!this->insert(p)) ErrorMultipleName(p->name);
                    }
                    return *sample;
                }


            private:
                Y_Disable_Copy_And_Assign(Samples); //!< discarding
            };

        }

    }

}

#endif // !Y_Fit_Samples_Included

