//! \file

#ifndef Y_DLL_Included
#define Y_DLL_Included 1

#include "y/string.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Dynamically Linked Libary
    //
    //
    //_________________________________________________________________________
    class DLL
    {
    public:
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        DLL(const String &);       //!< load
        DLL(const char * const);   //!< load
        DLL(const DLL &) noexcept; //!< shared copy
        virtual ~DLL() noexcept;   //!< cleanup

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        void * query(const String &     symbol) const noexcept; //!< \param symbol symbol name \return symbol address
        void * query(const char * const symbol) const noexcept; //!< \param symbol symbol name \return symbol address

        //! load symbol with conversion
        /**
         \param symbol symbol name
         \return symbol address converted to PROC
         */
        template <typename PROC> inline
        PROC load(const String &symbol) const noexcept
        {
            union {
                void *addr;
                PROC  proc;
            } alias = { query(symbol) };
            return alias.proc;
        }


        //! load symbol with conversion, wrapper
        /**
         \param symbol symbol name
         \return symbol address converted to PROC
         */
        template <typename PROC> inline
        PROC load(const char * const symbol) const noexcept
        {
            const String _(symbol); return load<PROC>(_);
        }

    private:
        class Code;
        Y_Disable_Assign(DLL); //!< discarding
        Code * const code;     //!< inner handle
    };

}

#endif
