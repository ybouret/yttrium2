
//! \file
//!
#ifndef Y_Coven_Analysis_Included
#define Y_Coven_Analysis_Included 1

#include "y/coven/tribes.hpp"
#include "y/functor.hpp"
#include <iomanip>

namespace Yttrium
{

    namespace Coven
    {

        //______________________________________________________________________
        //
        //
        //
        //! Embedded analysis
        //
        //
        //______________________________________________________________________
        struct Analysis
        {
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static unsigned           Width; //!< helper for format
            static const char * const CallSign; //!< "Coven::Analysis"
            static const char * const And;      //!< "&&"
            static const char * const Filter;   //!< "Filter"

            //! processing root policy
            enum RootPolicy
            {
                AcceptRoot, //!< root vector(s) sent to survey
                RejectRoot, //!< no root vector sent to survey
            };


            //! embedded analysis method
            /**
             \param xml      output
             \param matrix   compatible matrix
             \param survey   collect results
             \param policy   root vector policy
             \param optimize optimize search
             */
            template <typename MATRIX> static inline
            void Run(XMLog        &   xml,
                     const MATRIX &   matrix,
                     Survey &         survey,
                     const RootPolicy policy,
                     const bool       optimize)
            {
                Y_XML_Section_Attr(xml,CallSign, Y_XML_Attr(matrix.rows) << Y_XML_Attr(matrix.cols));
                survey.release();
                if(matrix.cols<=0) return;

                QVector::Pool vpool(matrix.cols);
                QFamily::Pool fpool(vpool);
                IPool         ipool;
                Survey *      first = 0;
                switch(policy)
                {
                    case RejectRoot: break;
                    case AcceptRoot: first = &survey; break;
                }

                Tribes        tribes(xml,matrix,ipool,fpool,first);
                size_t        generated = tribes.size;
                while(true)
                {
                    const size_t gen = tribes.generate(xml,matrix, &survey,optimize);
                    if(gen<=0) break;
                    generated += gen;
                }
                Summary(xml, tribes, generated, survey);
            }


            //! embedded analysis method and filter
            /**
             \param xml      output
             \param matrix   compatible matrix
             \param keep     would keep vectors if result is true
             \param survey   collect results
             \param policy   root vector policy
             \param optimize optimize search
             \return final survey size
             */
            template <typename MATRIX, typename IS_OK> static inline
            size_t Run(XMLog &          xml,
                       const MATRIX &   matrix,
                       IS_OK &          keep,
                       Survey &         survey,
                       const RootPolicy policy,
                       const bool       optimize)
            {
                Y_XML_Section_Attr(xml,CallSign,And<<Filter);
                { Run(xml,matrix,survey,policy,optimize); }
                {
                    Y_XML_Section(xml,Filter);
                    const size_t oldSize = survey->size;
                    const size_t newSize = survey.retain(xml,keep);
                    FilterOut(xml,oldSize,newSize);
                    return newSize;
                }
            }

        private:
            //! display analysis summary
            static void Summary(XMLog &, const Tribes &,const size_t,const Survey &);
            
            //! display filter result
            static void FilterOut(XMLog &,const size_t,const size_t);
        };


    }

}

#endif
