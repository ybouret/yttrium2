
#include "y/chemical/plexus/solver.hpp"
#include "y/stream/libc/output.hpp"
#include "y/mkl/numeric.hpp"
#include "y/mkl/api/almost-equal.hpp"
#include "y/mkl/opt/optimize.hpp"
#include "y/jive/vfs.hpp"
#include "y/vfs/local/fs.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        void Solver:: kinetic(XMLog & xml)
        {
            Y_XMLog(xml, "kinetic");
            
        }

    }

}

