
#include "y/object/factory.hpp"
#include "y/check/usual.hpp"
#include <cstring>


namespace Yttrium
{
    Object:: ~Object() noexcept
    {
    }

    Object:: Object() noexcept
    {
    }

    namespace
    {
        static inline void * factoryQuery(const size_t blockSize)
        {
            static Object::Factory & factory = Object::Factory::Instance();
            assert(blockSize>0);
            return factory.query(blockSize);
        }

        static inline void factoryStore(void * const blockAddr, const size_t blockSize) noexcept
        {
            assert(blockSize>0);
            assert( Object::Factory::Exists() );
            static Object::Factory &factory = Object::Factory::Location();
            factory.store(blockAddr,blockSize);
        }
    }


    void * Object:: operator new(const size_t blockSize)
    {
        assert(blockSize>0);
        return factoryQuery(blockSize);
    }

    void Object:: operator delete(void * const blockAddr, const size_t blockSize) noexcept
    {
        assert( Good(blockAddr,blockSize) );
        if(blockSize>0)
            factoryStore(blockAddr,blockSize);
    }


    void * Object:: operator new[](const size_t blockSize)
    {
        assert(blockSize>0);
        return factoryQuery(blockSize);
    }

    void Object:: operator delete[](void * const blockAddr, const size_t blockSize) noexcept
    {
        assert( Good(blockAddr,blockSize) );
        if(blockSize>0)
            factoryStore(blockAddr,blockSize);
    }

    void * Object::operator new(const size_t blockSize, void * const blockAddr) noexcept
    {
        assert(blockSize>0);
        assert(0!=blockAddr);
        return memset(blockAddr,0,blockSize);
    }

    void Object:: operator delete(void *, void *) noexcept
    {}



}
