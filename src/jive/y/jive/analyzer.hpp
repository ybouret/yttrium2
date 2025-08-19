
//! \file

#ifndef Y_Jive_Analyzer_Included
#define Y_Jive_Analyzer_Included 1


#include "y/jive/syntax/grammar.hpp"
#include "y/functor.hpp"

namespace Yttrium
{
    namespace Jive
    {

        enum Analysis
        {
            Exhaustive,
            Permissive
        };

        class Analyzer
        {
        public:
            typedef Functor<void,TL1(Token)>  TerminalProc;
            typedef Functor<void,TL1(size_t)> InternalProc;

        protected:
            explicit Analyzer(const Syntax::Grammar &,
                              const Analysis,
                              const bool=false);
        public:
            virtual ~Analyzer() noexcept;

            void operator()(const XNode * const root);

            template <typename RID, typename HOST, typename METH>
            void push(const RID &rid, HOST &host, METH meth)
            {
                const Tag          name(rid);
                const TerminalProc proc(&host,meth);
                on(name,proc);
            }

            template <typename RID, typename HOST, typename METH>
            void call(const RID &rid, HOST &host, METH meth)
            {
                const Tag          name(rid);
                const InternalProc proc(&host,meth);
                on(name,proc);
            }

            const Syntax::Grammar &grammar;
            
        private:
            class Code;
            Y_Disable_Copy_And_Assign(Analyzer);
            Code * const code;

            virtual void init() = 0;
            virtual void quit() = 0;

            void on(const Tag &, const TerminalProc &);
            void on(const Tag &, const InternalProc &);

        public:
            bool &verbose;
        };

#define Y_Jive_Push(CLASS,ID) push(#ID,*this, & CLASS:: on##ID)
#define Y_Jive_Call(CLASS,ID) call(#ID,*this, & CLASS:: on##ID)

        class Walker : public Analyzer
        {
        public:
            explicit Walker(const Syntax::Grammar &);
            virtual ~Walker() noexcept;

        private:
            Y_Disable_Copy_And_Assign(Walker);
            virtual void init();
            virtual void quit();
        };
    }

}

#endif


