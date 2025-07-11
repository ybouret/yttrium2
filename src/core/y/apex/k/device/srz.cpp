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

#include "y/pointer/auto.hpp"
#include "y/exception.hpp"
#include "y/format/decimal.hpp"

namespace Yttrium
{
    namespace Apex
    {
        Device * Device::Load(InputStream &fp, const char * const varName)
        {
            static const char fn[]     = "Apex::Load";
            const size_t      numBytes = fp.readVBR<size_t>(varName,"bytes");
            AutoPtr<Device>   device   = new Device(numBytes,Plan8);
            {
                Parcel<uint8_t> & p = device->get<uint8_t>();
                for(size_t i=0;i<numBytes;++i)
                {
                    if( 1 != fp.readCBR(p.data[i]) )
                    {
                        const char * const id = varName ? varName : "variable";
                        throw Specific::Exception(fn,"missing byte %s/%s of %s", Decimal(i+1).c_str(),Decimal(numBytes).c_str(),id);
                    }
                }
                p.size = numBytes;
                device->fix();
                if(numBytes != p.size) {
                    const char * const id = varName ? varName : "variable";
                    throw Specific::Exception(fn,"corrupted %s",id);
                }

            }
            return device.yield();
        }


    }

}

