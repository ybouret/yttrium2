
//! \file

#ifndef Y_XMLog_Included
#define Y_XMLog_Included 1

#include "y/xml/element.hpp"
#include "y/xml/attribute.hpp"
#include "y/string.hpp"

namespace Yttrium
{

    class XMLog
    {
    public:
        explicit XMLog(std::ostream &, bool & ) noexcept;
        virtual ~XMLog() noexcept;

        std::ostream  & operator()(void) noexcept;

        bool          & verbose;
        size_t          depth;
        std::ostream  & os;      //!< output stream

        
        class Section
        {
        public:
            template <typename NAME>
            explicit Section(XMLog &xmlog, const NAME &name, const bool partial=false) :
            xml(xmlog),
            str(xml.verbose ? new String(name) : 0)
            {
                init(partial);
            }

            void quit();


            virtual ~Section() noexcept;


        private:
            Y_Disable_Copy_And_Assign(Section);
            void           init(const bool);
            XMLog   &      xml;
            String * const str;
        };

    private:
        Y_Disable_Copy_And_Assign(XMLog);
    };

#define Y_XMLog(XML,MSG) do { if(xml.verbose) { XML() << MSG << std::endl; } } while(false)


    //! create the guard name
#define Y_XML_Section__(X,Y) X##Y

    //! instantiate the guard name
#define Y_XML_Section_(HOST,NAME,ID) volatile Yttrium::XMLog::Section  Y_XML_Section__(__xmlSection,ID)(HOST,NAME)

    //! use a local ScopedLock to lock HOST
#define Y_XML_Section(HOST,NAME) Y_XML_Section_(HOST,NAME,__LINE__)

}


#endif

