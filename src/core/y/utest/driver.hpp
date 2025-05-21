//! \file

#ifndef Y_UTest_Driver_Included
#define Y_UTest_Driver_Included 1

#include "y/core/setup.hpp"
#include "y/exception.hpp"
#include "y/core/utils.hpp"
#include "y/utest/catch.hpp"

namespace Yttrium
{

    namespace UTest
    {

        typedef int (*CFunction)(int,char **); //!< alias

        //______________________________________________________________________
        //
        //! function and its name
        //______________________________________________________________________
        struct Procedure
        {
            CFunction   call; //!< test function
            const char *name; //!< test name

            //! comparison by name for qsort
            /**
             \param lhs address of first procedure
             \param rhs address of second procedure
             \return name comparison
             */
            static  int Compare(const void * const lhs, const void * const rhs) noexcept;
        };

        //______________________________________________________________________
        //
        //
        //
        //! storage and call of test functions
        //
        //
        //______________________________________________________________________
        class Driver
        {
        public:

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            virtual ~Driver() noexcept;
            void     display()   const; //!< display content

            //! append a new test
            /**
             will throw upon too many or multiple tests
             \param call test function
             \param name test name
             */
            void operator()(CFunction          call,
                            const char * const name);


            //! call argv[1] or display()
            /**
             \param  argc from main
             \param  argv from main
             \return result of test(--argc,++argv)
             */
            int operator()(int argc, char **argv) const;

        protected:
            //! initialize
            /**
             \param p persistent procedures
             \param n available procedures
             */
            explicit Driver(Procedure * const p,
                            const size_t      n) noexcept;

            Procedure * const proc;          //!< persistent procedures
            const size_t      capacity;      //!< available procedures
            size_t            size;          //!< number of active procedures
            size_t            maxNameLength; //!< max name length of procedures

        private:
            Y_Disable_Copy_And_Assign(Driver); //!< discarding
            void clear() noexcept;             //!< hard-reset
        };

        //______________________________________________________________________
        //
        //
        //
        //! Data for N testds
        //
        //
        //______________________________________________________________________
        template <size_t N>
        class DriverData
        {
        public:

            inline virtual ~DriverData() noexcept {} //!< destructor

        protected:
            //! constructor
            inline explicit DriverData() noexcept : proc_()
            {
            }

            Procedure proc_[N]; //!< local memory for procedures
        private:
            Y_Disable_Copy_And_Assign(DriverData); //!< discarding

        };

        //______________________________________________________________________
        //
        //
        //
        //! Driver with N tests
        //
        //
        //______________________________________________________________________
        template <size_t N>
        class DriverWith : public DriverData<N>, public Driver
        {
        public:
            //! constructor
            inline  explicit DriverWith() noexcept :
            DriverData<N>(),
            Driver(proc_,N)
            {
            }

            //! destructor
            inline virtual ~DriverWith() noexcept {}

        private:
            Y_Disable_Copy_And_Assign(DriverWith); //!< discarding
        };

    }

    //! prepare driver
#define Y_UTEST_DECL(N) \
/**/  using namespace Yttrium;\
/**/  int main(int argc, char **argv) \
/**/  {\
/**/    UTest::DriverWith<N> driver;\
/**/    try {\

    //! run driver
#define Y_UTEST_EXEC() \
/**/      return driver(argc,argv);\
/**/    }\
/**/    Y_UTEST_CATCH();\
/**/  }

    //! declare test
#define Y_UTEST(NAME) do { \
/**/ extern int (Y_UTest_##NAME)(int,char **);\
/**/ driver(Y_UTest_##NAME,#NAME);\
/**/ } while(false)


}


#endif
