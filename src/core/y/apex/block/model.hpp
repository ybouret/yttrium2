
//! \file

#ifndef Y_Apex_Model_Included
#define Y_Apex_Model_Included 1

#include "y/apex/block/blocks.hpp"
#include "y/apex/block/transmogrify.hpp"
#include "y/apex/block/ops.hpp"
#include "y/object.hpp"

namespace Yttrium
{
    class OutputStream;
    class InputStream;

    
    namespace Apex
    {

       

        //______________________________________________________________________
        //
        //
        //
        //! Model: Blocks + view and bits
        //
        //
        //______________________________________________________________________
        class Model : public Object, private Blocks
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const unsigned Ops = 6;            //!< alias
            typedef void         (Model:: *Change)(); //!< alias
            typedef size_t       (Model:: *Update)(); //!< alias
            static const ViewType SmallView[Ops];     //!< table of small type for ops
            static unsigned BytesPerUnit(const ViewType) noexcept; //!< \return 2^view

            

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param userBytes minimal bytes \param userView initial view
            explicit Model(const size_t   userBytes,
                           const ViewType userView);

            //! duplicate \param userModel source \param userView [new] view
            explicit Model(const Model &  userModel,
                           const ViewType userView);

            //! setup with natural
            explicit Model(const natural_t);

            //! setup with array of naturals
            explicit Model(const natural_t * const, const size_t );

            //! setup with anonymous data
            /**
             \param entry first bytes of data matching tview
             \param count number of data matching tview
             \param tview view type of data
             */
            explicit Model(const void * const entry,
                           const size_t       count,
                           const ViewType     tview);

            //explicit Model(Random::Bits &ran, const size_t numBits);


            //! cleanup
            virtual ~Model() noexcept;
            Y_OSTREAM_PROTO(Model); //!< display

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            Model & ldz(const ViewType) noexcept; //!< set to zero             \return *this
            Model & set(const ViewType) noexcept; //!< transmogriy to new view \return *this
            void    cpy(const Model & ) noexcept; //!< copy when capacity is enough
            void    update() noexcept;            //!< update view, set bits


            //! \return get block with matching view
            template <typename T>
            inline const Block<T> & get() const noexcept
            {
                assert( BlockAPI::VTable[ IntegerLog2For<T>::Value ] == view );
                return block<T>();
            }

            //! \return get block with matching view
            template <typename T>
            inline  Block<T> & get() noexcept
            {
                assert( BlockAPI::VTable[ IntegerLog2For<T>::Value ] == view );
                return block<T>();
            }

            //! \return transmogrified block
            template <typename T>
            inline  Block<T> & make() noexcept
            {
                set(  BlockAPI::VTable[ IntegerLog2For<T>::Value ] );
                return block<T>();
            }


            //__________________________________________________________________
            //
            //
            // Operations
            //
            //__________________________________________________________________
            size_t         save(OutputStream &); //!< effective serialization \return written bytes
            static Model * Load(InputStream &, const ViewType, const char * const); //!< reload with variable name \return read model


            static Model * Add(const OpsMode, const Model &, const Model &); //!< addition \return resulting model
            static Model * Add(const OpsMode, const Model &, const natural_t);     //!< addition \return resulting model

            static Model * Sub(const OpsMode, const Model &,   const Model &); //!< addition \return resulting model
            static Model * Sub(const OpsMode, const Model &,   const natural_t);     //!< addition \return resulting model
            static Model * Sub(const OpsMode, const natural_t, const Model &); //!< addition \return resulting model


            //! compare by adjusting to biggest view
            static SignType Compare(const Model &, const Model &);

            //! compare by formatting natural_t to model view
            static SignType Compare(const Model &, const natural_t) noexcept;

            

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const ViewType view;  //!< current view
            const size_t  &bytes; //!< current bytes
            const size_t  &space; //!< current capacity
            const size_t   bits;  //!< curretn bits

        private:
            Y_Disable_Copy_And_Assign(Model); //!< discarding
            static Change const ChangeTo[Metrics::Views][Metrics::Views]; //!< change table
            static Update const Updating[Metrics::Views];                 //!< update table

            //! generic transmogrify
            template <typename TARGET, typename SOURCE>
            inline void To() noexcept {
                assert( BlockAPI::VTable[ IntegerLog2For<SOURCE>::Value ] == view );
                Transmogrify::To( block<TARGET>(), block<SOURCE>() );
            }

            //! upgrade from current view \return bit count
            template <typename T>
            inline size_t Go() noexcept {
                static const size_t ViewIndex = IntegerLog2For<T>::Value;
                assert( BlockAPI::VTable[ ViewIndex ] == view );
                return block<T>().update( sync[ViewIndex] );
            }


        };

        //! helper to define tables
#define Y_Apex_Model_Table(PRE,POST) \
PRE <uint8_t,uint16_t>  POST,\
PRE <uint8_t,uint32_t>  POST,\
PRE <uint8_t,uint64_t>  POST,\
PRE <uint16_t,uint32_t> POST,\
PRE <uint16_t,uint64_t> POST,\
PRE <uint32_t,uint64_t> POST

    }

}

#endif

