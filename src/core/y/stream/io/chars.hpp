
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

        //______________________________________________________________________
        //
        //
        //! prototype
        //
        //______________________________________________________________________
        typedef Protean::ListProto<Char,Char::Cache &,Container,MultiThreadedObject> CharsProto;


        //______________________________________________________________________
        //
        //
        //
        //! List of Chars with unique shared cache
        //
        //
        //______________________________________________________________________
        class Chars : public CharsProto, public Recyclable
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Chars();                  //!< setup
            virtual ~Chars() noexcept;         //!< cleanup
            Chars(const Chars & );             //!< duplicate
            Chars & operator=(const Chars & ); //!< assign \return *this

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            virtual void free() noexcept; //!< free content
        };
    }
}


#endif // !Y_Stream_IO_Chars_Included

