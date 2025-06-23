
//!\ file


#ifndef Y_String_Core_Included
#define Y_String_Core_Included 1

#include "y/object.hpp"
#include "y/container/contiguous.hpp"
#include "y/ability/legacy-string.hpp"
#include "y/string/fwd.hpp"
#include "y/type/sign.hpp"

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
        public LegacyString, public Contiguous< Writable<T> >
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef Stride<T> Code; //!< alias

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

            friend std::ostream & operator<< <>(std::ostream &, const String &);

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual size_t       size()     const noexcept;
            virtual size_t       capacity() const noexcept;
            virtual const char * c_str()    const noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            String & pushAtTail(const T *const, const size_t);
            String & pushAtTail(const T *const);
            String & pushAtTail(const String &);
            String & pushAtTail(const T);


            String & pushAtHead(const T *const, const size_t);
            String & pushAtHead(const T *const);
            String & pushAtHead(const String &);
            String & pushAtHead(const T);



            inline String & operator += (const String &  rhs) { return pushAtTail(rhs); }
            inline String & operator += (const T * const rhs) { return pushAtTail(rhs); }
            inline String & operator += (const T         rhs) { return pushAtTail(rhs); }

            inline String & operator << (const String   & rhs) { return pushAtTail(rhs); }
            inline String & operator << (const T * const  rhs) { return pushAtTail(rhs); }
            inline String & operator << (const T          rhs) { return pushAtTail(rhs); }

            inline String & operator >> (const String  & rhs) { return pushAtHead(rhs); }
            inline String & operator >> (const T * const rhs) { return pushAtHead(rhs); }
            inline String & operator >> (const T         rhs) { return pushAtHead(rhs); }


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

            static SignType Compare(const String &, const String &) noexcept;

        private:
            Code * const code;
            virtual const T & getItemAt(const size_t) const noexcept;
        };

    }

}

#endif
