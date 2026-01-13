
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

            void Huffman:: Node:: propagate() noexcept
            {
                static const CodeType one       = 1 ;
                const CodeType        childCode = code << 1;
                const unsigned        childBits = bits+1;
                if(left)
                {
                    left->code = childCode;
                    left->bits = childBits;
                    left->propagate();
                }

                if(right)
                {
                    right->code = childCode;
                    right->bits = childBits;
                    right->code |= one;
                    right->propagate();
                }
            }




            SignType  Huffman:: Node:: Comparator:: operator()(const Node::Pointer lhs, const Node::Pointer rhs) noexcept
            {
                assert(lhs);
                assert(rhs);
                return Sign::Of(rhs->freq,lhs->freq);
            }

            Huffman:: Huffman() noexcept:
            root(0),
            nodes(0),
            Q(),
            wksp()
            {
                Coerce(nodes) = static_cast<Node *>( Y_Memory_BZero(wksp) );
            }

            Huffman:: ~Huffman() noexcept
            {
            }

            void Huffman:: build(Alphabet &alpha)
            {
                root         = 0;
                {
                    size_t inode = 0;

                    // initialize queue, with at least NYT if no detected char
                    assert(alpha.encoding.size>=2);
                    Q.free();

                    //for(Character *ch=alpha.encoding.head;ch;ch=ch->next)
                    for(Character *ch=alpha.encoding.tail;ch;ch=ch->prev)
                    {
                        assert(inode<InnerNodes);
                        Node::Pointer const node = Memory::Stealth::CastZeroed<Node>(nodes + inode++);
                        node->leaf = ch;
                        node->freq = ch->freq;
                        assert(0==node->code);
                        assert(0==node->bits);
                        Q << node;
                    }

                    assert(Q->size>=2);



                    // build tree
                    while(Q->size>1)
                    {
                        assert(inode<InnerNodes);
                        Node * const        left  = Q.pop();
                        Node * const        right = Q.pop();
                        Node::Pointer const node  = Memory::Stealth::CastZeroed<Node>(nodes + inode++);
                        assert(left->freq<=right->freq);
                        left->parent  = node;
                        right->parent = node;
                        node->left    = left;
                        node->right   = right;
                        node->freq    = left->freq + right->freq;
                        Q << node;
                    }

                    std::cerr << "#nodes=" << inode << "/ " << InnerNodes << std::endl;
                    assert(1==Q->size);
                }
                (root = Q.pop())->propagate();

                {
                    const Node * node = nodes;
                    for(Character *ch=alpha.encoding.tail;ch;ch=ch->prev,++node)
                    {
                        assert(node->leaf==ch);
                        ch->bits = node->bits;
                        ch->code = node->code;
                    }

                }
            }


        }

    }

}

#include "y/graphviz/vizible.hpp"
#include "y/string/format.hpp"
#include "y/stream/output.hpp"
#include "y/format/binary.hpp"

namespace Yttrium
{
    namespace Information
    {
        namespace Pack
        {


            OutputStream & Huffman:: Node:: viz(OutputStream &fp) const
            {

                if(left)  left->viz(fp);
                if(right) right->viz(fp);

                nodeName(fp) << '[';
                String name = Formatted::Get("[%lu]",  (unsigned long) freq );
                if(leaf)
                {
                    name += "@";
                    const  uint16_t b = leaf->data;
                    if(b<256)
                    {
                        name += "'";
                        name += (char) leaf->data;
                        name += "'";
                    }
                    else
                    {
                        if(b==Alphabet::NYT) name += "NYT";
                        if(b==Alphabet::EOS) name += "EOS";
                    }
                }
                //name += Formatted::Get(" #%u",bits);
                if(bits)
                {
                    name += '<';
                    name += Binary(code,bits).c_str();
                    name += '>';
                }
                Label(fp,name);
                Endl(fp << ']');

                if(left)  { Endl(to(left,fp)  << "[label=\"0\"]"); }
                if(right) { Endl(to(right,fp) << "[label=\"1\"]"); }

                return fp;
            }
        }

    }

}
