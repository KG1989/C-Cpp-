#include <iostream>
#include <string>
#include <cstdlib>
#include <assert.h>
using std::cout;
using std::cin;
using std::string;
using std::endl;

class DubLinkedList
{
    private:
        struct Node
        {
            Node *prev;
            Node *next;
            int data;
        };
        Node *head;         //sentinels
        Node *tail;
        int size;
    
    public:
        DubLinkedList();
        ~DubLinkedList();
        bool isEmpty() const;
        const int& getFront() const;
        const int& getBack() const;
        const int& getSize() const;
        void addFront(const int val);
        void addBack(const int val);
        void removeFront();
        void removeBack();
        void printList();
        void addSomewhere(Node *ref, const int val);
        void removeSomewhere(Node *removeMe);
};

DubLinkedList::DubLinkedList()
{
    head = new Node;            //create sentinels - these nodes hold no data
    //assert(head != NULL);
    tail = new Node;            //have them point to each other initially
    //assert(tail != NULL);
    head->next = tail;
    head->prev = NULL;
    tail->prev = head;
    tail->next = NULL;
    size = 0;
}

DubLinkedList::~DubLinkedList()
{
    while (!isEmpty())
    {
        removeFront();
    }
    delete head;
    delete tail;
}

const int& DubLinkedList::getSize() const
{
    return size;
}

bool DubLinkedList::isEmpty() const
{
    return head->next == tail;          //if the initial condition is true then the list is empty. 
}

const int& DubLinkedList::getFront() const
{
    return head->next->data;
}

const int& DubLinkedList::getBack() const
{
    return tail->prev->data;
}

void DubLinkedList::addSomewhere(Node *ref, const int val)
{
    Node *newNode = new Node;
    newNode->data = val;
    
    newNode->next = ref;           //newNode before reference node
    newNode->prev = ref->prev;
    ref->prev->next = newNode;
    ref->prev = newNode;

    size++;
}

void DubLinkedList::addFront(const int val)
{
    addSomewhere(head->next, val);  //add right after the head node, before any other nodes.
}

void DubLinkedList::removeSomewhere(Node *removeMe)
{
    Node *before = removeMe->prev;
    Node *after = removeMe->next;
    after->prev = before;
    before->next = after;

    delete removeMe;
    removeMe = NULL;
}

void DubLinkedList::removeFront()
{
    removeSomewhere(head->next);
}

void DubLinkedList::printList()
{
    Node *temp = head->next;
    
    do
    {
        cout << temp->data << endl;
        temp = temp->next;
    } while (temp != tail);
}

int main() 
{
    DubLinkedList *Dlist = new DubLinkedList;
    
    Dlist->addFront(5);
    Dlist->addFront(4);
    //cout << Dlist->getSize() << endl;
    Dlist->addFront(3);
    Dlist->addFront(7);
    cout << Dlist->getSize() << endl;
    cout << Dlist->getFront() << endl;
    cout << Dlist->getBack() << endl;
    Dlist->printList();
    
    delete Dlist;
    return 0;
}




