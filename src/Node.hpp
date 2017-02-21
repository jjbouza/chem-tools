//
//  Node.hpp
//  Chemistry
//
//  Created by Jose Bouza on 2/20/16.
//  Copyright © 2016 Jose Bouza. All rights reserved.
//

//Abstract tree like structure. Used to store chemical formula data. Consider internal redeisgn using smart pointers. 

#ifndef Node_hpp
#define Node_hpp


#include <vector>
#include <map>
#include <stdexcept>
#include <utility> 


template <class NodeType>
class Node {
    
public:
    
    Node(NodeType data_in, int multiplier);
    Node(int mulitplier);
    Node();
    //Copy constructor
    Node(const Node<NodeType>& other);
    
    
    ~Node();
    void setMultiplier(int mult);
    
    //The node is internally stored as a pointer. The pointer must be initilaized on the heap and the ownership is transferred to the parent node.
    int addBranch(Node<NodeType>* node, int multiplierin);
    
    //For nodes that only consist of data (no child nodes)
    int addBranch(NodeType child_contents, int multiplier);
    
    void setData(NodeType data_in);
    
    Node* branch(int node_id) const;
    
    int getMultilier();
    
    bool containsData();
    
    NodeType get();
    
    int getKeyBuffer();
    
    //Frees memory of all child nodes.
    void delete_node();
    
    void delete_branch(int branch_id);
    
    std::vector<Node<NodeType>> generateChildList();
    
    
private:
    
    std::map<int, Node<NodeType>*> children;
    NodeType data;
    bool contains_data;
    int key_buffer;
    int mulitplier;
    
};

template <class NodeType>
Node<NodeType>::Node(NodeType data_in, int multiplier)
{
    Node::key_buffer = 0;
    Node::contains_data = false;
    Node::mulitplier = multiplier;
    Node::setData(data_in);
}

template <class NodeType>
Node<NodeType>::Node(int mulitplier)
{
    Node::key_buffer = 0;
    Node::contains_data = false;
    Node::mulitplier = mulitplier;
}

template <class NodeType>
Node<NodeType>::Node()
{
    Node::key_buffer = 0;
    Node::contains_data = false;
    Node::mulitplier = 1;
}


template <class NodeType>
Node<NodeType>::Node(const Node<NodeType>& other)
{
    //Copy children
    for(int i = 1; i <= other.key_buffer; i++)
    {
        Node<NodeType> child = Node(*other.branch(i));
        
        this->children[i] = new Node<NodeType>( child );
    }
    
    this->data = other.data;
    this->contains_data = other.contains_data;
    this->key_buffer = other.key_buffer;
    this->mulitplier = other.mulitplier;
    
}

template <class NodeType>
Node<NodeType>::~Node()
{
    for(int i = 1; i <= Node::key_buffer; i++)
    {
        delete children[i];
    }
}

template <class NodeType>
void Node<NodeType>::setMultiplier(int mult)
{
    Node::mulitplier = mult;
}

//The node is internally stored as a pointer. The pointer must be initilaized on the heap and the ownership is transferred to the parent node.
template <class NodeType>
int Node<NodeType>::addBranch(Node<NodeType>* node, int multiplierin)
{
    Node::key_buffer++;
    node->mulitplier = multiplierin;
    children[Node::key_buffer] = node;
    return Node::key_buffer;
}

//For nodes that only consist of data (no child nodes)
template <class NodeType>
int Node<NodeType>::addBranch(NodeType child_contents, int multiplier)
{

    Node::key_buffer++;
    children[Node::key_buffer] = new Node(child_contents, multiplier);
    return Node::key_buffer;
    
}

template <class NodeType>
void Node<NodeType>::setData(NodeType data_in)
{
    Node::data = data_in;
    contains_data = true;
}

template <class NodeType>
Node<NodeType>* Node<NodeType>::branch(int node_id) const
{
    if(children.count(node_id) == 1)
    {
        return children.at(node_id);
    }
    
    else
    {
        //Branch ID does not exist
        throw std::invalid_argument("Branch ID does not exist");
    }
    
}

template <class NodeType>
int Node<NodeType>::getMultilier()
{
    return Node::mulitplier;
}

template <class NodeType>
bool Node<NodeType>::containsData()
{
    return contains_data;
}

template <class NodeType>
NodeType Node<NodeType>::get()
{
    if(contains_data == true)
    {
        return data;
    }
    
    else
    {
        //No data
        throw std::invalid_argument("No data");
    }
}

template <class NodeType>
int Node<NodeType>::getKeyBuffer()
{
    return key_buffer;
}

//Frees memory of all child nodes.
template <class NodeType>
void Node<NodeType>::delete_node()
{
    for(int i = 1; i <= key_buffer; i++)
    {
        delete children[i];
    }
}

template <class NodeType>
void Node<NodeType>::delete_branch(int branch_id)
{
    if(children.count(branch_id) == 1)
    {
        children.erase(branch_id);
    }
    
    else
    {
        //Branch ID does not exist
        throw std::invalid_argument("Branch ID does not exist");
    }
}

//If you modify elements in the child list you will modify the original Node*!. If you would like
//to modify make a copy using the copy constructor.
template <class NodeType>
std::vector<Node<NodeType>> Node<NodeType>::generateChildList()
{
    std::vector<Node<NodeType>> child_list;
    
    if(key_buffer > 0)
    {
        for(int i = 1; i <= key_buffer; i++)
        {
            child_list.push_back(*branch(i));
        }
    }
    return child_list; 
}


#endif /* multipliertree_hpp */
