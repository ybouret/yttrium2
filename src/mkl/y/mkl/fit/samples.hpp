
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
                typedef XAddition *                        XAddPtr;        //!< alias
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
                weight(),
                xBeta(),
                xAlpha()
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
                virtual void scatter(Writable<ORDINATE>       &a_global,
                                     const Readable<ORDINATE> &a_local) const noexcept
                {

                    assert(a_local.size()==a_global.size());
                    a_global.ld(a_local);
                }

                inline
                virtual ORDINATE computeD2(Function                 & F,
                                           const Readable<ORDINATE> & aorg)
                {
                    xadd.ldz();
                    size_t total  = 0;
                    for(Iterator it=this->begin();it!=this->end();++it)
                    {
                        SampleType &   sample = **it;
                        const size_t   n      = sample.count();
                        const ORDINATE w      = (fcpu_t)n;
                        total += n;
                        xadd << w * sample.computeD2(F,aorg);
                    }
                    if(total>0)
                    {
                        const ORDINATE den =  (fcpu_t)total;
                        return (D2 = xadd.sum()/den);
                    }
                    else
                    {
                        return (D2 = xadd.sum()); // zero
                    }
                }

                inline
                virtual ORDINATE computeD2full(Gradient                 & F,
                                               const Readable<ORDINATE> & aorg,
                                               const Readable<bool>     & used)
                {
                    assert(aorg.size()==used.size());

                    //----------------------------------------------------------
                    //
                    // initialize global data
                    //
                    //----------------------------------------------------------
                    const size_t nvar = aorg.size();
                    initialize(nvar);

                    //----------------------------------------------------------
                    //
                    // first part: collect individual metrics
                    //
                    //----------------------------------------------------------
                    xadd.ldz();
                    size_t total  = 0;
                    for(Iterator it=this->begin();it!=this->end();++it)
                    {
                        SampleType &   sample = **it;
                        const size_t   n      = sample.count();
                        const ORDINATE w      = (fcpu_t)n;
                        weight << w;
                        total += n;
                        xadd << w * sample.computeD2full(F,aorg,used);
                    }
                    assert(this->size() == weight.size() );

                    //----------------------------------------------------------
                    //
                    // second part: build global metrics
                    //
                    //----------------------------------------------------------
                    if(total>0)
                    {
                        //------------------------------------------------------
                        // dispatch
                        //------------------------------------------------------
                        {
                            size_t i=1; // sample index for weight
                            for(Iterator it=this->begin();it!=this->end();++it,++i)
                            {
                                const SampleType              & S      = **it;
                                const ORDINATE                  w      = weight[i];
                                const Variables               & vars   = S.vars;
                                const Readable<ORDINATE>      & beta0  = S.beta;
                                const Matrix<ORDINATE>        & alpha0 = S.alpha;
                                const Variables::ConstIterator  vend   = vars->end();
                                for(Variables::ConstIterator jter=vars->begin();jter!=vend;++jter)
                                {
                                    const Variable &jv = **jter;
                                    const size_t    jG = jv.global.indx; if( !used[jG] ) continue;
                                    const size_t    j0 = jv.indx;
                                    assert(xBeta[jG]!=0);assert(xAlpha[jG][jG]!=0);
                                    *xBeta[jG]      << w * beta0[j0];
                                    *xAlpha[jG][jG] << w * alpha0[j0][j0];
                                    Variables::ConstIterator kter = jter;
                                    for(++kter;kter!=vend;++kter)
                                    {
                                        const Variable &kv = **kter;
                                        const size_t    kG = kv.global.indx; if( !used[kG] ) continue;
                                        const size_t    k0 = kv.indx;
                                        assert(xAlpha[jG][kG]!=0);
                                        *xAlpha[jG][kG] << w * alpha0[j0][k0];
                                    }
                                }
                            }
                        }

                        //------------------------------------------------------
                        // collect
                        //------------------------------------------------------
                        const ORDINATE den =  (fcpu_t)total;
                        for(size_t i=1;i<=nvar;++i)
                        {
                            if(!used[i]) continue;
                            beta[i]     = xBeta[i]->sum()/den;
                            alpha[i][i] = xAlpha[i][i]->sum()/den;
                            for(size_t j=i+1;j<=nvar;++j)
                            {
                                assert(0!=xAlpha[i][j]);
                                if(!used[j]) continue;
                                alpha[i][j] = xAlpha[i][j]->sum()/den;
                            }
                        }
                        this->symmetrize();

                        //------------------------------------------------------
                        // return
                        //------------------------------------------------------
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


                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                Vector<ORDINATE> weight; //!< weight per sample
                Vector<XAddPtr>  xBeta;  //!< storage of XAddition
                Matrix<XAddPtr>  xAlpha; //!< storage of XAddition
                
            private:
                Y_Disable_Copy_And_Assign(Samples); //!< discarding

                //! initialize dynamic values \param nvar global variables
                inline void initialize(const size_t nvar)
                {
                    const ORDINATE zero(0);
                    const ORDINATE one(1);

                    beta.adjust(nvar,zero);
                    alpha.make(nvar,nvar);
                    alpha.diagonal(one,zero);
                    weight.free();

                    cadd.adjust( (nvar * (nvar+3)) >>1 );
                    cadd.ldz();
                    xBeta.adjust(nvar,0);
                    xAlpha.make(nvar,nvar);
                    {
                        XAddition *node = cadd.head;
                        for(size_t i=1;i<=nvar;++i)
                        {
                            xBeta[i] = node; node=node->next;
                            for(size_t j=1;j<i;++j) xAlpha[i][j] = 0;
                            for(size_t j=i;j<=nvar;++j)
                            {
                                xAlpha[i][j] = node; node=node->next;
                            }
                        }
                    }
                }


            };

        }

    }

}

#endif // !Y_Fit_Samples_Included

