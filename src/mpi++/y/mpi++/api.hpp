//! \file

#ifndef Y_MPI_Included
#define Y_MPI_Included 1

#include "y/singleton.hpp"
#include "y/concurrent/life-time.hpp"
#include "y/exception.hpp"
#include <mpi.h>

namespace Yttrium
{

    class MPI : public Singleton<MPI,ClassLockPolicy>
    {
    public:
        static const char * const CallSign;
        static const Longevity    LifeTime = LifeTimeOf:: MPI;

        

        class Exception : public Yttrium:: Exception
        {
        public:
            Exception(const int err, const char * fmt,...) noexcept Y_Printf_Check(3,4);
            Exception(const Exception &) noexcept;
            virtual ~Exception()         noexcept;
            virtual const char * what() const noexcept;

        private:
            Y_Disable_Assign(Exception);
            char info[Length];
        };


        static MPI & Init(int *argc, char ***argv, const int required);

        virtual void display(std::ostream &, size_t) const;


    public:
        const int threadLevel;
        
    private:
        Y_Disable_Assign(MPI);
        friend Singleton<MPI,ClassLockPolicy>;
        explicit MPI();
        virtual ~MPI() noexcept;
    };
}

#endif

