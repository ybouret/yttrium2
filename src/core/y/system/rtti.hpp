//! \file

#ifndef Y_System_RTTI_Included
#define Y_System_RTTI_Included 1

#include <typeinfo>
#include "y/string.hpp"
#include "y/pointer/arc.hpp"
#include "y/pointer/keyed.hpp"
#include "y/core/linked/list/cxx.hpp"

namespace Yttrium
{

    namespace System
    {

        //______________________________________________________________________
        //
        //
        //
        //! Run Time Type Information
        //
        //
        //______________________________________________________________________
        class RTTI : public CountedObject
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            class DataBase;

            //__________________________________________________________________
            //
            //
            //! Alias
            //
            //__________________________________________________________________
            class Alias : public String
            {
            public:
                typedef CxxListOf<Alias> List;      //!< alias
                explicit Alias(const String &);     //!< setup
                explicit Alias(const char * const); //!< setup
                virtual ~Alias() noexcept;          //!< cleanup
                Alias *  next;                      //!< for list
                Alias *  prev;                      //!< for list
            private:
                Y_Disable_Copy_And_Assign(Alias);   //!< discarding
            };

            
            typedef ArcPtr<RTTI>          PtrType; //!< alias
            typedef Keyed<String,PtrType> Pointer; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            virtual ~RTTI() noexcept;                            //!< cleanup
            Y_OSTREAM_PROTO(RTTI);                               //!< display

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            const String & key()  const noexcept;                 //!< \return uuid
            const String & name() const noexcept;                 //!< \return uuid or first alias
            RTTI &         aka(const String &);                   //!< manual alias setup \return *this
            RTTI &         aka(const char * const);               //!< manual alias setup \return *this
            bool           called(const String &) const noexcept; //!< \return true if matches uuid of alias


            //! \return global RTTI
            template <typename T> inline
            static RTTI & Get() {
                static RTTI & _ = Get( typeid(T), sizeof(T) );
                return _;
            }

            //! \return global name
            template <typename T> inline
            static const String & Name()
            {
                static RTTI & _ = Get<T>();
                return _.name();
            }

            static void Display(std::ostream &); //!< display content

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const String         uuid;    //!< system uuid
            const size_t         bytes;   //!< bytes per item
            const Alias::List    aliases; //!< list of aliases

        private:
            Y_Disable_Copy_And_Assign(RTTI); //!< discarding
            friend class DataBase;
            explicit      RTTI(const std::type_info &, const size_t); //!< setup
            static RTTI &  Get(const std::type_info &, const size_t); //!< \return Get/Create RTTI

        };
    }

}

#endif // !Y_System_RTTI_Included

