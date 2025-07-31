
//! \file
//!
#ifndef Y_Coven_Analysis_Included
#define Y_Coven_Analysis_Included 1

#include "y/coven/tribes.hpp"
#include "y/functor.hpp"

namespace Yttrium
{

    namespace Coven
    {
        typedef Functor<size_t,TL2(XMLog &, const Survey)> Analyzer;

        template <typename MATRIX> inline
        size_t Analysis(XMLog        &xml,
                        const MATRIX &matrix,
                        Analyzer     &analyze,
                        const bool    optimize=true)
        {
            Y_XML_Section_Attr(xml,"Coven::Analysis",Y_XML_Attr(matrix.rows) << Y_XML_Attr(matrix.cols));
            if(matrix.cols<=0) return 0;
            Survey        survey;
            {
                QVector::Pool vpool(matrix.cols);
                QFamily::Pool fpool(vpool);
                IPool         ipool;
                Tribes        tribes(xml,matrix,ipool,fpool,&survey);
                size_t        generated = tribes.size;
                while(true)
                {
                    const size_t gen = tribes.generate(xml,matrix, &survey,optimize);
                    if(gen<=0) break;
                    generated += gen;
                }
                Y_XMLog(xml, "#configurations = " << generated);
            }
            Y_XMLog(xml, "survey size=" << survey->size << " / trial=" << survey.calls);
            return analyze(xml,survey);
        }


    }

}

#endif
