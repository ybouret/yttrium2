
#include "y/jive/pattern/posix.hpp"
#include "y/jive/pattern/all.hpp"
#include "y/pointer/auto.hpp"
#include "y/stream/input.hpp"
#include "y/system/exception.hpp"
#include <cerrno>

namespace Yttrium
{
    namespace Jive
    {

        namespace
        {
            static const char missing[] = "missing ";

            static inline Pattern * ReadByte(InputStream &fp, const FourCC &cc)
            {
                uint8_t code = 0;
                if( fp.readCBR(code) < sizeof(code) ) throw Libc::Exception(EIO,"%s%s code",missing,cc.c_str());
                return new Byte(code);
            }


            static inline Pattern * ReadNot(InputStream &fp, const FourCC &cc)
            {
                uint8_t code = 0;
                if( fp.readCBR(code) < sizeof(code) ) throw Libc::Exception(EIO,"%s%s code",missing,cc.c_str());
                return new Not(code);
            }


            static inline Pattern * ReadLump(InputStream &fp, const FourCC &cc)
            {
                uint8_t lower = 0;
                uint8_t upper = 0;
                if( fp.readCBR(lower) < sizeof(lower) ) throw Libc::Exception(EIO,"%s%s lower",missing,cc.c_str());
                if( fp.readCBR(upper) < sizeof(upper) ) throw Libc::Exception(EIO,"%s%s upper",missing,cc.c_str());
                return new Lump(lower,upper);
            }

            static inline Pattern * ReadOption(InputStream &fp)
            {
                const Motif motif = Pattern::ReadFrom(fp);
                return new Option(motif);
            }


            static inline Pattern * ReadRepeat(InputStream &fp, const FourCC &cc)
            {
                const size_t minCount = fp.readVBR<size_t>(cc.c_str(),"minCount");
                const Motif  motif = Pattern::ReadFrom(fp);
                return new Repeat(motif,minCount);
            }

            static inline Pattern * ReadAmount(InputStream &fp, const FourCC &cc)
            {
                const size_t minCount = fp.readVBR<size_t>(cc.c_str(),"minCount");
                const size_t maxCount = fp.readVBR<size_t>(cc.c_str(),"maxCount");
                const Motif  motif = Pattern::ReadFrom(fp);
                return new Amount(motif,minCount,maxCount);
            }

            template <typename LOGIC>
            static inline Pattern * ReadLogic(LOGIC * const p, InputStream &fp, const FourCC &cc)
            {
                assert(p!=0);
                AutoPtr<Pattern> motif = p;
                const size_t     n     = fp.readVBR<size_t>(cc.c_str(),"operands");
                for(size_t i=1;i<=n;++i)
                    p->pushTail( Pattern::ReadFrom(fp) );
                return motif.yield();
            }


        }


        Pattern * Pattern:: ReadFrom(InputStream &fp)
        {
            uint32_t id = 0;
            if( fp.readCBR(id) < sizeof(id) ) throw Libc::Exception(EIO,"%s Jive::Pattern UUID",missing);

            const FourCC cc(id);
            switch(id)
            {
                case Byte::UUID:  return ReadByte(fp,cc);
                case Not:: UUID:  return ReadNot(fp,cc);
                case Lump::UUID:  return ReadLump(fp,cc);

                case Option::UUID: return ReadOption(fp);
                case Repeat::UUID: return ReadRepeat(fp,cc);
                case Amount::UUID: return ReadAmount(fp,cc);

                case And::  UUID: return ReadLogic( new And(),  fp, cc);
                case Or::   UUID: return ReadLogic( new Or(),   fp, cc);
                case None:: UUID: return ReadLogic( new None(), fp, cc);

                default:
                    throw Specific::Exception("Pattern::ReadFrom","unexpected uuid='%s'",cc.c_str());
            }

            return 0;
        }

    }

}

