
//! \file

#ifndef Y_Jive_Analyzer_Included
#define Y_Jive_Analyzer_Included 1


#include "y/jive/syntax/grammar.hpp"
#include "y/functor.hpp"

namespace Yttrium
{
    namespace Jive
    {

        //______________________________________________________________________
        //
        //
        //! Analyzer behavior
        //
        //______________________________________________________________________
        enum Analysis
        {
            Exhaustive, //!< each aggregate/terminal must be processed
            Permissive  //!< walk thru
        };

        //______________________________________________________________________
        //
        //
        //
        //! Syntax::Node analyzer
        //
        //
        //______________________________________________________________________
        class Analyzer
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef Jive::Token               Token;        //!< alias
            typedef Functor<void,TL1(Token)>  TerminalProc; //!< process terminal
            typedef Functor<void,TL1(size_t)> InternalProc; //!< process internal

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
        protected:
            //! setup from grammar, analysis type and verbosity
            explicit Analyzer(const Syntax::Grammar &,
                              const Analysis = Exhaustive);
        public:
            //! cleanup
            virtual ~Analyzer() noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! walk down \param root top level node
            void walk(const XNode * const root);

            //! create process for terminal
            /**
             \param rid terminal name
             \param host host object
             \param meth host method pointer
             */
            template <typename RID, typename HOST, typename METH>
            void push(const RID &rid, HOST &host, METH meth)
            {
                const Tag          name(rid);
                const TerminalProc proc(&host,meth);
                on(name,proc);
            }

            //! create process for internal aggregate
            /**
             \param rid internal name
             \param host host object
             \param meth host method pointer
             */
            template <typename RID, typename HOST, typename METH>
            void func(const RID &rid, HOST &host, METH meth)
            {
                const Tag          name(rid);
                const InternalProc proc(&host,meth);
                on(name,proc);
            }

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const Syntax::Grammar &grammar; //!< persistent grammar
                                            //!
        private:
            class Code;
            Y_Disable_Copy_And_Assign(Analyzer); //!< discarding
            Code * const code; //!< inner code

            virtual void init()  = 0;  //!< initialize before walking
            virtual void quit()  = 0;  //!< finalize   after  walking
            virtual void show(const size_t) const; //!< called after push/func, do nothing is default

            void on(const Tag &, const TerminalProc &); //!< register callback
            void on(const Tag &, const InternalProc &); //!< register callback

        public:
            bool &verbose; //!< verbosity
        };


#define Y_Jive_Push(CLASS,ID) push(#ID,*this, & CLASS:: on##ID) //!< helper
#define Y_Jive_Func(CLASS,ID) func(#ID,*this, & CLASS:: on##ID) //!< helper

        //______________________________________________________________________
        //
        //
        //
        //! permissive, verbose Analyzer
        //
        //
        //______________________________________________________________________
        class Walker : public Analyzer
        {
        public:
            explicit Walker(const Syntax::Grammar &); //!< setup
            virtual ~Walker() noexcept;               //!< cleanup

        private:
            Y_Disable_Copy_And_Assign(Walker); //!< discarding
            virtual void init(); //!< do nothing
            virtual void quit(); //!< do nothing
        };
    }

}

#endif


