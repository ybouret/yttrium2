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
        class Source : public InputStream
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
            // Interface
            //
            //__________________________________________________________________
            virtual bool query(char &);
            virtual void store(char);
            
            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            void            endl() noexcept;              //!< signal endl to module

            Char *          get();                        //!< \return new char from module/buffer
            void            put(Char * const) noexcept;   //!< store into buffer
            void            put(Token &)     noexcept;    //!< store previously read
            void            dup(const Token &);           //!< store a copy of token

            bool            ready();                      //!< \return true if more char available
            void            fetch(size_t);                //!< prefetch chars
            size_t          cache()  const noexcept;      //!< \return buffer.size
            void            sweep(size_t n) noexcept;     //!< \param n n<=cached(), skipped
            const Char *    peek();                       //!< make ready \return best effort buffer head
            const Context & context() const noexcept;     //!< \return  current context
        private:
            Y_Disable_Copy_And_Assign(Source); //!< discarding
            ArcPtr<Module> handle;             //!< module handle
            Token          buffer;             //!< I/O buffer

        };
    }

}

#endif

