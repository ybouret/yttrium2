
//! \file

#ifndef Y_Jive_Pattern_Dictionary_Included
#define Y_Jive_Pattern_Dictionary_Included 1

#include "y/jive/pattern.hpp"

namespace Yttrium
{
    namespace Jive
    {
        //______________________________________________________________________
        //
        //
        //
        //! Dictionary of pre-compiled pattern
        //
        //
        //______________________________________________________________________
        class Dictionary : public CountedObject
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef ArcPtr<Dictionary> Pointer;
            
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Dictionary();          //!< setup
            virtual ~Dictionary() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            void operator()(const String &,     Pattern * const); //!< store a new pattern
            void operator()(const char * const, Pattern * const); //!< store a new pattern

            Pattern * query(const char * const) const; //!< \return cloned pattern, NULL if not found
            Pattern * query(const String &)     const; //!< \return cloned pattern, NULL if not found

        private:
            class Code;
            Y_Disable_Copy_And_Assign(Dictionary); //!< discarding
            Code * const code;                     //!< inner implementation
        };
    }

}

#endif


