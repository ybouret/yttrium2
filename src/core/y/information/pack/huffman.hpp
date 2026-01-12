
//! \file

#ifndef Y_Information_Pack_Huffman_Included
#define Y_Information_Pack_Huffman_Included 1

#include "y/information/pack/alphabet.hpp"
#include "y/container/ordered/priority-queue.hpp"

namespace Yttrium
{

    namespace Information
    {
        namespace Pack
        {

            class Huffman
            {
            public:
                typedef Alphabet::CodeType  CodeType;
                typedef Alphabet::DataType  DataType;
                typedef Alphabet::FreqType  FreqType;

                static const DataType MaxChars = Alphabet::EOS;
                static const DataType MaxNodes = 2*MaxChars;


                class Node
                {
                public:
                    typedef Node *Pointer;

                    class Comparator
                    {
                    public:
                        Comparator()  noexcept;
                        ~Comparator() noexcept;

                        SignType operator()(const Node::Pointer, const Node::Pointer) noexcept;

                    private:
                        Y_Disable_Copy_And_Assign(Comparator);
                    };

                    typedef PriorityQueue<Pointer,Comparator> PQ;

                    Node *      parent;
                    Node *      left;
                    Node *      right;
                    FreqType    freq;
                    CodeType    code;
                    unsigned    bits;
                    Character * leaf;

                    

                private:
                    Y_Disable_Copy_And_Assign(Node);
                    Node() noexcept;
                    ~Node() noexcept;
                };





                Huffman() :
                pq(WithAtLeast,MaxNodes),
                root(0),
                inode(0),
                count(MaxNodes),
                bytes(0),
                nodes( Object::AllocatorInstance().acquireAs<Node>(count,bytes) )
                {
                }

                virtual ~Huffman() noexcept;

                void build(Alphabet &alpha);


                const Node::PQ & queue() const noexcept { return pq; }

            private:
                Y_Disable_Copy_And_Assign(Huffman);
                Node::PQ pq;
                Node *   root;
                size_t   inode;
                size_t   count;
                size_t   bytes;
                Node *   nodes;
            };

        }

    }

}

#endif // !Y_Information_Pack_Huffman_Included

