
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
        static inline void * factoryAcquire(const size_t blockSize)
        {
            assert(blockSize>0);
            Object::Factory & factory = Object::Factory::Instance();
            return factory.acquire(blockSize);
        }

        static inline void factoryRelease(void * const blockAddr, const size_t blockSize) noexcept
        {
            assert(blockSize>0);
            assert( Object::Factory::Exists() );
            static Object::Factory &factory = Object::Factory::Location();
            factory.release(blockAddr,blockSize);
        }
    }


    void * Object:: operator new(const size_t blockSize)
    {
        assert(blockSize>0);
        return factoryAcquire(blockSize);
    }

    void Object:: operator delete(void * const blockAddr, const size_t blockSize) noexcept
    {
        assert( Good(blockAddr,blockSize) );
        if(blockSize>0)
            factoryRelease(blockAddr,blockSize);
    }


    void * Object:: operator new[](const size_t blockSize)
    {
        assert(blockSize>0);
        return factoryAcquire(blockSize);
    }

    void Object:: operator delete[](void * const blockAddr, const size_t blockSize) noexcept
    {
        assert( Good(blockAddr,blockSize) );
        if(blockSize>0)
            factoryRelease(blockAddr,blockSize);
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
