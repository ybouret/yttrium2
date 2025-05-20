
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
        static const char * const CallSign;                           //!< "Exception;
        static const size_t       Length =128-sizeof(std::exception); //!< internal memory

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

    protected:
        char tell[Length];           //!< store context

    private:
        Y_Disable_Assign(Exception); //!< no assignment
        void clear() noexcept;       //!< erase tell

    };


    namespace Specific
    {
        //______________________________________________________________________
        //
        //
        //
        //! Information with specific reason
        //
        //
        //______________________________________________________________________
        class Exception : public Yttrium::Exception
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            virtual ~Exception() noexcept; //!< cleanup

            //! initialize
            /**
             \param title will be what()
             */
            explicit Exception(const char * title) noexcept;

            //! initialize
            /**
             \param title will be what()
             \param formatString to format when()
             */
            explicit Exception(const char * title,
                               const char * formatString,...) noexcept Y_Printf_Check(3,4);

            //! duplicate
            /** \param other source */
            Exception(const Exception &other)      noexcept;

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________

            //! [std::exception]
            /** \return info */
            virtual const char * what() const noexcept;

        protected:
            char info[Length]; //!< store information

        private:
            Y_Disable_Assign(Exception); //!< no assigment
        };

    }
}

#endif
