//! \file

#ifndef Y_Vizible_Included
#define Y_Vizible_Included 1

#include "y/string/fwd.hpp"
#include "y/core/setup.hpp"

namespace Yttrium
{
    class OutputStream;

    class Vizible
    {
    public:
        static const char *Char[256];

        explicit Vizible() noexcept;
        virtual ~Vizible() noexcept;

        OutputStream & name(OutputStream &) const;
        OutputStream & to(const Vizible * const, OutputStream &fp) const;

        static OutputStream & Label(OutputStream &, const Core::String<char> &);
        static OutputStream & Label(OutputStream &, const char * const);
        static OutputStream & Label(OutputStream &, const char);
        static OutputStream & Endl(OutputStream &);

        static OutputStream & Enter(OutputStream &);
        static OutputStream & Leave(OutputStream &);

        template <typename CLASS> static inline
        OutputStream & Save(OutputStream &fp, const CLASS &obj)
        {
            return Leave( obj.viz( Enter(fp) ) );
        }

        static void DotToPng(const Core::String<char> &dotFile,const bool keepDot=false);
        static void DotToPng(const char * const,const bool keepDot=false);

        template <typename FILENAME, typename CLASS> static inline
        void SaveAs(const FILENAME &dotFile, const CLASS &obj)
        {
            OutputStream * const fp = NewDotFile(dotFile);
            try { Save(*fp,obj); DelDotFile(fp); }
            catch(...) { DelDotFile(fp); throw; }
        }

        template <typename FILENAME, typename CLASS> static inline
        void Render(const FILENAME &dotFile, const CLASS &obj, const bool keepDot=false)
        {
            SaveAs(dotFile,obj);
            DotToPng(dotFile,keepDot);
        }





    private:
        Y_Disable_Copy_And_Assign(Vizible);
        static OutputStream * NewDotFile(const Core::String<char> &);
        static OutputStream * NewDotFile(const char * const);
        static void           DelDotFile(OutputStream * const) noexcept;

    };
}

#endif

