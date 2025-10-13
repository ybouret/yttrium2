
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
            //__________________________________________________________________
            //
            //
            //
            //! Samples Common parts
            //
            //
            //__________________________________________________________________
            class SamplesCommon
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                static const char * const CallSign; //!< "Fit::Samples"

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                explicit SamplesCommon() noexcept; //!< setup
                virtual ~SamplesCommon() noexcept; //!< cleanup

                //______________________________________________________________
                //
                //
                // methods
                //
                //______________________________________________________________

                //! throw exception if multiple name is detected
                static void ErrorMultipleName(const String &);

            private:
                Y_Disable_Copy_And_Assign(SamplesCommon); //!< discarding
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
            public Adjustable<ABSICISSA,ORDINATE>,
            public SuffixSet<String, typename Sample<ABSICISSA,ORDINATE>::Pointer>,
            public SamplesCommon
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef Adjustable<ABSICISSA,ORDINATE>   AdjustableType; //!< alias
                typedef Sample<ABSICISSA,ORDINATE>       SampleType;     //!< alias
                typedef typename SampleType::Pointer     SamplePointer;  //!< alias
                typedef SuffixSet<String,SamplePointer>  SampleDB;       //!< alias
                typedef typename SampleDB::Iterator      Iterator;       //!< alias
                typedef typename SampleDB::ConstIterator ConstIterator;  //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup
                template <typename UID>
                inline explicit Samples(const UID &uid) :
                AdjustableType(uid),
                SuffixSet<String,SamplePointer>(),
                SamplesCommon()
                {}

                //! cleanup
                inline virtual ~Samples() noexcept {}


                //______________________________________________________________
                //
                //
                // interface
                //
                //______________________________________________________________
                inline virtual size_t count() const noexcept
                {
                    size_t res = 0;
                    for(ConstIterator it=this->begin();it!=this->end();++it)
                    {
                        res += (**it).count();
                    }
                    return res;
                }


                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! append a new sample
                /**
                 \param sample newly created sample
                 \return *sample
                 */
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

