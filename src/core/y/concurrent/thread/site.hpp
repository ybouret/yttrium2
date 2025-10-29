//! \file

#ifndef Y_Concurrent_Thread_Site_Included
#define Y_Concurrent_Thread_Site_Included 1

#include "y/protean/bare/heavy/list.hpp"
#include "y/type/ingress.hpp"
#include "y/string.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        typedef Protean::BareHeavyList<size_t> PList; //!< alias
        typedef PList::NodeType                PNode; //!< alias

        //______________________________________________________________________
        //
        //
        //
        //! Site for processor(s)
        //
        //
        //______________________________________________________________________
        class Site : public Ingress<const PList>
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign;        //!< "Concurrent::Site"
            static const char * const Y_NUM_THREADS;   //!< environment variable name
            static const char         COMMA = ',';     //!< alias
            static const char         COLON = ':';     //!< alias
            typedef TypeToType<Site>  Default_;        //!< alias
            static const Default_     Default;         //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            Site(const Default_ &); //!< setup to hardware or parsed environment variable if found


            //! setup linear case
            /**
             \param nprocs number of processors >= 1
             \param offset first processor index
             \param stride stride between processors >= 1
             */
            Site(const size_t nprocs, const size_t offset=0, const size_t stride=1);
            Site(const String &);           //!< parse
            Site(const Site &);             //!< duplicate
            Site & operator=(const Site &); //!< duplicate/swap \return *this
            virtual ~Site() noexcept;       //!< cleanup

        private:
            Y_Ingress_Decl(); //!< helper
            PList plist;      //!< processor(s) list

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            void parse(const String &); //!< parse string

            //! setup linear cases
            /**
             \param nprocs number of processors >= 1
             \param offset first processor index
             \param stride stride between processors >= 1
             */
            void setup(const size_t nprocs,
                       const size_t offset,
                       const size_t stride);

            void parseLinear(const String &); //!< parse nprocs:offset:stride
            void parseCalled(const String &); //!< parse index[,index]*
        };

    }
}

#endif // !Y_Concurrent_Thread_Site_Included

