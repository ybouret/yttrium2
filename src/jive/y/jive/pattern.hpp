
//! \file

#ifndef Y_Jive_Pattern_Included
#define Y_Jive_Pattern_Included 1

#include "y/jive/source.hpp"
#include "y/core/linked/list/cloneable.hpp"
#include "y/graphviz/vizible.hpp"
#include "y/jive/pattern/first-chars.hpp"
#include "y/type/fourcc.hpp"
#include "y/object/counted.hpp"
#include "y/pointer/arc.hpp"

namespace Yttrium
{
    namespace Jive
    {
        //______________________________________________________________________
        //
        //
        //
        //! Pattern interface
        //
        //
        //______________________________________________________________________
        class Pattern : public CountedObject, public Vizible, public Serializable
        {
        public:
            

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Pattern(const uint32_t) noexcept; //!< setup with uuid
            virtual ~Pattern() noexcept;               //!< cleanup
            Pattern(const Pattern &) noexcept;         //!< copy all but self

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual Pattern *      clone()                    const = 0; //!< \return clone
            virtual bool           accepts(Token &, Source &) const = 0; //!< \return true if accepted
            virtual OutputStream & viz(OutputStream&)         const = 0; //!< save as GraphViz \return output stream
            virtual FirstChars     firstChars()      const noexcept = 0; //!< \return first chars
            virtual bool           strong()                   const = 0; //!< \return true if doesn't accept empty token
            virtual bool           univocal()                 const = 0; //!< \return true if non empty token is univocal

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            bool feeble() const; //!< \return true if accepts empty token
            bool flexible() const; //!< \return !univoca()

            bool             isBasic()  const noexcept;    //!< \return true is basic
            static Pattern * Optimize(Pattern * const);    //!< \return performed logic optimization
            static Pattern * ReadFrom(InputStream &);      //!< \return reloaded
            static Pattern * Insensitive(Pattern * const); //!< \return case insensitive pattern

            static Pattern * Among(const String &);        //!< \return Or'd
            static Pattern * Among(const char * const);    //!< \return Or'd
            static Pattern * Exact(const String &);        //!< \return And
            static Pattern * Exact(const char * const);    //!< \return And

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const uint32_t uuid; //!< identifier
            Pattern *      next; //!< for list
            Pattern *      prev; //!< for list
            void * const   self; //!< original type

        private:
            Y_Disable_Assign(Pattern); //!< discard

        protected:

            //! record self
            template <typename DERIVED> inline
            void I_am() noexcept {
                assert(DERIVED::UUID==uuid);
                Coerce(self) = static_cast<DERIVED *>(this);
            }
        public:

            //! \return derived from recorded self
            template <typename DERIVED> inline
            DERIVED *as() noexcept
            {
                assert(DERIVED::UUID==uuid);
                assert(self);
                return static_cast<DERIVED *>(self);
            }

            //! \return derived from recorded self
            template <typename DERIVED> inline
            const DERIVED *as() const noexcept
            {
                assert(DERIVED::UUID==uuid);
                assert(self);
                return static_cast<const DERIVED *>(self);
            }
        };


        //! helper to declare pattern
#define Y_Jive_Pattern_Decl(MOTIF,PATTERN, A,B,C,D)                             \
/**/    class MOTIF : public PATTERN                                            \
/**/    {                                                                       \
/**/      public:                                                               \
/**/        inline virtual          ~MOTIF() noexcept {}                        \
/**/        inline virtual Pattern * clone() const { return new MOTIF(*this); } \
/**/        static const uint32_t UUID = Y_FOURCC(A,B,C,D)                      \

        //! helper to declare pattern
#define Y_Jive_Pattern_End(MOTIF)                    \
/**/      private: MOTIF & operator=(const MOTIF &); \
/**/     }

        //! full pattern APU
#define Y_Jive_Pattern_API() \
/**/    virtual bool           accepts(Token &,Source &) const; \
/**/    virtual OutputStream & viz(OutputStream&)        const; \
/**/    virtual FirstChars     firstChars()     const noexcept; \
/**/    virtual size_t         serialize(OutputStream &) const; \
/**/    virtual bool           strong()                  const; \
/**/    virtual bool           univocal()                const

        typedef ArcPtr<Pattern>          Motif;    //!< alias
        typedef ListOfCloneable<Pattern> Patterns; //!< alias

    }

}

#endif
