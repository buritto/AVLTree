#include <iostream>
#include <cstdlib>

template <typename  T>
struct  Node
{
public:
     T  Key;

     Node<T> * LeftNode;
     Node<T> * RightNode;

     Node(T key, unsigned char height=0)
     {
         Key = key;
         Height = height;
     }

    static unsigned char GetHeight( Node<T> * node)
     {
         if (!node)
             return 0;
         return node->Height;
     }

     int GetBalanceFactor()
     {
         return  GetHeight(RightNode) -GetHeight(LeftNode);
     }

     void FixHeight()
     {
         unsigned char heightLeftNode = GetHeight(LeftNode);
         unsigned char heightRightNode = GetHeight(RightNode);

         if (heightLeftNode > heightRightNode)
             Height = static_cast<unsigned char>(heightLeftNode + 1);
         else
              Height = static_cast<unsigned char>(heightRightNode + 1);
     }

    static Node<T> * RightTurn(Node<T> * nodeForTurn)
     {
         Node<T> * node = nodeForTurn -> LeftNode;
         nodeForTurn ->  LeftNode = node->RightNode;
         node->RightNode = nodeForTurn;
         nodeForTurn -> FixHeight();
         node->FixHeight();
         return node;
     }

    static Node <T> * LeftTurn(Node<T> * nodeForTurn)
     {
         Node<T> * node  = nodeForTurn->RightNode;
         nodeForTurn -> RightNode = node->LeftNode;
         node->LeftNode = nodeForTurn;
         nodeForTurn->FixHeight();
         node->FixHeight();
         return node;
     }

private:
    unsigned char  Height;

};


template <typename T>

struct AvlTree
{
public:
    Node<T> * Root;

    AvlTree(Node<T> * root)
    {
        Root = root;
    }

    Node<T> *  Balance(Node<T> * node)
    {
        node->FixHeight();
        if (node->GetBalanceFactor() == 2)
        {
            if (node->RightNode->GetBalanceFactor() < 0)
            {
                node->RightNode = Node<T>::RightTurn(node->RightNode);
            }
            return  Node<T>::LeftTurn(node);

        }
        if (node->GetBalanceFactor() == -2)
        {
            if(node->LeftNode->GetBalanceFactor() > 0)
            {
                node->LeftNode = Node<T>::LeftTurn(node->LeftNode);
            }
            return  Node<T>::RightTurn(node);
        }
        return  node;
    }

    void Add(T key)
    {
        Root  = AddNode(Root, key);
    }

    void Remove(T key)
    {
        Root  = RemoveNode(Root, key);
    }

    T GetMin()
    {
        GetMin(Root);
    }

private:

    T GetMin(Node<T> * node)
    {
        if (!node)
        {
            throw std::invalid_argument( "tree does not have Node" );
        }
        if (node->LeftNode)
            return GetMin(node->LeftNode);
        return node->Key;
    }

    Node<T> * AddNode(Node<T> * node, T key)
    {
        if (!node)
            return new Node<T>(key);
        if (key <  node->Key)
                node->LeftNode =  AddNode(node->LeftNode, key);
        else
            node->RightNode = AddNode(node->RightNode, key);
        return Balance(node);
    }

    Node<T> *  FindMin(Node<T> * node)
    {
        if (node->LeftNode)
            return FindMin(node->LeftNode);
        return node;
    }

    Node<T> * RemoveNodeWithMinKey(Node<T> * node )
    {
        if (!node->LeftNode)
            return node->RightNode;
        node->LeftNode = RemoveNodeWithMinKey(node->LeftNode);
        return Balance(node);
    }

    Node<T> * RemoveNode(Node<T>* node, T key)
    {
        if (key <  node->Key)
            node->LeftNode = RemoveNode(node->LeftNode, key);
        else
        {
            if (key > node->Key)
                node->RightNode  = RemoveNode(node->RightNode, key);
            else{

                Node<T> * left = node->LeftNode;
                Node<T> * right = node->RightNode;

                delete(node);

                if (!right)
                {
                    if (left)
                        return left;
                    return nullptr;
                }

                Node<T> * minNode = FindMin(right);
                minNode->RightNode = RemoveNodeWithMinKey(right);
                minNode->LeftNode = left;
                return Balance(minNode);
            }
        }
        return Balance(node);
    }
};


int main() {
    auto * tree = new AvlTree<int>(new Node<int>(83));
    tree->Add(35);
    tree->Add(15);
    tree->Add(21);
    tree->Add(50);
    tree->Add(49);
    tree->Add(77);
    tree->Add(86);
    tree->Add(86);
    tree->Add(93);
    tree->Add(92);

    tree->Remove(50);
    tree->Remove(93);
    tree->Remove(92);

    int min = tree->GetMin();
    return 0;
}