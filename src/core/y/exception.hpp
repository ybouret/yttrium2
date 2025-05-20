
//! \file

#ifndef Y_Exception_Included
#define Y_Exception_Included 1

#include "y/core/setup.hpp"
#include "y/check/printf.hpp"
#include <exception>
#include <iosfwd>

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Base class for Exceptions
    //
    //
    //__________________________________________________________________________
    class Exception : public std::exception
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        static const char * const CallSign;       //!< "Exception;
        static const size_t       Length = 128;   //!< internal memory

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        explicit Exception()         noexcept; //!< setup emtpy
        Exception(const Exception &) noexcept; //!< duplicate
        virtual ~Exception()         noexcept; //!< cleanup

        //! C-style formatting
        /**
         \param formatString C-style format string
         */
        explicit Exception(const char * const formatString,...)  noexcept Y_Printf_Check(2,3);

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! reason of exception
        /**
         \return explanation string
         */
        virtual const char * what() const noexcept;

        //! context of exception
        /**
         \return information string
         */
        const char *         when() const noexcept;

        //! pretty display exception
        void                 show(std::ostream &) const;

        //! append formatted information
        /**
         \param formatString printf-like format string
         */
        void                 add(const char * const formatString,...) noexcept Y_Printf_Check(2,3);

        //! prepend formatted information
        /**
         \param formatString printf-like format string
         */
        void                 pre(const char * const formatString,...) noexcept Y_Printf_Check(2,3);
        
    private:
        Y_Disable_Assign(Exception); //!< no assignment
        char tell[Length];           //!< store context

        void clear() noexcept; //!< erase tell
    };

}

#endif
