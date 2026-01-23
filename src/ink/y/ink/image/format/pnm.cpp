
#include "y/ink/image/format/pnm.hpp"
#include "y/system/exception.hpp"

namespace Yttrium
{
    namespace Ink
    {

     



        const char * const FormatPNM:: CallSign  = "PNM";
        const char * const FormatPNM:: Extension = "p[bgp]m";

        FormatPNM::  FormatPNM() : Format(CallSign,Extension) {}
        FormatPNM:: ~FormatPNM() noexcept {}

        FormatPNM:: Kind FormatPNM:: GetKind(const String &lowerCaseExt, const bool binary)
        {
            if("pbm" == lowerCaseExt) return binary ? P4 : P1;
            if("pgm" == lowerCaseExt) return binary ? P5 : P2;
            if("ppm" == lowerCaseExt) return binary ? P6 : P3;
            throw Specific::Exception(CallSign, "invalid extension '%s'", lowerCaseExt.c_str());
        }




    }
}

