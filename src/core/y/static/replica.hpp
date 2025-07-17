
//! \file

#ifndef Y_Static_Replica_Included
#define Y_Static_Replica_Included 1

#include "y/memory/stealth.hpp"
#include "y/calculus/alignment.hpp"
#include "y/type/args.hpp"
#include "y/type/destruct.hpp"
#include "y/type/copy-of.hpp"
#include <iostream>
#include <cstring>

namespace Yttrium
{
    namespace Static
    {

        //______________________________________________________________________
        //
        //
        //
        //! Make a static temporary object
        //
        //
        //______________________________________________________________________
        template <typename T>
        class Replica
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_Args_Declare(T,Type); //!< aliases
            static const unsigned Blocks = Alignment::WordsFor<T>::Count; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup emtpy
            inline Replica() noexcept : pointee(0), wksp()
            {
                clear();
            }

            //! cleanup
            inline ~Replica() noexcept
            {
                free();
            }

            //! setup \param value sent to constructor
            inline Replica(const ParamType value) :
            pointee(0),
            wksp()
            {
                new (pointee = static_cast<MutableType *>( clear() )) MutableType(value);
            }

            //! setup \param arg sent to constructor
            template <typename U>
            inline Replica(const CopyOf_&, const U &arg) :
            pointee(0),
            wksp()
            {
                new (pointee = static_cast<MutableType *>( clear() )) MutableType(arg);
            }

            //! assign new value \param value replacement value \return *this
            Replica & operator=(ParamType value)
            {
                Replica tmp(value);
                if(pointee) Destruct(pointee); else link();
                {
                    void ** target = wksp;
                    void ** source = tmp.wksp;
                    for(unsigned i=Blocks;i>0;--i)
                    {
                        *(target++) = *source;
                        *(source++) = 0;
                    }
                }
                tmp.pointee = 0;
                return *this;
            }

            //! display
            inline friend std::ostream & operator<<(std::ostream &os, const Replica &self)
            {
                if(self.pointee) os << *self.pointee; else os << Core::Nil;
                return os;
            }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! access \return valid content
            inline ConstType & operator*() const noexcept { assert(pointee); return *pointee; }


            //! tranfer memory \param addr target
            inline void yield(void * const addr) noexcept
            {
                assert(0!=addr);
                assert(0!=pointee);
                memcpy(addr,wksp,sizeof(T));
                reset();
            }

            //! free content
            inline void free() noexcept
            {
                if(pointee)
                {
                    Destruct(pointee);
                    reset();
                }
            }


            inline bool isEmpty() const noexcept { return 0==pointee; } //!< \return true iff empty
            inline bool isValid() const noexcept { return 0!=pointee; } //!< \return true iff valid


        private:
            MutableType * pointee;              //!< current pointee
            void *        wksp[Blocks];         //!< local memory
            Y_Disable_Copy_And_Assign(Replica); //!< discarding

            //! \return cleared local memory
            inline void *clear() noexcept { return Y_Memory_BZero(wksp); }

            //! reset pointer and memory
            inline void  reset() noexcept
            {
                pointee = 0;
                clear();
            }

            //! link pointee to (untouched) memory
            inline void link() noexcept
            {
                pointee = static_cast<MutableType *>( Memory::Stealth::Address(wksp) );
            }


        };
    }

}

#endif

