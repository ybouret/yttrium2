
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
            // Definitions
            //
            //__________________________________________________________________

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
            // interface
            //
            //__________________________________________________________________
            virtual Pattern *      clone()                    const = 0; //!< \return clone
            virtual bool           accepts(Token &, Source &) const = 0; //!< \return true if accepted
            virtual OutputStream & viz(OutputStream&)         const = 0; //!< save as GraphViz
            virtual FirstChars     firstChars()      const noexcept = 0; //!< \return first chars

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
                Coerce(self) = static_cast<DERIVED *>(*this);
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

#define Y_Jive_Pattern_Decl(MOTIF,A,B,C,D)                               \
/**/    class MOTIF : public Pattern                                     \
/**/    {                                                                \
/**/      public:                                                        \
/**/        inline virtual   ~MOTIF() noexcept {}                        \
/**/        inline Pattern *  clone() const { return new MOTIF(*this); } \
/**/        static const uint32_t UUID = Y_FOURCC(A,B,C,D)               \

#define Y_Jive_Pattern_End(MOTIF)                    \
/**/      private: MOTIF & operator=(const MOTIF &); \
/**/     }

#define Y_Jive_Pattern_API() \
/**/    virtual bool           accepts(Token &,Source &) const; \
/**/    virtual OutputStream & viz(OutputStream&)        const; \
/**/    virtual FirstChars     firstChars()     const noexcept; \
/**/    virtual size_t         serialize(OutputStream &) const

        typedef ArcPtr<Pattern>          Motif;
        typedef ListOfCloneable<Pattern> Patterns; //!< alias

    }

}

#endif
