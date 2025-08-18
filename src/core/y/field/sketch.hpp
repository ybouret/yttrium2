
//! \file

#ifndef Y_Field_Sketch_Included
#define Y_Field_Sketch_Included 1

#include "y/string.hpp"

namespace Yttrium
{

    namespace Field
    {

        //______________________________________________________________________
        //
        //
        //
        //! name and memory for fields
        //
        //
        //______________________________________________________________________
        class Sketch : public CountedObject
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup empty \param fieldName name
            template <typename UID>
            explicit Sketch(const UID & fieldName) :
            name(fieldName),
            wlen(0),
            wksp(0)
            {
            }

            //! setup with required memory
            /**
             \param fieldName name
             \param dataBytes items * sizeof(type)
            */
            template <typename UID>
            explicit Sketch(const UID &  fieldName,
                            const size_t dataBytes) :
            name(fieldName),
            wlen(dataBytes),
            wksp( Make(wlen) )
            {
            }

            //! cleanup
            virtual ~Sketch() noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            const String & key() const noexcept; //!< \return name


            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const String   name; //!< identifier
        protected:
            size_t         wlen; //!< positive if standalone
            void *         wksp; //!< standalone memory

        private:
            Y_Disable_Copy_And_Assign(Sketch); //!< disarding
            static void * Make(size_t &);                     //!< \return acquired memory
            static void   Free(void * &, size_t &) noexcept;  //!< free memory
        };
    }

}

#endif

