
//! \file

#ifndef Y_Information_Pack_Huffman_Included
#define Y_Information_Pack_Huffman_Included 1

#include "y/information/pack/alphabet.hpp"
#include "y/container/ordered/priority-queue.hpp"
#include "y/container/ordered/static-priority-queue.hpp"
#include "y/graphviz/vizible.hpp"

namespace Yttrium
{

    namespace Information
    {
        namespace Pack
        {

            //__________________________________________________________________
            //
            //
            //
            //! Huffman Tree building
            //
            //
            //__________________________________________________________________
            class Huffman
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef Alphabet::CodeType  CodeType; //!< alias
                typedef Alphabet::DataType  DataType; //!< alias
                typedef Alphabet::FreqType  FreqType; //!< alias
                static const DataType       MaxChars = Alphabet::InnerChars-1; //!< alias

                //______________________________________________________________
                //
                //
                //! Tree Node
                //
                //______________________________________________________________
                class Node : public Vizible
                {
                public:
                    //__________________________________________________________
                    //
                    // Definitions
                    //__________________________________________________________
                    typedef Node *Pointer; //!< alias

                    ///! comparator
                    class Comparator
                    {
                    public:
                        Comparator()  noexcept; //!< setup
                        ~Comparator() noexcept; //!< cleanup

                        //! \return decreasing frequency
                        SignType operator()(const Node::Pointer, const Node::Pointer) noexcept;

                    private:
                        Y_Disable_Copy_And_Assign(Comparator); //!< discarding
                    };

                    //! inner priority queue
                    typedef StaticPriorityQueue<Pointer,MaxChars,Comparator> PrioQ;

                    //__________________________________________________________
                    //
                    // Methods
                    //__________________________________________________________
                    OutputStream &viz(OutputStream &) const; //!< \return graphviz code

                    //! \param maxBits code max bits \return true if tree depth if ok
                    bool          propagate(const size_t maxBits=16) noexcept;

                    //__________________________________________________________
                    //
                    // Members
                    //__________________________________________________________
                    Node *      parent; //!< parent node
                    Node *      left;   //!< left node
                    Node *      right;  //!< right node
                    FreqType    freq;   //!< sum of frequencies
                    CodeType    code;   //!< partial code
                    unsigned    bits;   //!< partial bits
                    Character * leaf;   //!< NULL if not leaf


                private:
                    Y_Disable_Copy_And_Assign(Node); //!< discarding
                    Node()          noexcept;        //!< discarding
                    virtual ~Node() noexcept;        //!< discarding
                };

                static const DataType InnerNodes = 2*MaxChars-1;                           //!< alias
                static const size_t   SizeOfNode = sizeof(Node);                           //!< alias
                static const size_t   InnerBytes = SizeOfNode * InnerNodes;                //!< alias
                static const size_t   InnerWords = Alignment::WordsGEQ<InnerBytes>::Count; //!< alias


                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                explicit Huffman() noexcept; //!< setup
                virtual ~Huffman() noexcept; //!< cleanup

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                void build(Alphabet &alpha) noexcept;

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                Node *         root;                //!< tree root
            private:
                Y_Disable_Copy_And_Assign(Huffman); //!< discarding
                Node *   const nodes;               //!< inner nodes
            public:
                Node::PrioQ    Q;                   //!< inner queue
            private:
                void *         wksp[ InnerWords ];  //!< inner workspace
            };

        }

    }

}

#endif // !Y_Information_Pack_Huffman_Included

