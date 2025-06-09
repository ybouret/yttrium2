//! \file

#ifndef Y_Memory_Purgatory_Included
#define Y_Memory_Purgatory_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Memory
    {
        template <typename T>
        class Purgatory
        {
        protected:
            inline explicit Purgatory() noexcept {}
            inline virtual ~Purgatory() noexcept {}

        public:
            virtual void zombify(T * const object) noexcept = 0;
            virtual T *  recover()                          = 0;
            virtual T *  reenact(const T &object)           = 0;

        private:
            Y_Disable_Copy_And_Assign(Purgatory);
        };

#define Y_Purgatory_Recover(BUILD) do { \
/**/  void * const addr = deadPool.query();\
/**/    try {\
/**/      return new (addr) BUILD;\
/**/    }\
/**/    catch(...)\
/**/    {\
/**/      deadPool.store(addr);\
/**/      throw;\
/**/  }\
} while(false)

    }
}

#endif
