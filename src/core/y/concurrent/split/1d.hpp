
//! \file


#ifndef Y_Concurrent_Split1D_Included
#define Y_Concurrent_Split1D_Included 1

#include "y/concurrent/member.hpp"
#include "y/object/counted.hpp"
#include "y/pointer/arc.hpp"
#include "y/container/cxx/array.hpp"
#include "y/type/ingress.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        namespace Split
        {

            //__________________________________________________________________
            //
            //
            //
            //! offset+length
            //
            //
            //__________________________________________________________________
            class Zone
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                Zone()            noexcept; //!< setup to zeor
                Zone(const Zone&) noexcept; //!< duplicate
                virtual ~Zone()   noexcept; //!< cleanup

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const size_t offset; //!< cumulative offset
                const size_t length; //!< dedicated  length from offset
            private:
                Y_Disable_Assign(Zone); //!< discarding
            };

            //__________________________________________________________________
            //
            //
            //
            //! offset+length+utmost
            //
            //
            //__________________________________________________________________
            template <typename T>
            class Segment : public CountedObject
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef ArcPtr<Segment>   Pointer; //!< alias
                typedef CxxArray<Pointer> Array;   //!< alias

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                explicit Segment() noexcept : offset(0), length(0), utmost(0) {} //!< setup empty
                virtual ~Segment() noexcept {}                                   //!< cleanup

                //! display
                inline friend
                std::ostream & operator<<(std::ostream &os, const Segment &self)
                {
                    return os << self.offset << '+' << self.length;
                }

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const T      offset; //!< offset
                const size_t length; //!< length
                const T      utmost; //!< utmost

            private:
                Y_Disable_Copy_And_Assign(Segment); //!< discarding
            };

            //__________________________________________________________________
            //
            //
            //
            //! empty segment
            //
            //
            //__________________________________________________________________
            template <typename T>
            class EmptySegment : public Segment<T>
            {
            public:
                inline explicit EmptySegment() noexcept : Segment<T>() {} //!< setup
                inline virtual ~EmptySegment() noexcept {}                //!< cleanup
            private:
                Y_Disable_Copy_And_Assign(EmptySegment); //!< discarding
            };

            //__________________________________________________________________
            //
            //
            //
            //! heavy segment
            //
            //
            //__________________________________________________________________
            template <typename T>
            class HeavySegment : public Segment<T>
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup \param ini initial offset \param num positive length
                inline explicit HeavySegment(const T ini, const size_t num) noexcept :
                Segment<T>()
                {
                    assert(num>0);
                    Coerce(this->offset) = ini;
                    Coerce(this->length) = num;
                    Coerce(this->utmost) = ini + (T) (num-1);
                }

                //! cleanup
                inline virtual ~HeavySegment() noexcept {}
            private:
                Y_Disable_Copy_And_Assign(HeavySegment); //!< discarding
            };

            //__________________________________________________________________
            //
            //
            //
            //! Base class for segments
            //
            //
            //__________________________________________________________________
            template <typename T>
            class SegmentsComm
            {
            public:
                inline explicit SegmentsComm() : empty( new EmptySegment<T>() ) {} //!< setup
                inline virtual ~SegmentsComm() noexcept {}                         //!< cleanup

                const typename Segment<T>::Pointer empty; //!< const empty

            private:
                Y_Disable_Copy_And_Assign(SegmentsComm); //!< discarding

            };

            //__________________________________________________________________
            //
            //
            //
            //! pre-computed segments
            //
            //
            //__________________________________________________________________
            template <typename T>
            class Segments :
            public SegmentsComm<T>,
            public Ingress< const Readable<typename Segment<T>::Pointer> >
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef Segment<T>                SegType;    //!< alias
                typedef typename SegType::Pointer SegPointer; //!< alias
                typedef typename SegType::Array   SegArray;   //!< alias
                using SegmentsComm<T>::empty;

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! setup \param numProcessors parallel size
                inline explicit Segments(const size_t numProcessors) :
                arr(numProcessors,empty)
                {
                    assert(numProcessors>0);
                }

                //! cleanup
                inline virtual ~Segments() noexcept {}

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! set all to empty
                virtual void reset() noexcept
                {
                    for(size_t i=arr.size();i>0;--i) arr[i] = this->empty;
                }


            private:
                Y_Disable_Copy_And_Assign(Segments); //!< discarding
                inline virtual const Readable<SegPointer> & locus() const noexcept { return arr; }

                SegArray arr; //!< the arrays
            };



            //__________________________________________________________________
            //
            //
            //
            //! Stable burden division
            //
            //
            //__________________________________________________________________
            class In1D : public Zone
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                In1D(const size_t) noexcept; //!< setup with burden
                virtual ~In1D()    noexcept; //!< cleanup

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                //! initialize
                /**
                 \param numProcessors target count of cpu
                 \param initialOffset to propagate
                 */
                void boot(const size_t numProcessors,
                          const size_t initialOffset) noexcept;

                //! \return true if a new zone was computer
                bool next() noexcept;

                //! \return matching zone with initial offset
                Zone operator()(const Member &, const size_t) noexcept;

                //! compute \param segments parallel segments \param ini initial offset \return segments
                template <typename T> inline
                Segments<T> & operator()(Segments<T> &segments,
                                         const T      ini)
                {
                    const size_t np = segments->size();
                    boot(np,0);
                    for(size_t i=1;i<=np;++i)
                    {
                        assert(divide>0);
                        typename Segment<T>::Pointer p = segments.empty;
                        (void) next();
                        if(length>0)
                        {
                            const  typename Segment<T>::Pointer tmp = new HeavySegment<T>( ini + (T)offset, length );
                            p = tmp;
                        }
                        Coerce( (*segments)[i] ) = p;
                    }
                    return segments;
                }

            private:
                size_t       divide; //!< internal divide
                size_t       remain; //!< internal remain
            public:
                const size_t burden; //!< original burden
            private:
                Y_Disable_Copy_And_Assign(In1D); //!< discarding
            };

        }

    }
}

#endif

