
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

        struct Analysis
        {

            static unsigned           Width; //!< helper for format
            static const char * const CallSign;
            static const char * const And;
            static const char * const Filter;

            enum RootPolicy
            {
                AcceptRoot,
                RejectRoot,
            };


            //! embedded analysis method
            template <typename MATRIX> static inline
            void Run(XMLog        &  xml,
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
            static void Summary(XMLog &        xml,
                                const Tribes & tribes,
                                const size_t   generated,
                                const Survey & survey);

            static void FilterOut(XMLog &xml, const size_t oldSize, const size_t newSize);
        };


    }

}

#endif
