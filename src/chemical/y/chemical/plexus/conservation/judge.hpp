
//! \file


#ifndef Y_Chemical_Conservation_Judge_Included
#define Y_Chemical_Conservation_Judge_Included 1


#include "y/chemical/plexus/conservation/act.hpp"
#include "y/chemical/plexus/conservation/broken.hpp"


namespace Yttrium
{
    namespace Chemical
    {
        namespace Conservation
        {


            class Judge : public Object
            {
            public:
                explicit Judge(const Act &);
                virtual ~Judge() noexcept;

                void trial(XMLog &xml, XWritable &Ctop);

            private:
                Y_Disable_Copy_And_Assign(Judge);

                const Act &act;
                BList      blist;
                XAdd       xadd;
                const xreal_t zero;

            };

        }


    }

}

#endif

