
//! \file

#ifndef Y_Memory_Object_Factory_API_Included
#define Y_Memory_Object_Factory_API_Included 1

#include "y/concurrent/life-time.hpp"

namespace Yttrium
{
    namespace Memory
    {
        namespace Object
        {

            //__________________________________________________________________
            //
            //
            //
            //! low-level Factory content and methods
            //
            //
            //__________________________________________________________________

            class FactoryAPI
            {
            public:
                static const char * const              CallSign; //!< "Memory::Object::Factory"
                static const System::AtExit::Longevity LifeTime = LifeTimeOf::MemoryObjectFactory; //!< life time
                class Code;

                //! cleanup
                virtual ~FactoryAPI() noexcept;

            protected:
                //! parametric setup
                /**
                 \param userPageBytes Factory::PAGE_SIZE
                 */
                explicit FactoryAPI(const size_t userPageBytes);
                Code * const code; //!< singleton code

                //! display for all internal elements
                void     displayAll(std::ostream &,size_t) const;

            private:
                Y_Disable_Copy_And_Assign(FactoryAPI); //!< discading
            };

        }
    }

}

#endif

