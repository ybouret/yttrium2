#include "y/apex/k/device.hpp"

namespace Yttrium
{
    namespace Apex
    {
        size_t Device:: srz(OutputStream &fp) const
        {
            const Parcel<uint8_t> &p = make<uint8_t>();
            size_t res = fp.emitVBR(p.size);
            fp.frame(p.data,p.size);
            return res + p.size;
        }
        

    }

}

