
//! \file

#ifndef Y_XMLog_Included
#define Y_XMLog_Included 1

#include "y/xml/element.hpp"
#include "y/xml/attribute.hpp"
#include "y/string.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! helper for XML like output log
    //
    //
    //__________________________________________________________________________
    class XMLog
    {
    public:
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup with persistent output and verbose
        explicit XMLog(std::ostream &, bool & ) noexcept;

        //! cleanup
        virtual ~XMLog() noexcept;

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________
        std::ostream  & operator()(void); //!< \return indented output stream
        void quit();                      //!< emit RANGLE

        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________
        bool          & verbose; //!< persistent verbosity
        size_t          depth;   //!< current depth
        std::ostream  & os;      //!< output stream


        //______________________________________________________________________
        //
        //
        //! Section
        //
        //______________________________________________________________________
        class Section
        {
        public:
            //! format helper
            enum Property
            {
                Normal,      //!< "<element>"
                Partial,     //!< "<element"
                Standalone   //!< "<element/>"
            };

            //! setup
            /**
             - prepare/emit element and increase depth
             \param xmlog host
             \param name  compatible name
             \param ppty  property
             */
            template <typename NAME>
            explicit Section(XMLog &xmlog, const NAME &name, const Property ppty) :
            xml(xmlog),
            str( xml.verbose ? new String(name) : 0),
            pty(ppty)
            {
                init();
            }

            //! decrease depth and close element
            virtual ~Section() noexcept;

        private:
            Y_Disable_Copy_And_Assign(Section); //!< discarding
            void           init();              //!< initial emit
            XMLog   &      xml;                 //!< host
            String * const str;                 //!< if verbosity
            const Property pty;                 //!< property
        };

    private:
        Y_Disable_Copy_And_Assign(XMLog); //!< discarding
    };

    //! helper to output indented message
#define Y_XMLog(XML,MSG) do { if(xml.verbose) { XML() << MSG << std::endl; } } while(false)


    //! create the section name
#define Y_XML_Section__(X,Y) X##Y

    //! instantiate the section name
#define Y_XML_Section_(HOST,NAME,PARTIAL,ID) volatile Yttrium::XMLog::Section  Y_XML_Section__(__xmlSection,ID)(HOST,NAME,PARTIAL)

    //! create a full section name
#define Y_XML_Section(HOST,NAME) Y_XML_Section_(HOST,NAME,Yttrium::XMLog::Section::Normal,__LINE__)

    //! create a seciton name with attributes
#define Y_XML_Section_Attr(HOST,NAME,ATTR) Y_XML_Section_(HOST,NAME,Yttrium::XMLog::Section::Partial,__LINE__);\
do { if(HOST.verbose) { HOST.os << ATTR; HOST.quit(); } } while(false)

}


#endif

