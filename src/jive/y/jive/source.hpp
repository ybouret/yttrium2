//! \file

#ifndef Y_Jive_Source_Included
#define Y_Jive_Source_Included 1

#include "y/jive/token.hpp"
#include "y/jive/module.hpp"

namespace Yttrium
{
    namespace Jive
    {

        //______________________________________________________________________
        //
        //
        //
        //! Buffered source of Char from a Module
        //
        //
        //______________________________________________________________________
        class Source
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Source(Module * const) noexcept; //!< setup from module
            virtual ~Source()               noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            void endl() noexcept; //!< signal endl to module


            Char * query();                      //!< query new char from module/buffer
            void   store(Char * const) noexcept; //!< store into buffer
            void   store(Token &token) noexcept; //!< store previously read
            void   stash(const Token &token);    //!< store a copy of token
            bool   ready();                      //!< check if more char available
            void   fetch(size_t);                //!< prefetch chars
            size_t cache()  const noexcept; //!< \return buffer.size
            void   sweep(size_t n) noexcept; //!< \param n<=cached(), skipped


        private:
            Y_Disable_Copy_And_Assign(Source);
            ArcPtr<Module> handle;
            Token          buffer;

        };
    }

}

#endif

