
//!\ file


#ifndef Y_String_Core_Included
#define Y_String_Core_Included 1

#include "y/object.hpp"
#include "y/container/contiguous.hpp"
#include "y/ability/legacy-string.hpp"
#include "y/string/fwd.hpp"
#include "y/type/sign.hpp"
#include "y/ability/serializable.hpp"

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
        template <typename T> std::ostream & operator<<(std::ostream &, const String<T> &);

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
        public LegacyString,
        public Contiguous< Writable<T> >,
        public Serializable
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef Stride<T> Code; //!< alias
            typedef Contiguous< Writable<T> > ContiguousType;
            
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

            //! output dependending on T \return output stream
            friend std::ostream & operator<< <>(std::ostream &, const String &);

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

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
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

        private:
            Code * const code; //!< internal memory

            //! [Readable] \param indx valid index \return (*this)[indx]
            virtual const T & getItemAt(const size_t indx) const noexcept;
        };

    }

}

#endif
