
//! \file

#ifndef Y_Exception_Included
#define Y_Exception_Included 1

#include "y/core/setup.hpp"
#include "y/check/printf.hpp"
#include <exception>
#include <iosfwd>

namespace Yttrium
{

    class Exception : public std::exception
    {
    public:
        // Definitions
        static const char * const CallSign; //!< "Exception;
        static const size_t       Length = 128;

        explicit Exception()         noexcept;
        Exception(const Exception &) noexcept;
        virtual ~Exception()         noexcept;
        explicit Exception(const char * const formatString,...)  noexcept Y_Printf_Check(2,3);


        virtual const char * what() const noexcept;
        const char *         when() const noexcept;
        void                 show(std::ostream &) const;
        void                 add(const char * const formatString,...) noexcept Y_Printf_Check(2,3);
        void                 pre(const char * const formatString,...) noexcept Y_Printf_Check(2,3);
        
    private:
        Y_Disable_Assign(Exception);
        char tell[Length];

        void clear() noexcept; //!< erase story
    };

}

#endif
