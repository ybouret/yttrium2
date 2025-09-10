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


        class RTTI : public CountedObject
        {
        public:
            class DataBase;
            
            class Alias : public String
            {
            public:
                typedef CxxListOf<Alias> List;

                explicit Alias(const String &);
                explicit Alias(const char * const);
                virtual ~Alias() noexcept;
                
                Alias *next;
                Alias *prev;
            private:
                Y_Disable_Copy_And_Assign(Alias);
            };

            
            typedef ArcPtr<RTTI>          PtrType;
            typedef Keyed<String,PtrType> Pointer;
            
            explicit RTTI(const std::type_info &);
            virtual ~RTTI() noexcept;

            
            const String & key()  const noexcept;
            const String & name() const noexcept;
            RTTI &         aka(const String &);
            RTTI &         aka(const char * const);

            static RTTI & Get(const std::type_info &);

            template <typename T> inline
            static RTTI & Get() {
                static RTTI & _ = Get( typeid(T) );
                return _;
            }

            template <typename T> inline
            static const String & Name()
            {
                static RTTI & _ = Get<T>();
                return _.name();
            }





            const String         uuid;
            const Alias::List    aliases;



        private:
            Y_Disable_Copy_And_Assign(RTTI);
        };
    }

}

#endif

