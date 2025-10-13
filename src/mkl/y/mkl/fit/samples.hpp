
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
            template <typename ABSCISSA,typename ORDINATE>
            class Samples :
            public Adjustable<ABSCISSA,ORDINATE>,
            public SuffixSet<String, typename Sample<ABSCISSA,ORDINATE>::Pointer>,
            public SamplesCommon
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef Adjustable<ABSCISSA,ORDINATE>      AdjustableType; //!< alias
                typedef Sample<ABSCISSA,ORDINATE>          SampleType;     //!< alias
                typedef typename SampleType::Pointer       SamplePointer;  //!< alias
                typedef SuffixSet<String,SamplePointer>    SampleDB;       //!< alias
                typedef typename SampleDB::Iterator        Iterator;       //!< alias
                typedef typename SampleDB::ConstIterator   ConstIterator;  //!< alias
                typedef typename AdjustableType::XAddition XAddition;      //!< alias
                typedef typename AdjustableType::Function  Function;       //!< alias
                using AdjustableType::xadd;
                using AdjustableType::D2;

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
                        res += (**it).count();
                    return res;
                }

                virtual ORDINATE computeD2(Function                 & F,
                                           const Readable<ORDINATE> & aorg)
                {

                    xadd.ldz();
                    size_t res  = 0;
                    for(Iterator it=this->begin();it!=this->end();++it)
                    {
                        SampleType &   sample = **it;
                        const size_t   n      = sample.count();
                        const ORDINATE dof(n);
                        res += n;
                        xadd << dof * sample.computeD2(F,aorg);
                    }
                    if(res>0)
                    {
                        const ORDINATE den(res);
                        return (D2 = xadd.sum()/den);
                    }
                    else
                    {
                        return (D2 = xadd.sum());
                    }
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

