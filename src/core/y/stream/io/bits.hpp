

//! \file

#ifndef Y_IO_Bits_Included
#define Y_IO_Bits_Included 1

#include "y/stream/io/bit.hpp"
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
        typedef Protean::ListProto<Bit,Bit::Cache &,Container,MultiThreadedObject> BitsProto;


        //______________________________________________________________________
        //
        //
        //
        //! List of IOBits with unique shared cache
        //
        //
        //______________________________________________________________________
        class Bits : public BitsProto, public Recyclable
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //______________________________________________________________________
            explicit Bits();                   //!< setup
            virtual ~Bits() noexcept;          //!< cleanup
            Bits(const Bits & );             //!< duplicate
            Bits & operator=(const Bits & ); //!< assign \return *this

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


#endif // !Y_IO_Bits_Included

