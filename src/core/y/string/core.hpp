
//!\ file


#ifndef Y_String_Core_Included
#define Y_String_Core_Included 1

#include "y/object.hpp"
#include "y/container.hpp"

namespace Yttrium
{

    namespace Core
    {
        template <typename> class Stride;

        template <typename T>
        class String
        {
        public:
            typedef Stride<T> Code;
            String();
            String(const String &);
            String & operator=( const String & );
            virtual ~String() noexcept;

            String(const T * const, const size_t);
            String(const T * const, const size_t,
                   const T * const, const size_t);


            // Interface
            virtual size_t size()     const noexcept;
            virtual size_t capacity() const noexcept;

        private:
            Code * const code;
        };
        
    }

}

#endif
