

//! \file

#ifndef Y_String_Tokenizer_Included
#define Y_String_Tokenizer_Included 1

#include "y/core/setup.hpp"
#include "y/string/fwd.hpp"

namespace Yttrium
{

    namespace Core {
        

        //______________________________________________________________________
        //
        //
        //
        //! Tokenizer
        //
        //
        //______________________________________________________________________
        template <typename T>
        class Tokenizer
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Tokenizer(const T *, const size_t); //!< setup
            explicit Tokenizer(const T *);               //!< setup
            explicit Tokenizer(const String<T> &);       //!< setup
            virtual ~Tokenizer() noexcept;               //!< cleanup

            //__________________________________________________________________
            //
            //
            // methods
            //
            //__________________________________________________________________
            const T *    token() const noexcept; //!< \return current token location
            size_t       units() const noexcept; //!< \return current token size

            bool         next(const T * const sep, const size_t num) noexcept; //!< \param sep separators \param num |sep| \return found next
            bool         next(const T *)                             noexcept; //!< \return found next
            bool         next(const T)                               noexcept; //!< \return found next
            bool         next(const String<T> &)                     noexcept; //!< \return found next

            //! split src and append tokens to sequence-like container
            /**
             \param seq target sequence
             \param src source string
             \param sep separators
             \param num number of separator
             \param imax limit count if positive
             */
            template <typename SEQUENCE> static inline
            void AppendTo(SEQUENCE        &seq,
                          const String<T> &src,
                          const T * const  sep,
                          const size_t     num,
                          const int        imax=-1)
            {
                Tokenizer _(src);
                int       i=0;
                while( _.next(sep,num) ) {
                    ++i;
                    if(imax>=0 && i>imax) return;
                    const String<T> s(_.token(),_.units());
                    seq << s;
                }
            }

            //! split src and append all possible tokens to seq
            /**
             \param seq target sequence
             \param str source string
             \param sep separators
             */
            template <typename SEQUENCE> static inline
            void AppendTo(SEQUENCE        &seq,
                          const String<T> &str,
                          const T * const sep)
            {
                AppendTo<SEQUENCE>(seq,str,sep,Length(sep),-1);
            }

            //! split src and append all possible tokens to seq
            /**
             \param seq target sequence
             \param str source string
             \param sep separators
             */
            template <typename SEQUENCE> static inline
            void AppendTo(SEQUENCE        &seq,
                          const String<T> &str,
                          const String<T> &sep)
            {
                AppendTo<SEQUENCE>(seq,str,sep.c_str(),sep.size(),-1);
            }
            
            //! split src and append all possible tokens to seq
            /**
             \param seq target sequence
             \param str source string
             \param sep separator
             */
            template <typename SEQUENCE> static inline
            void AppendTo(SEQUENCE        &seq,
                          const String<T> &str,
                          const T          sep)
            {
                AppendTo<SEQUENCE>(seq,str,&sep,1,-1);
            }




        private:
            Y_Disable_Copy_And_Assign(Tokenizer); //!< discarding
            class Code;
            Code *code; //!< inner code
        };
    }

    typedef Core::Tokenizer<char> Tokenizer; //!< alias


}

#endif

