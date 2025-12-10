
//!\ file


#ifndef Y_String_Core_Included
#define Y_String_Core_Included 1

#include "y/object/counted.hpp"
#include "y/container/contiguous.hpp"
#include "y/ability/legacy-string.hpp"
#include "y/string/fwd.hpp"
#include "y/type/sign.hpp"
#include "y/ability/serializable.hpp"
#include "y/container/sequence.hpp"
#include "y/container/expandable.hpp"
#include "y/type/with-at-least.hpp"
#include "y/memory/buffer/ro.hpp"
#include "y/ability/random-access.hpp"

namespace Yttrium
{

    namespace Core
    {
        template <typename> class Stride;

        template <typename T> String<T> operator+(const String<T> &, const String<T> &);   //!< forward declaration
        template <typename T> String<T> operator+(const String<T> &, const T * const);     //!< forward declaration
        template <typename T> String<T> operator+(const String<T> &, const T);             //!< forward declaration
        template <typename T> String<T> operator+(const T, const String<T> &);             //!< forward declaration
        template <typename T> String<T> operator+(const T * const, const String<T> &);     //!< forward declaration

        template <typename T> bool      operator==(const String<T> &, const String<T> &) noexcept; //!< forward declaration
        template <typename T> bool      operator==(const T *   const, const String<T> &) noexcept; //!< forward declaration
        template <typename T> bool      operator==(const String<T> &, const T *   const) noexcept; //!< forward declaration
        template <typename T> bool      operator==(const String<T> &, const T)           noexcept; //!< forward declaration
        template <typename T> bool      operator==(const T, const String<T> &)           noexcept; //!< forward declaration


        template <typename T> bool      operator!=(const String<T> &, const String<T> &) noexcept; //!< forward declaration
        template <typename T> bool      operator!=(const T *   const, const String<T> &) noexcept; //!< forward declaration
        template <typename T> bool      operator!=(const String<T> &, const T *   const) noexcept; //!< forward declaration
        template <typename T> bool      operator!=(const String<T> &, const T)           noexcept; //!< forward declaration
        template <typename T> bool      operator!=(const T, const String<T> &)           noexcept; //!< forward declaration

        //______________________________________________________________________
        //
        //
        //
        //! generic string API
        //
        //
        //______________________________________________________________________
        template <typename T>
        class String :
        public CountedObject,
        public LegacyString,
        public Contiguous< Writable<T> >,
        public Sequence<T,Expandable>,
        public Serializable,
        public RandomAccess,
        public Memory::ReadOnlyBuffer
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef Stride<T>                 Code;           //!< alias
            typedef Contiguous< Writable<T> > ContiguousType; //!< alias
            typedef Sequence<T,Expandable>    SequenceType;   //!< alias
            Y_Args_Declare(T,Type);                           //!< aliases

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            String();                               //!< setup empty
            String(const String &);                 //!< duplicate
            String & operator=( const String & );   //!< assign \return *this*
            virtual ~String() noexcept;             //!< cleanup
            String(const T * const);                //!< setup from legacy string
            String(const T * const, const size_t);  //!< setup from legacy block
            String(const T * const, const size_t,
                   const T * const, const size_t);  //!< catenate two legacy blocks
            String(const T);                        //!< setup from single char

            String & operator=(const T * const);    //!< assing legacy string \return *this
            String & operator=(const T) noexcept;   //!< assign single char   \return *this*

            String(InputStream &, const char * const = 0); //!< load from serialized with optional variable name

            //! create a string with some room
            /**
             \param n minimal number of chars
             \param filled if true, set size to n
             */
            String(const WithAtLeast_ &, const size_t n, const bool filled);

            //! output dependending on T \return output stream
            inline friend std::ostream & operator<<(std::ostream &os, const String &self)
            {
                return self.print(os);
            }

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual size_t       size()     const noexcept; //!< [Container] \return size
            virtual size_t       capacity() const noexcept; //!< [Container] \return capacity
            virtual const char * c_str()    const noexcept;
            virtual size_t       serialize(OutputStream&) const;
            virtual void         free()    noexcept;
            virtual size_t       available() const noexcept;
            virtual void         pushTail(ParamType); //!< append char
            virtual void         pushHead(ParamType); //!< prepend char
            virtual void         popTail() noexcept;
            virtual void         popHead() noexcept;
            virtual void         reserve(const size_t n);
            virtual const void * ro()     const noexcept;
            virtual size_t       length() const noexcept;
            virtual void         remove(const size_t) noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            void     swapFor(String &) noexcept;               //!< no-throw content exchange

            String & pushAtTail(const T *const, const size_t); //!< push legacy block  \return *this
            String & pushAtTail(const T *const);               //!< push legacy string \return *this
            String & pushAtTail(const String &);               //!< push String        \return *this*
            String & pushAtTail(const T);                      //!< push single char   \return *this*


            String & pushAtHead(const T *const, const size_t);//!< push legacy block  \return *this
            String & pushAtHead(const T *const);              //!< push legacy string \return *this
            String & pushAtHead(const String &);              //!< push String        \return *this*
            String & pushAtHead(const T);                     //!< push single char   \return *this*



            inline String & operator += (const String &  rhs) { return pushAtTail(rhs); } //!< \param rhs string        \return *this += rhs
            inline String & operator += (const T * const rhs) { return pushAtTail(rhs); } //!< \param rhs legacy string \return *this += rhs
            inline String & operator += (const T         rhs) { return pushAtTail(rhs); } //!< \param rhs single char   \return *this += rhs

            inline String & operator << (const String   & rhs) { return pushAtTail(rhs); } //!< \param rhs string        \return *this += rhs
            inline String & operator << (const T * const  rhs) { return pushAtTail(rhs); } //!< \param rhs legacy string \return *this += rhs
            inline String & operator << (const T          rhs) { return pushAtTail(rhs); } //!< \param rhs single char   \return *this += rhs

            inline String & operator >> (const String  & lhs) { return pushAtHead(lhs); } //!< \param lhs legacy string  \return lhs + *this
            inline String & operator >> (const T * const lhs) { return pushAtHead(lhs); } //!< \param lhs single char    \return lhs + *this
            inline String & operator >> (const T         lhs) { return pushAtHead(lhs); } //!< \param lhs string         \return lhs + *this


            friend String<T> operator+<>(const String<T> &, const String<T> &);
            friend String<T> operator+<>(const String<T> &, const T *   const);
            friend String<T> operator+<>(const T *   const, const String<T> &);
            friend String<T> operator+<>(const String<T> &, const T);
            friend String<T> operator+<>(const T, const String<T> &);

            friend bool      operator==<>(const String<T> &, const String<T> &) noexcept;
            friend bool      operator==<>(const String<T> &, const T *   const) noexcept;
            friend bool      operator==<>(const T *   const, const String<T> &) noexcept;
            friend bool      operator==<>(const T, const String<T> &) noexcept;
            friend bool      operator==<>(const String<T> &, const T) noexcept;

            friend bool      operator!=<>(const String<T> &, const String<T> &) noexcept;
            friend bool      operator!=<>(const String<T> &, const T *   const) noexcept;
            friend bool      operator!=<>(const T *   const, const String<T> &) noexcept;
            friend bool      operator!=<>(const T, const String<T> &) noexcept;
            friend bool      operator!=<>(const String<T> &, const T) noexcept;

            static SignType Compare(const String &, const String &) noexcept; //!< \return lexicographic comparison

            String &       reverse()   noexcept; //!< reverse content \return *this
            const String & key() const noexcept; //!< self key \return *this

        private:
            Code * const code; //!< internal memory

            //! [Readable] \param indx valid index \return (*this)[indx]
            virtual const T & getItemAt(const size_t indx) const noexcept;

            virtual const T & getHead() const noexcept;
            virtual const T & getTail() const noexcept;
            std::ostream &    print(std::ostream &) const; //!< helper for display \return output stream

        };

    }

}

#endif // !Y_String_Core_Included
