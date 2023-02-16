#include "chain.h"
#include "chain_given.cpp"
#include <cmath>
#include <iostream>

// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain() //not sure about this
{
    clear();
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
void Chain::insertBack(const Block &ndata) //why create a new ListNode?
{
    Node *new_node = new Node(ndata); 

    Node *temp = walk(head_, length_);

    temp->next = new_node;
    length_++;
}


/**
 * Swaps the two nodes at the indexes "node1" and "node2".
 * The indexes of the nodes are 1 based.
 * assumes i and j are valid (in {1,length_} inclusive)
 * 
 */
void Chain::swap(int i, int j)
{
    Node *node_before_n1 = walk(head_, i-1);
    Node *node_before_n2 = walk(head_, j-1);
    Node *node_1 = node_before_n1->next;
    Node *node_2 = node_before_n2->next;
    Node *temp;

    if (i == j) {
        return;
    }

    if (node_before_n1 == node_2) {
        node_before_n2->next = node_1;
        node_2->next = node_1->next;
        node_1->next = node_2;
    }
    else if (node_before_n2 == node_1) {
        node_before_n1->next = node_2;
        node_1->next = node_2->next;
        node_2->next = node_1;
    }
    else {
        node_before_n1->next = node_2;
        node_before_n2->next = node_1;

        temp = node_1->next;
        node_1->next = node_2->next;
        node_2->next = temp;
    }
}

/**
 * Reverses the chain
 */
void Chain::reverse()
{
    for (int i = 1; i <= (int) length_/2; i++) {
        swap(i, length_-i+1); 
    }
}

/*
* Modifies the current chain by "rotating" every k nodes by one position.
* In every k node sub-chain, remove the first node, and place it in the last 
* position of the sub-chain. If the last sub-chain has length less than k,
* then don't change it at all. 
* Some examples with the chain a b c d e:
*   k = 1: a b c d e
*   k = 2: b a d c e
*   k = 3: b c a d e
*   k = 4: b c d a e
*/
void Chain::rotate(int k)
{
    Node *last;
    Node *before_first = head_;
    Node *first;

    if (k == 1 || k > length_) {
        return;
    }

    for (int i=1; i+k-1 <= length_; i = i+k) {
        last = walk(before_first->next, k-1);

        first = before_first->next;
        before_first->next = first->next;
        first->next = last->next; 
        last->next = first;

        before_first = first;
    }
}

/**
 * Destroys ALL dynamically allocated memory associated with the
 * current Chain class.
 */
void Chain::clear()
{
    Node * temp = head_;
    Node * temp_2 = head_;

    for (int i = 0; i <= length_; i++) {
        temp = temp->next;
        delete temp_2;
        temp_2 = temp;   
    }

    head_ = NULL;
    length_ = 0;
    height_ = 0;
    width_ = 0;
}

/* makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::copy(Chain const &other)
{
    Node *stepper = other.head_;

    head_ = new Node(stepper->data);
    length_ = other.length_;
    height_ = other.height_;
    width_ = other.width_;

    Node *temp = head_;

    stepper = stepper->next;

    for (int i=1; i<= other.length_; i++) {
        temp->next = new Node(stepper->data);
        temp = temp->next;
        stepper = stepper->next;
    }
}
