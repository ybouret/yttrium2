//! \file

#ifndef Y_UTest_Driver_Included
#define Y_UTest_Driver_Included 1

#include "y/core/setup.hpp"
#include "y/exception.hpp"
#include "y/core/utils.hpp"
#include <iostream>
#include <cstring>
#include <cassert>
#include <cstdlib>

namespace Yttrium
{

    namespace UTest
    {

        typedef int (*CFunction)(int,char **);
        struct Procedure
        {
            CFunction   call;
            const char *name;
            static  int Compare(const void * const lhs, const void * const rhs) noexcept;
        };

        template <size_t N>
        class Driver
        {
        public:
            inline  Driver() noexcept : size(0), maxNameLength(0), proc() { clear(); }
            inline ~Driver() noexcept { clear(); }

            inline void operator()(CFunction          call,
                                   const char * const name)
            {
                assert(0!=call);
                assert(0!=name);
                if(size>=N) throw Exception("UTest::Driver<%lu> is full!", static_cast<unsigned long>(size) );
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

            inline void display() const
            {
                for(size_t i=0;i<size;++i)
                {
                    std::cerr << '\t' << '[' << proc[i].name << ']' << std::endl;
                }
            }

            inline int operator()(int argc, char **argv) const
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
                    std::cerr << "<" << mainName << " [" << size << "/" << N << "]>" << std::endl;
                    display();
                    std::cerr << "<" << mainName << "/>" << std::endl;
                    return 0;
                }
            }





        private:
            Y_Disable_Copy_And_Assign(Driver);
            size_t    size;
            size_t    maxNameLength;
            Procedure proc[N];

            inline void clear() noexcept
            {
                memset(proc,0,sizeof(proc));
                size          = 0;
                maxNameLength = 0;
            }
        };

    }

#define Y_UTEST_DECL(N) \
/**/  using namespace Yttrium;\
/**/  int main(int argc, char **argv) \
/**/  {\
/**/    UTest::Driver<N> driver;\
/**/    try {\

#define Y_UTEST_EXEC() \
/**/      return driver(argc,argv);\
/**/    }\
/**/    catch(...)\
/**/    { std::cerr << Core::Unknown << ' ' << Exception::CallSign << std::endl; return 3; }\
/**/  }

#define Y_UTEST(NAME) do { \
/**/ extern int (Y_UTest_##NAME)(int,char **);\
/**/ driver(Y_UTest_##NAME,#NAME);\
/**/ } while(false)


}


#endif
