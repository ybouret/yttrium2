//! \file

#ifndef Y_LUAXX_STATE_INCLUDED
#define Y_LUAXX_STATE_INCLUDED 1

#include "y/string.hpp"
#include "y/pointer/arc.hpp"

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

namespace Yttrium
{
    namespace Lua
    {
        //______________________________________________________________________
        //
        //
        //! wrapper for lua_State
        //
        //______________________________________________________________________
        class State : public CountedObject
        {
        public:
            //__________________________________________________________________
            //
            // definition
            //__________________________________________________________________
            static const char dummy_name[]; //!< used for evaluation

            //__________________________________________________________________
            //
            // C++
            //__________________________________________________________________
            virtual ~State() noexcept; //!< lua_close
            explicit State();         //!< lua_newstate

            //__________________________________________________________________
            //
            // methods
            //__________________________________________________________________
            void getglobal(const String &); //!< clear/getglobal
            void getglobal(const char   *); //!< clear/getglobal

            void dofile(const String &);   //!< dofile
            void dofile(const char   *);   //!< dofile
            void dostring(const String &); //!< dostring
            void dostring(const char   *); //!< dostring

            //! conversion to lua_Integer/lua_Number/string
            template <typename T>
            T to(const int idx)
            {
                static const TypeToType<T> which = {};
                return to(which,idx);
            }

            //! return type at idx
            int type(const int idx) noexcept;


            //! getglobal and convert
            template <typename T> inline
            T get(const String &name) { getglobal(name); return to<T>(-1); }

            //! getglobal and convert
            template <typename T> inline
            T get(const char   *name) { getglobal(name); return to<T>(-1); }

            //! evaluate expression
            template <typename T> inline
            T eval(const String &expr)
            {
                set_dummy_name(expr);
                return get<T>(dummy_name);
            }

            //! evaluate expression
            template <typename T> inline
            T eval(const char *expr)
            {
                set_dummy_name(expr);
                return get<T>(dummy_name);
            }

            //! access operator
            lua_State * operator*() noexcept;

        private:
            Y_Disable_Copy_And_Assign(State);
            lua_State  *L;
            lua_Integer to(const TypeToType<lua_Integer> &, const int);
            lua_Number  to(const TypeToType<lua_Number>  &, const int);
            String      to(const TypeToType<String>      &, const int);
            void        set_dummy_name(const String &);
            void        set_dummy_name(const char   *);
        };

        //______________________________________________________________________
        //
        //
        //! shared lua state
        //
        //______________________________________________________________________
        typedef ArcPtr<State> VM;
    }
}

#endif

