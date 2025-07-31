
#include "y/coven/tribes.hpp"


namespace Yttrium
{

    namespace Coven
    {


        Tribes:: ~Tribes() noexcept
        {

        }

        std::ostream & operator<<(std::ostream &os, const Tribes &tribes)
        {
            os << "<Tribes size=" << tribes.size << ">" << std::endl;
            for(const Tribe *tr=tribes.head;tr;tr=tr->next)
            {
                os << *tr << std::endl;
            }
            return os << "</Tribes>" << std::endl;
        }


        bool Tribes:: colinearity() const noexcept
        {
            assert(tail!=0);
            assert(1==tail->family->size());
            assert(0!=tail->family->lastVec);
            const QVector &lhs = * tail->family->lastVec;
            for(const Tribe *prev=tail->prev;prev;prev=prev->prev)
            {
                assert(1==prev->family->size());
                assert(0!=prev->family->lastVec);
                const QVector &rhs = * prev->family->lastVec;
                if(lhs==rhs)
                {
                    std::cerr << "colinear rows" << std::endl;
                    return true;
                }
            }
            return false;
        }

        void Tribes:: finish(const IList &toRemove) noexcept
        {
            for(Tribe *tr=head;tr;tr=tr->next)
            {
                for(const INode *node=toRemove->head;node;node=node->next)
                {
                    tr->remove(**node);
                }
            }
        }

#if 0
        static inline
        void promoteReadyOf(Tribe * const tribe, const IList &peerBasis)
        {
            //std::cerr << "Promote " << *tribe << " with " << peerBasis << std::endl;

            {
                IList ready(peerBasis.pool);
                while(tribe->ready->size)
                {
                    INode * const node = tribe->ready->popHead();
                    if(peerBasis.has(**node))
                    {
                        tribe->basis.sorted(node);
                    }
                    else
                        ready->pushTail(node);
                }

                (*tribe->ready).swapListFor(*ready);
            }


        }
#endif

        void Tribes:: shrink(XMLog &xml)
        {
            assert(isOrderedBy(Tribe::Compare,Sign::LooselyIncreasing));

            if(size<=0)
            {
                Y_XMLog(xml, "(*) [no produced tribe]");
                return;
            }

            Y_XML_Section_Attr(xml, "shrink", Y_XML_Attr(size));
            //------------------------------------------------------------------
            //
            // remove stalled and replica in one pass
            //
            //------------------------------------------------------------------
            {
                Tribe::List list;
                const size_t numAtStart = size;
                size_t       numStalled = 0;
                size_t       numReplica = 0;
                while(size>0)
                {
                    Tribe * const source = head;
                    if(source->stalled())
                    {
                        //------------------------------------------------------
                        // won't produce new vector
                        //------------------------------------------------------
                        ++numStalled;
                        goto DROP;
                    }

                    for(Tribe *target=list.tail;target;target=target->prev)
                    {
                        if(target->basis == source->basis)
                        {
                            if(target->ready == source->ready)
                            {
                                assert( __Zero__ == Tribe::Compare(source,target) );
                                ++numReplica;
                                goto DROP; // replica, same future
                            }

                            //            same basis, different ready:
                            goto KEEP; //   for next generation
                        }

                        assert(target->basis != source->basis);
                    }

                KEEP:
                    list.pushTail( popHead() );
                    continue;

                DROP:
                    delete popHead();
                }
                swapListFor(list);
                if(numStalled) Y_XMLog(xml, "#stalled   = " << numStalled);
                if(numReplica) Y_XMLog(xml, "#replica   = " << numReplica);
                if(numReplica||numStalled) {
                    /**/       Y_XMLog(xml, "#remaining = " << size << " / " << numAtStart);
                    assert(numStalled+numReplica+size == numAtStart);
                }
            }
            assert(isOrderedBy(Tribe::Compare,Sign::LooselyIncreasing));

            if(size<=0) return;

            {
                Tribe::List list; // collect [un]processed
                while(size>0)
                {
                    //----------------------------------------------------------
                    //
                    // initialize same to current head
                    //
                    //----------------------------------------------------------
                    Tribe::List     same;       // shall be processed
                    same.pushTail( popHead() ); // init
                    {
                        Tribe::List diff; // shall return to *this
                        //------------------------------------------------------
                        //
                        // dispatch remaining
                        //
                        //------------------------------------------------------
                        {
                            const QFamily &lhs = *same.head->family;
                            while(size>0)
                            {
                                Tribe * const tribe = popHead();
                                if( lhs == *tribe->family )
                                {
                                    same.pushTail(tribe);
                                }
                                else
                                {
                                    diff.pushTail(tribe);
                                }
                            }
                        }

                        //------------------------------------------------------
                        //
                        // return diff to *this for next loop
                        //
                        //------------------------------------------------------
                        assert(0==size);
                        swapListFor(diff);
                    }

                    //----------------------------------------------------------
                    //
                    // process same
                    //
                    //----------------------------------------------------------
                    if(same.size>1)
                    {
                        std::cerr << "\t\t###same families = " << same.size << std::endl;
                    }

                    list.mergeTail(same);
                }

                list.sort(Tribe::Compare);
                swapListFor(list);
            }

        }


    }

}
