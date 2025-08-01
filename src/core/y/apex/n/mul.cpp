
#include "y/apex/natural.hpp"
#include "y/apex/k/device.hpp"

namespace Yttrium
{
    namespace Apex
    {

        static const Natural::MulAPI * theAPI =  & Natural::LMulAPI;
        static MultiplicationAlgorithm theMul =    RegularMultiplication;

        MultiplicationAlgorithm Natural:: Get() noexcept { return theMul; }

        MultiplicationAlgorithm Natural:: Set(const MultiplicationAlgorithm algo) noexcept
        {
            Y_Giant_Lock();
            const MultiplicationAlgorithm old = theMul;

            switch(algo)
            {
                case RegularMultiplication:
                    theAPI = & LMulAPI;
                    break;

                case FourierMultiplication:
                    theAPI = & FMulAPI;
                    break;
            }

            theMul = algo;

            return old;
        }

        const char * Natural:: MultiplicationName() noexcept
        {
            switch(theMul)
            {
                    Y_Return_Named_Case(RegularMultiplication);
                    Y_Return_Named_Case(FourierMultiplication);
            }
            return Core::Unknown;
        }


        Device * Natural:: Mul(const Natural &lhs, const Natural &rhs)
        {
            assert(theAPI);
            return theAPI->proc1(lhs,rhs);
        }

        Device * Natural:: Mul(const Natural &lhs, const natural_t rhs)
        {
            assert(theAPI);
            return theAPI->proc2(lhs,rhs);
        }

        Device * Natural:: Mul(const natural_t lhs, const Natural &rhs)
        {
            assert(theAPI);
            return theAPI->proc3(lhs,rhs);
        }

        Natural Natural:: sqr() const
        {
            Y_Lock(**this);
            return Natural(Hook,theAPI->sproc(*this));
        }
    }

}

namespace Yttrium
{
    namespace Apex
    {
        Device * Natural:: LMul(const Natural &lhs, const Natural &rhs)
        {
            Y_Lock(*lhs);
            Y_Lock(*rhs);
            return Device::Mul(*lhs.device,*rhs.device,Ops);
        }

        Device * Natural:: LMul(const Natural &lhs, const natural_t rhs)
        {
            Y_Lock(*lhs);
            return Device::Mul(*lhs.device,rhs,Ops);
        }

        Device * Natural:: LMul(const natural_t lhs, const Natural &rhs)
        {
            Y_Lock(*rhs);
            return Device::Mul(*rhs.device,lhs,Ops);
        }


        Device * Natural:: LSqr(const Natural &n)
        {
            return Device::Sqr(*n.device,Ops);
        }

         

        const Natural::MulAPI Natural::LMulAPI  =
        {
            Natural::LMul,
            Natural::LMul,
            Natural::LMul,
            Natural::LSqr
        };
        
    }



}

namespace Yttrium
{
    namespace Apex
    {
        Device * Natural:: FMul(const Natural &lhs, const Natural &rhs)
        {
            Y_Lock(*lhs);
            Y_Lock(*rhs);
            return Device::MulDFT(*lhs.device,*rhs.device);
        }

        Device * Natural:: FMul(const Natural &lhs, const natural_t rhs)
        {
            Y_Lock(*lhs);
            return Device::MulDFT(*lhs.device,rhs);
        }

        Device * Natural:: FMul(const natural_t lhs, const Natural &rhs)
        {
            Y_Lock(*rhs);
            return Device::MulDFT(*rhs.device,lhs);
        }

        Device * Natural:: FSqr(const Natural &n)
        {
            return Device::SqrDFT(*n.device);
        }

        const Natural::MulAPI Natural::FMulAPI  =
        {
            Natural::FMul,
            Natural::FMul,
            Natural::FMul,
            Natural::FSqr
        };
    }

}


