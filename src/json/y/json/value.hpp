//! \file

#ifndef Y_JSON_Value_Included
#define Y_JSON_Value_Included 1

#include "y/string.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/pointer/arc.hpp"
#include "y/pointer/keyed.hpp"
#include "y/container/associative/hash/set.hpp"

namespace Yttrium
{

    namespace JSON
    {

        //______________________________________________________________________
        //
        //
        //
        //! Type of Value
        //
        //
        //______________________________________________________________________
        enum Type
        {
            IsString, //!< String
            IsNumber, //!< Number
            IsNull,   //!< Null
            IsTrue,   //!< True
            IsFalse,  //!< False
            IsArray,  //!< Array
            IsObject  //!< Object
        };

        typedef double Number;     //!< alias
        Y_Shallow_Decl(AsArray);   //!< alias
        Y_Shallow_Decl(AsObject);  //!< alias

        //______________________________________________________________________
        //
        //
        //
        //! Variant Value
        //
        //
        //______________________________________________________________________
        class Value
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            virtual ~Value() noexcept;        //!< cleanup
            Value(const Value &);             //!< copy
            Value & operator=(const Value &); //!< assign \return *this
            
            Value() noexcept;           //!< IsNull
            Value(const String &);      //!< IsString
            Value(const char   *);      //!< IsString
            Value(const bool) noexcept; //!< Is[True|False]
            Value(const Number);        //!< IsNumber

            Value(const AsArray_  &);   //!< IsArray
            Value(const AsObject_ &);   //!< IsObject

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            void  xch(Value &) noexcept;                         //!< swap contents
            void  nullify()    noexcept;                         //!< clear content
            std::ostream & display(std::ostream &) const;        //!< display \return stream
            Y_OSTREAM_PROTO(Value);                              //!< default display
            template <typename T> const T & as() const noexcept; //!< \return access data

            //! access data, mutable \return data
            template <typename T> inline
            T & as() noexcept
            {
                const Value &self = *this;
                const T     &cstv = self.as<T>();
                return Coerce(cstv);
            }

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const Type type;  //!< type
        private:
            void       *impl; //!< opaque data

        };

        //______________________________________________________________________
        //
        //
        //
        //! Array = Vector of Values
        //
        //
        //______________________________________________________________________
        class Array : public Vector<Value>
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Array()     noexcept;    //!< setup
            virtual ~Array()     noexcept;    //!< cleanup
            explicit Array(const Array &);    //!< copy
            Array & operator=(const Array &); //!< assign \return *this

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            void add(Value &);                            //!< steal value, pushed
            std::ostream & display(std::ostream &) const; //!< display \return stream
        };


        //______________________________________________________________________
        //
        //
        //
        //! Pair key/value for Object
        //
        //
        //______________________________________________________________________
        class Pair : public Yttrium::Object, public Counted
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Pair(const String &); //!< setup with null value
            virtual ~Pair() noexcept;      //!< cleanup
            Y_OSTREAM_PROTO(Pair);         //!< output

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            const String & key() const noexcept; //!< \return key

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const String k; //!< key
            Value        v; //!< value
            
        private:
            Y_Disable_Copy_And_Assign(Pair); //!< discarding
        };

        typedef Keyed<String, ArcPtr<Pair> > SharedPair; //!< alias
        typedef HashSet<String,SharedPair>   Pairs;      //!< alias


        //______________________________________________________________________
        //
        //
        //
        //! Object = Set of SharedPairs
        //
        //
        //______________________________________________________________________
        class Object : public Pairs
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Object();                  //!< create
            virtual ~Object() noexcept;         //!< cleanup
            explicit Object(const Object &);    //!< copy
            Object & operator=(const Object &); //!< \return *this

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            std::ostream & display(std::ostream &)      const; //!< display \return stream
            Value &       operator[](const String &key);       //!< get/create (null) Value \param key key \return value
            const Value & operator[](const String &key) const; //!< get existing Value \param key key \return existing value

        };

    }

}

#endif

