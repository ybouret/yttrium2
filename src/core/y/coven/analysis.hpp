
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

        template <typename MATRIX> inline
        void Analysis(XMLog        & xml,
                      const MATRIX & matrix,
                      Survey &       survey,
                      const bool     optimize)
        {
            Y_XML_Section_Attr(xml,"Coven::Analysis", Y_XML_Attr(matrix.rows) << Y_XML_Attr(matrix.cols));
            survey.release();
            if(matrix.cols<=0) return;
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

                {
                    static const int w = 8;
                    Y_XML_Section(xml,"Summary");
                    Y_XMLog(xml, "#configuration  : " << std::setw(w)  << tribes.cardinal);
                    Y_XMLog(xml, "#generated      : " << std::setw(w)  << generated);
                    Y_XMLog(xml, "#issuedVectors  : " << std::setw(w)  << survey.calls);
                    Y_XMLog(xml, "#uniqueVectors  : " << std::setw(w)  << survey->size);
                }
            }

        }

        template <typename MATRIX, typename IS_OK> inline
        size_t Analysis(XMLog &        xml,
                        const MATRIX & matrix,
                        IS_OK &        keep,
                        Survey &       survey,
                        const bool     optimize)
        {
            Analysis(xml,matrix,survey,optimize);
            return survey.retain(xml,keep);
        }




    }

}

#endif
