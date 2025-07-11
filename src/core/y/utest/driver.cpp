#include "y/utest/driver.hpp"
#include "y/check/usual.hpp"
#include <cstdlib>
#include <cstring>
#include <iostream>

namespace Yttrium
{
    namespace UTest
    {
        int Procedure::Compare(const void *const lhs, const void *const rhs) noexcept
        {
            return strcmp( static_cast<const Procedure *>(lhs)->name, static_cast<const Procedure *>(rhs)->name );
        }

        Driver:: ~Driver() noexcept
        {
            clear();
        }

        Driver:: Driver(Procedure * const p,
                        const size_t      n) noexcept :
        proc(p),
        capacity(n),
        size(0),
        maxNameLength(0)
        {
            assert( Good(proc,capacity) );
            clear();
        }

        void Driver:: clear() noexcept
        {
            memset(proc,0,sizeof(Procedure)*capacity);
            size=0;
            maxNameLength=0;
        }

        void Driver:: display() const
        {
            for(size_t i=0;i<size;++i)
                std::cerr << '\t' << '[' << proc[i].name << ']' << std::endl;
        }

        void Driver:: operator()(CFunction          call,
                                 const char * const name)
        {
            assert(0!=call);
            assert(0!=name);
            if(size>=capacity) throw Exception("UTest::Driver<%lu> is full!", static_cast<unsigned long>(size) );
            for(size_t i=0;i<size;++i)
            {
                if( 0 == strcmp(proc[i].name,name) ) throw Exception("multiple UTest '%s'",name);
            }
            Procedure &target = proc[size++];
            target.call = call;
            target.name = name;
            InSituMax(maxNameLength, strlen(name) );
            qsort(proc,size, sizeof(Procedure), Procedure::Compare);
        }

        int Driver:: operator()(int argc, char **argv) const
        {
            assert(0!=argv);
            assert(argc>=1);
            const char * const mainName = argv[0];
            if(argc>1)
            {
                const char * const testName = argv[1];
                for(size_t i=0;i<size;++i)
                {
                    const Procedure &p = proc[i];
                    if( 0 == strcmp(p.name,testName))
                    {
                        return p.call(--argc,++argv);
                    }
                }
                std::cerr << "[" << testName << "] not found. Did you mean :" << std::endl;
                for(size_t i=0;i<size;++i)
                {
                    const char * const name = proc[i].name;
                    const char * big = name;
                    const char * little = testName;
                    if( strlen(big) < strlen(little) )
                    {
                        Swap(big,little);
                    }
                    if( strstr(big,little) )
                    {
                        std::cerr << "\t" << name << std::endl;
                    }

                }
                return 1;
            }
            else
            {
                std::cerr << "<" << mainName << " [" << size << "/" << capacity << "]>" << std::endl;
                display();
                std::cerr << "<" << mainName << " [" << size << "]>" << std::endl;
                return 0;
            }
        }
    }

}
