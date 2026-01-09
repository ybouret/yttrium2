
#include "y/information/pack/huffman.hpp"
#include "y/memory/stealth.hpp"

namespace Yttrium
{

    namespace Information
    {
        namespace Pack
        {

            Huffman:: Node:: Comparator::  Comparator() noexcept {}
            Huffman:: Node:: Comparator:: ~Comparator() noexcept {}


            SignType  Huffman:: Node:: Comparator:: operator()(const Node::Pointer lhs, const Node::Pointer rhs) noexcept
            {
                assert(lhs);
                assert(rhs);
                return Sign::Of(lhs->freq,rhs->freq);
            }

            Huffman:: ~Huffman() noexcept
            {
                Object::AllocatorLocation().releaseAs(nodes,count,bytes);
            }

            void Huffman:: build(Alphabet &alpha)
            {
                root  = 0;
                inode = 0;

                // initialize queue
                for(Character *ch=alpha.encoding.head;ch;ch=ch->next)
                {
                    Node::Pointer const node = Memory::Stealth::CastZeroed<Node>(nodes + inode++);
                    node->leaf = ch;
                    node->freq = ch->freq;
                    assert(0==node->code);
                    assert(0==node->bits);
                    pq.push(node);
                }

                assert(pq.size()>=1);
                


            }


        }

    }

}
