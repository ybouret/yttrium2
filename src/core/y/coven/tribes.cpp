
#include "y/coven/tribes.hpp"


namespace Yttrium
{

    namespace Coven
    {
        apn Tribes:: MaxFor(const size_t n)
        {
            apn sum = 0;
            for(size_t k=1;k<=n;++k)
            {
                sum += apn::Enum(n,k);
            }
            return sum;
        }

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

        static inline
        void promoteReadyOf(Tribe * const tribe, const IList &peerBasis)
        {

            //std::cerr << "promote " << tribe->basis << ":" << tribe->ready << " with " << peerBasis << std::endl;
            assert(IList::AreDetached(tribe->basis,tribe->ready));

            {
                IList ready(peerBasis.pool);
                while(tribe->ready->size)
                {
                    INode * const node = tribe->ready->popHead();
                    const size_t  indx = **node;
                    if(peerBasis.found(indx))
                    {
                        // updated ready to basis
                        assert( !tribe->basis.found(indx) );
                        tribe->basis.sorted(node);
                    }
                    else
                    {
                        // keep ready
                        ready->pushTail(node);
                    }
                }
                tribe->ready->swapListFor( *ready );
            }

            assert(IList::AreDetached(tribe->basis,tribe->ready));
        }

        static inline
        Tribe * findTarget(Tribe::List &list, const Tribe * const source)
        {
            for(Tribe * target=list.head;target;target=target->next)
            {
                if(target->basis==source->basis) continue;
                if(target->basis->size!=source->basis->size) continue;
                if(*target->family == *source->family) return target;
            }
            return 0;
        }

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
            //
            // remove stalled and replica in one pass
            //
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

            if(xml.verbose) xml() << "compressing : " << '[';
            while( varied(xml) )
                ;
            if(xml.verbose) xml.os << ']' << std::endl;

            Y_XMLog(xml, "#remaining = " << size);

        }

        bool Tribes:: varied(XMLog &xml)
        {
            Tribe::List list; // storage
            //Y_XMLog(xml,"try to compress size=" << size);
            while(size>0)
            {
                Tribe * source = head;
                Tribe * target = findTarget(list,source);

                if( target )
                {
                    //----------------------------------------------------------
                    //
                    // promoting ready indices from peer basis
                    //
                    //----------------------------------------------------------
                    //Y_XMLog(xml, "(*) ---- same families ----");
                    //Y_XMLog(xml, "(-) source: " << source->basis << ":" << source->ready);
                    //Y_XMLog(xml, "(-) target: " << target->basis << ":" << target->ready);


                    {
                        const IList sourceBasis = source->basis;
                        const IList targetBasis = target->basis;
                        //Y_XMLog(xml, "(#) promoting");
                        promoteReadyOf(source,targetBasis);
                        promoteReadyOf(target,sourceBasis);
                    }
                    //Y_XMLog(xml, "(+) source: " << source->basis << ":" << source->ready);
                    //Y_XMLog(xml, "(+) target: " << target->basis << ":" << target->ready);

                    //----------------------------------------------------------
                    //
                    // check result
                    //
                    //----------------------------------------------------------
                    bool deleted = false;
                    if(source->ready->size<=0)
                    {
                        //Y_XMLog(xml,"(-) removing source");
                        if(xml.verbose) xml.os << '-';
                        assert(head == source);
                        delete popHead();
                        source = 0;
                        deleted = true;
                    }

                    if(target->ready->size<=0)
                    {
                        //Y_XMLog(xml,"(-) removing target");
                        if(xml.verbose) xml.os << '-';
                        assert(list.owns(target));
                        delete list.pop( target );
                        target = 0;
                        deleted = true;
                    }

                    if( source&&target && Tribe::AreIdentical(source,target) )
                    {
                        //Y_XMLog(xml,"(-) removing replica");
                        if(xml.verbose) xml.os << '#';
                        delete popHead();
                        source = 0;
                        deleted = true;
                     }

                    if(!deleted)
                    {
                        if(xml.verbose) xml.os << '+';
                        ///Y_XMLog(xml, "(+) keeping modified tribes");
                    }


                    //----------------------------------------------------------
                    //
                    // build new tribes
                    //
                    //----------------------------------------------------------
                    list.mergeTail(*this).sort(Tribe::Compare);
                    swapListFor(list);
                    return true; // something has changed
                }

                // move to list
                list.pushTail(popHead());
            }

            // at this point, nothing was done
            assert(isOrderedBy(Tribe::Compare,Sign::LooselyIncreasing));
            swapListFor(list);
            return false;
        }


    }

}
