
//! \file

#ifndef Y_Field_Sketch_Included
#define Y_Field_Sketch_Included 1

#include "y/string.hpp"

namespace Yttrium
{

    namespace Field
    {

        
        class Sketch : public CountedObject
        {
        public:
            template <typename UID>
            explicit Sketch(const UID & fieldName) :
            name(fieldName),
            wlen(0),
            wksp(0)
            {
            }

            template <typename UID>
            explicit Sketch(const UID &  fieldName,
                            const size_t dataBytes) :
            name(fieldName),
            wlen(dataBytes),
            wksp( Make(wlen) )
            {
            }

            virtual ~Sketch() noexcept;

            const String & key() const noexcept;

            const String   name;
        protected:
            size_t         wlen;
            void *         wksp;

        private:
            Y_Disable_Copy_And_Assign(Sketch);
            static void * Make(size_t &);
            static void   Free(void * &, size_t &) noexcept;
        };
    }

}

#endif

