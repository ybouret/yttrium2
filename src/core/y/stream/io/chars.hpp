
//! \file

#ifndef Y_Stream_IO_Chars_Included
#define Y_Stream_IO_Chars_Included 1

#include "y/stream/io/char.hpp"
#include "y/protean/proto/list.hpp"
#include "y/container.hpp"
#include "y/threading/multi-threaded-object.hpp"
#include "y/ability/recyclable.hpp"

namespace Yttrium
{
    namespace IO
    {


        typedef Protean::ListProto<Char,Char::Cache &,Container,MultiThreadedObject> CharsProto;


        class Chars : public CharsProto, public Recyclable
        {
        public:
            explicit Chars();
            virtual ~Chars() noexcept;
            Chars(const Chars & );
            Chars & operator=(const Chars & );
            virtual void free() noexcept;
        };
    }
}


#endif


