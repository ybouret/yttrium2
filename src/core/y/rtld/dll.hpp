//! \file

#ifndef Y_DLL_Included
#define Y_DLL_Included 1

#include "y/string.hpp"

namespace Yttrium
{


    class DLL
    {
    public:
        DLL(const String &);
        DLL(const char * const);
        DLL(const DLL &) noexcept;
        virtual ~DLL() noexcept;

        void * query(const String &     symbol) const noexcept;
        void * query(const char * const symbol) const noexcept;

        template <typename PROC> inline
        PROC load(const String &symbol) const noexcept
        {
            union {
                void *addr;
                PROC  proc;
            } alias = { query(symbol) };
            return alias.proc;
        }

        template <typename PROC> inline
        PROC load(const char * const symbol) const noexcept
        {
            const String _(symbol); return load<PROC>(_);
        }

    private:
        class Code;
        Y_Disable_Assign(DLL);
        Code * const code;
    };

}

#endif
