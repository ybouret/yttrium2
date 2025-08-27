//! \file


#ifndef Y_Chemical_Indexed_Included
#define Y_Chemical_Indexed_Included 1


#include "y/chemical/type/entity.hpp"


namespace Yttrium
{
    namespace Chemical
    {

        //______________________________________________________________________
        //
        //
        //! description level
        //
        //______________________________________________________________________
        enum Level
        {
            TopLevel, //!< in global space
            SubLevel, //!< in cluster
            AuxLevel  //!< somewhere else
        };

        //______________________________________________________________________
        //
        //
        //
        //! Indexed Entity
        //
        //
        //______________________________________________________________________
        class Indexed : public Entity
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const unsigned MaxLevel = AuxLevel+1; //!< alias


            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup with empty name \param top TopLevel index, top>0
            explicit Indexed(const size_t top);

            //! setup \param id name \param top TopLevel index, top>0
            template <typename ID> inline
            explicit Indexed(const ID &id, const size_t top) :
            Entity(id),
            indx()
            {
                setup(top);
            }

            virtual ~Indexed() noexcept; //!< cleanup

            //! \param seq sequence-like \param level level \return seq[ indx[level] ]
            template <typename SEQ> inline
            typename SEQ::Type & operator()(SEQ &seq, const Level level) const noexcept
            {
                return seq[ indx[level] ];
            }

            //! \param seq sequence-like \param level level \return seq[ indx[level] ]
            template <typename SEQ> inline
            typename SEQ::ConstType & operator()(const SEQ &seq, const Level level) const noexcept
            {
                return seq[ indx[level] ];
            }


            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const size_t indx[MaxLevel]; //!< array of indices

        private:
            Y_Disable_Copy_And_Assign(Indexed); //!< discarding
            void setup(const size_t) noexcept;  //!< initializing
        };

    }

}

#endif

