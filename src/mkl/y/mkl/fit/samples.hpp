
//! \file

#ifndef Y_Fit_Samples_Included
#define Y_Fit_Samples_Included 1

#include "y/mkl/fit/sample.hpp"
#include "y/mkl/api/fcpu.hpp"

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
                typedef typename AdjustableType::Gradient  Gradient;       //!< alias
				typedef typename FCPU<ORDINATE>::Type      fcpu_t;         //!< alias
                using AdjustableType::xadd;
                using AdjustableType::D2;
                using AdjustableType::beta;
                using AdjustableType::alpha;
                using AdjustableType::cadd;

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup \param uid name
                template <typename UID>
                inline explicit Samples(const UID &uid) :
                AdjustableType(uid),
                SuffixSet<String,SamplePointer>(),
                SamplesCommon(),
                weight()
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

                inline
                virtual ORDINATE computeD2(Function                 & F,
                                           const Readable<ORDINATE> & aorg)
                {
                    xadd.ldz();
                    size_t res  = 0;
                    for(Iterator it=this->begin();it!=this->end();++it)
                    {
                        SampleType &   sample = **it;
                        const size_t   n      = sample.count();
                        const ORDINATE w      = (fcpu_t)n;
                        res += n;
                        xadd << w * sample.computeD2(F,aorg);
                    }
                    if(res>0)
                    {
                        const ORDINATE den =  (fcpu_t)res;
                        return (D2 = xadd.sum()/den);
                    }
                    else
                    {
                        return (D2 = xadd.sum());
                    }
                }

                inline
                virtual ORDINATE computeD2full(Gradient                 & F,
                                               const Readable<ORDINATE> & aorg,
                                               const Readable<bool>     & used)
                {
                    const ORDINATE zero(0);
                    const ORDINATE one(1);

                    assert(aorg.size()==used.size());

                    // initialize global data
                    const size_t nvar = aorg.size();
                    beta.adjust(nvar,zero);
                    alpha.make(nvar,nvar);
                    alpha.diagonal(one,zero);
                    weight.free();
                    cadd.adjust( (nvar * (nvar+3))>>1 );
                    cadd.ldz();

                    // first part: collect individual
                    xadd.ldz();
                    size_t res  = 0;
                    for(Iterator it=this->begin();it!=this->end();++it)
                    {
                        SampleType &   sample = **it;
                        const size_t   n      = sample.count();
                        const ORDINATE w      = (fcpu_t)n;
                        weight << w;
                        res += n;
                        xadd << w * sample.computeD2full(F,aorg,used);
                    }

                    assert(this->size() == weight.size() );

                    // second part: form global metrics
                    if(res>0)
                    {

                        // dispatch
                        {
                            XAddition *node = cadd.head;
                            size_t     i    = 1;
                            for(Iterator it=this->begin();it!=this->end();++it,++i)
                            {
                                const SampleType & sample = **it;
                                const ORDINATE     w      = weight[i];
                                {
                                    const Readable<ORDINATE> &beta0 = sample.beta;
                                    const Variables &        vars = sample.vars;
                                    const size_t             nvar = vars->size();
                                    Variables::ConstIterator jter = vars->begin();
                                    for(size_t j=nvar;j>0;--j,++jter)
                                    {
                                        const Variable &jv = **jter;
                                        const size_t    jG = jv.global.indx; if( !used[jG] ) continue;
                                        const ORDINATE  wbeta = w * jv(beta0);
                                        Y_Fit_Sample_Store( wbeta );
                                    }
                                }
                            }
                        }

                        // collect
                        const ORDINATE den =  (fcpu_t)res;
                        {
                            XAddition *node = cadd.head;
                            for(Iterator it=this->begin();it!=this->end();++it)
                            {
                                const SampleType &sample = **it;
                                const Variables &        vars = sample.vars;
                                const size_t             nvar = vars->size();
                                Variables::ConstIterator jter = vars->begin();
                                for(size_t j=nvar;j>0;--j,++jter)
                                {
                                    const Variable &jv = **jter;
                                    const size_t    jG = jv.global.indx; if( !used[jG] ) continue;
                                    Y_Fit_Sample_QMean(beta[jG],den);
                                }
                            }
                        }

                        // return
                        return (D2 = xadd.sum()/den);
                    }
                    else
                    {
                        return (D2 = zero);
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


                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                Vector<ORDINATE> weight; //!< weight per sample

            private:
                Y_Disable_Copy_And_Assign(Samples); //!< discarding
            };

        }

    }

}

#endif // !Y_Fit_Samples_Included

