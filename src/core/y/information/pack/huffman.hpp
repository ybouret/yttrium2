
//! \file

#ifndef Y_Information_Pack_Huffman_Included
#define Y_Information_Pack_Huffman_Included 1

#include "y/information/pack/alphabet.hpp"
#include "y/container/ordered/priority-queue.hpp"
#include "y/graphviz/vizible.hpp"

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

                class Node : public Vizible
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



                    OutputStream &viz(OutputStream &) const;
                    void          propagate()         noexcept;


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
                    virtual ~Node() noexcept;
                };

                static const DataType MaxChars   = Alphabet::InnerChars-1;
                static const DataType InnerNodes = 2*MaxChars-1;
                static const size_t   SizeOfNode = sizeof(Node);
                static const size_t   InnerBytes = SizeOfNode * InnerNodes;
                static const size_t   InnerWords = Alignment::WordsGEQ<InnerBytes>::Count;



                explicit Huffman();
                virtual ~Huffman() noexcept;

                void build(Alphabet &alpha);

                Node::PQ     pq;
                Node *       root;

            private:
                Y_Disable_Copy_And_Assign(Huffman);
                Node *   const nodes;
                void *         wksp[ InnerWords ];
            };

        }

    }

}

#endif // !Y_Information_Pack_Huffman_Included

