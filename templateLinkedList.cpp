#include <iostream>
#include <string>
//#include <cstdlib>
/* using std::cout;
using std::cin;
using std::string;
using std::endl; */
using namespace std;
template <typename E> class SLinkedList;

template <typename E>
class SNode
{
private:
    E element;          //element of type E (whatever we declare)
    SNode<E> *next;     //reference to next pointer of type template Node
    friend class SLinkedList<E>;
};

template <typename E>
class SLinkedList
{
public:
    SLinkedList();
    ~SLinkedList();
    bool isEmpty() const;
    int getSize();
    const E& getFront() const;
    void addFront(const E &e);
    void removeFront();
    void print();
private:
    SNode<E>* head;
    //int size;
};

template <typename E>
SLinkedList<E>::SLinkedList()
{
    head = NULL;
}

template <typename E>
SLinkedList<E>::~SLinkedList()
{
    while(!isEmpty())
    {
        removeFront();
    }
}

template <typename E>
bool SLinkedList<E>::isEmpty() const
{
    return head == NULL;    //true is head points to NULL (empty)
}

template <typename E>
const E& SLinkedList<E>::getFront() const
{
    return head->element; //data at the head of the list
}

template <typename E>
void SLinkedList<E>::addFront(const E &e)
{
    SNode<E> *newNode = new SNode<E>;   //instantiate new node
    newNode->element = e;
    newNode->next = head;    //if list is empty, head->next is null and newNode->next is now NULL
    head = newNode;     //point head to the newNode;
}

template <typename E>
void SLinkedList<E>::removeFront()
{
    if (!isEmpty())
    {
        SNode<E> *temp = head;
        head = temp->next;
        delete temp;
    }
    else
    {
        cout << "The list is empty. " << endl;
    }
}

template <typename E>
void SLinkedList<E>::print()
{
    SNode<E> *temp = head;        //set pointer to head of list

    if (!isEmpty())
    {
        do
        {
            cout << "Data: " << temp->element << endl;
            temp = temp->next;
        } while (temp != NULL);
    }
    else
    {
        cout << "The list is empty. " << endl;
    }
    
}


int main()
{
    SLinkedList<string> a;
    a.addFront("MSP");
    a.print();
    return 0;
}