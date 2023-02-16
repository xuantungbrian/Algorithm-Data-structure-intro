// linked_list.cc -- functions for linked_list lab (cs221)

#include "linked_list.h"

/**
 * Inserts a new Node (with key=newKey) at the head of the linked_list.
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty)
 * PRE: newKey is the value for the key in the new Node
 * POST: the new Node is now the head of the linked_list
 */
void insert(Node *&head, int newKey)
{
    Node *curr = new Node(newKey, head);
    head = curr;
}

/**
 * Print the keys of a linked_list in order, from head to tail
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty)
 */
void print(Node *head)
{
    std::cout << "[";
    for (Node *curr = head; curr != NULL; curr = curr->next)
    {
        std::cout << curr->key;
        if (curr->next != NULL)
            std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

/**
 * Returns the size (number of Nodes) of the linked_list
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty)
 */
int size(Node *head)
{
    if (!head) return 0;
    return 1 + size(head->next);
}

/**
 * Copies the keys in a linked list to a vector.
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty)
 * POST: a new vector<int> containing the keys in the correct order has been returned.
 */
std::vector<int> to_vector(Node *head)
{
    std::vector<int> result;
    for (Node *curr = head; curr != NULL; curr = curr->next)
    {
        result.push_back(curr->key);
    }
    return result;
}

/**
 * Delete the last Node in the linked_list
 * PRE: head is the first Node in a linked_list (if NULL, linked_list is empty)
 * POST: the last Node of the linked_list has been removed
 * POST: if the linked_list is now empty, head has been changed
 * POST: else head remains the first Node in the linked_list
 */
void delete_last_element(Node *&head)
{
    if (head == NULL) {
        return;
    }

    if (head->next == NULL) {
        delete head; //should I do it like this?
        head = NULL;
        return;
    }

    delete_last_element(head->next);
}

/**
 * Removes an existing Node (with key=oldKey) from the linked_list.
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty)
 * PRE: oldKey is the value of the key in the Node to be removed
 * PRE: if no Node with key=oldKey exists, the linked_list has not changed
 * POST: if a Node with key=oldKey was found, then it was deleted
 * POST: other Nodes with key=oldKey might still be in the linked_list
 * POST: head is the new first Node of the linked_list, if updated
 */
void remove(Node *&head, int oldKey)
{
    if (head == NULL) {
        return;
    }

    if (head->key == oldKey) {   
        if (head->next == NULL) {
            delete head; //why this change 1 line and works?
            head = NULL;
        }
        else {
            Node *temp = head->next;
            delete head;
            head = temp;
        }
        return;
    }

    if (head->next != NULL) {
        if (head->next->key == oldKey) {
            Node *temp = head->next->next;
            delete head->next;
            head->next = temp;
            return;
        }
        remove(head->next, oldKey);
    }
}

/**
 * Insert a new Node (with key=newKey) after an existing Node (with key=oldKey)
 * If there is no existing Node with key=oldKey, then no action.
 * PRE: head is the first Node in a linked_list (if NULL, linked_list is empty)
 * PRE: oldKey is the value to look for (in the key of an existing Node)
 * PRE: newKey is the value of the key in the new Node (that might be inserted)
 * POST: if no Node with key=oldKey was found, then the linked_list has not changed
 * POST: else a new Node (with key=newKey) is right after the Node with key = oldKey.
 */
void insert_after(Node *head, int oldKey, int newKey)
{
    while (head != NULL) {
        if (head->key == oldKey) {
            if (head->next == NULL) {
                head->next = new Node(newKey, NULL);
            }
            else {
                head->next = new Node(newKey, head->next);
            }
            return;
        }
        head = head->next;
    }
}

/**
 * Create a new linked_list by merging two existing linked_lists.
 * PRE: list1 is the first Node in a linked_list (if NULL, then it is empty)
 * PRE: list2 is the first Node in another linked_list (if NULL, then it is empty)
 * POST: A new linked_list is returned that contains new Nodes with the keys from
 * the Nodes in list1 and list2, starting with the key of the first Node of list1,
 * then the key of the first Node of list2, etc.
 * When one list is exhausted, the remaining keys come from the other list.
 * For example: [1, 2] and [3, 4, 5] would return [1, 3, 2, 4, 5]
 */
Node *interleave(Node *list1, Node *list2) //will this be pass by reference or value in the recursion?
{
    int i = 2;

    if (list1 == NULL && list2 != NULL) {
        Node *list3 = new Node(list2->key, NULL);
        list2 = list2->next;
        Node *temp_node = list3;
        while (list2 != NULL) {
            temp_node->next = new Node(list2->key, NULL);
            temp_node = temp_node->next;
            list2 = list2->next;
        }
        return list3;
    }
    else if (list1 == NULL && list2 == NULL) {
        return NULL;
    }

    Node *list3 = new Node(list1->key, NULL);
    Node *temp_node = list3;
    list1 = list1->next;

    while (list1 != NULL && list2 != NULL) {
        if (i%2 == 1) {    
            temp_node->next = new Node(list1->key, NULL);
            temp_node = temp_node->next;
            list1 = list1->next;
        }
        else {  
            temp_node->next = new Node(list2->key, NULL);
            temp_node = temp_node->next;
            list2 = list2->next;
        }
        i++;
    }

    if (list1 == NULL && list2 != NULL) {
        while (list2 != NULL) {
            temp_node->next = new Node(list2->key, NULL);
            temp_node = temp_node->next;
            list2 = list2->next;
        }
    }
    else if (list1 != NULL && list2 == NULL) {
        while (list1 != NULL) {
            temp_node->next = new Node(list1->key, NULL);
            temp_node = temp_node->next;
            list1 = list1->next;
        }
    }
    temp_node = NULL;
    return list3; 
}
