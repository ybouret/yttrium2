
//! \file

#ifndef Y_XML_Output_Included
#define Y_XML_Output_Included 1

#include "y/xml/format.hpp"
#include "y/ability/identifiable.hpp"

namespace Yttrium
{
    namespace XML
    {

        class Output : public Identifiable
        {
        protected:
            explicit Output() noexcept;
        public:
            virtual ~Output() noexcept;

            

            virtual void display(std::ostream &os,
                                 const size_t &indentation) const = 0;

        private:
            Y_Disable_Copy_And_Assign(Output);
        };

    }
}

#endif
