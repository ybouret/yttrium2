
//! \file

#ifndef Y_Apex_Model_Included
#define Y_Apex_Model_Included 1

#include "y/apex/block/blocks.hpp"
#include "y/apex/block/transmogrify.hpp"
#include "y/object.hpp"

namespace Yttrium
{
    namespace Apex
    {
        class Model : public Object, private Blocks
        {
        public:
            typedef void   (Model:: *Change)();
            typedef size_t (Model:: *Update)();

            explicit Model(const size_t   userBytes,
                           const ViewType userView);

            explicit Model(const Model &  userModel,
                           const ViewType userView);

            explicit Model(const uint64_t n);
            explicit Model(const uint64_t * const, const size_t );

            virtual ~Model() noexcept;

            Y_OSTREAM_PROTO(Model);

            void set(const ViewType vtgt) noexcept;

            size_t update() noexcept; //!< update view and return bits


            template <typename T>
            inline const Block<T> & get() const noexcept
            {
                assert( BlockAPI::VTable[ IntegerLog2For<T>::Value ] == view );
                return block<T>();
            }


            template <typename T>
            inline  Block<T> & get() noexcept
            {
                assert( BlockAPI::VTable[ IntegerLog2For<T>::Value ] == view );
                return block<T>();
            }

            template <typename T>
            inline  Block<T> & make() noexcept
            {
                set(  BlockAPI::VTable[ IntegerLog2For<T>::Value ] );
                return block<T>();
            }


            const ViewType view;
            const size_t  &bytes;
            const size_t   bits;

        private:
            Y_Disable_Copy_And_Assign(Model);
            static Change const ChangeTo[Metrics::Views][Metrics::Views];
            static Update const Updating[Metrics::Views];

            template <typename TARGET, typename SOURCE>
            inline void To() noexcept {
                assert( BlockAPI::VTable[ IntegerLog2For<SOURCE>::Value ] == view );
                Transmogrify::To( block<TARGET>(), block<SOURCE>() );
            }

            template <typename T>
            inline size_t Go() noexcept {
                static const size_t ViewIndex = IntegerLog2For<T>::Value;
                assert( BlockAPI::VTable[ ViewIndex ] == view );
                return block<T>().update( sync[ViewIndex] );
            }


        };

    }

}

#endif

