
//!\ file


#ifndef Y_String_Core_Included
#define Y_String_Core_Included 1

#include "y/object.hpp"

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
            String(const T * const);
            String(const T * const, const size_t);
            
        private:
            Code * const code;
        };

    }

}

#endif
