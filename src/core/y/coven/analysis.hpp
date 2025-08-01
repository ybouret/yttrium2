
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

            static unsigned Width; //!< helper for format
            static const char * const CallSign;
            static const char * const And;
            static const char * const Filter;

            //! embedded analysis method
            template <typename MATRIX> static inline
            void Run(XMLog        & xml,
                     const MATRIX & matrix,
                     Survey &       survey,
                     const bool     optimize)
            {
                Y_XML_Section_Attr(xml,CallSign, Y_XML_Attr(matrix.rows) << Y_XML_Attr(matrix.cols));
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
                        Y_XML_Section(xml,"Summary");
                        Y_XMLog(xml, "#configuration  : " << std::setw(Width)  << tribes.cardinal);
                        Y_XMLog(xml, "#generated      : " << std::setw(Width)  << generated);
                        Y_XMLog(xml, "#issuedVectors  : " << std::setw(Width)  << survey.calls);
                        Y_XMLog(xml, "#uniqueVectors  : " << std::setw(Width)  << survey->size);
                    }
                }

            }

            template <typename MATRIX, typename IS_OK> static inline
            size_t Run(XMLog &        xml,
                       const MATRIX & matrix,
                       IS_OK &        keep,
                       Survey &       survey,
                       const bool     optimize)
            {
                Y_XML_Section_Attr(xml,CallSign,And<<Filter);
                { Run(xml,matrix,survey,optimize); }
                {
                    Y_XML_Section(xml,Filter);
                    const size_t oldSize = survey->size;
                    const size_t newSize = survey.retain(xml,keep);
                    Y_XMLog(xml, "#initial  : " << std::setw(Width) << oldSize);
                    Y_XMLog(xml, "#selected : " << std::setw(Width) << newSize);
                    return newSize;
                }
            }

        };


    }

}

#endif
