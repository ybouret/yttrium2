

//! \file

#ifndef Y_Information_IOBits_Included
#define Y_Information_IOBits_Included 1

#include "y/information/iobit.hpp"
#include "y/protean/proto/list.hpp"
#include "y/container.hpp"
#include "y/threading/multi-threaded-object.hpp"
#include "y/ability/recyclable.hpp"

namespace Yttrium
{
    namespace Information
    {

        //______________________________________________________________________
        //
        //
        //! prototype
        //
        //______________________________________________________________________
        typedef Protean::ListProto<IOBit,IOBit::Cache &,Container,MultiThreadedObject> IOBitsProto;


        //______________________________________________________________________
        //
        //
        //
        //! List of IOBits with unique shared cache
        //
        //
        //______________________________________________________________________
        class IOBits : public IOBitsProto, public Recyclable
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //______________________________________________________________________
            explicit IOBits();                   //!< setup
            virtual ~IOBits() noexcept;          //!< cleanup
            IOBits(const IOBits & );             //!< duplicate
            IOBits & operator=(const IOBits & ); //!< assign \return *this

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


#endif // !Y_Information_IOBits_Included

