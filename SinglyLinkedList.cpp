#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::string;
using std::endl;

class StringNode
{
private:
    string element;
    StringNode *next;

    friend class StringLinkedList;
};


class StringLinkedList
{
private:
    StringNode *head;           //pointer to head
    int size;
    //StringNode *tail;
public:
    StringLinkedList();
    ~StringLinkedList();
    bool isEmpty() const;
    int getSize();
    const string& getFront() const;
    void addFront(const string &e);
    void removeFront();
    void print();
    void addBack(const string &e);
};


StringLinkedList::StringLinkedList()
{
    head = NULL;
    size = 0;
}
//destructor repeatedly deletes nodes using remove function
StringLinkedList::~StringLinkedList()
{
    while(!isEmpty())
    {
        removeFront();
    }
}

int StringLinkedList::getSize()
{
    return size;
}

bool StringLinkedList::isEmpty() const
{
    return head == NULL;    //true is head points to NULL (empty)
}

const string& StringLinkedList::getFront() const
{
    return head->element; //data at the head of the list
}

void StringLinkedList::addFront(const string &e)
{
    StringNode *newNode = new StringNode;   //instantiate new node
    newNode->element = e;
    newNode->next = head;    //if list is empty, head->next is null and newNode->next is now NULL
    head = newNode;     //point head to the newNode;
    size++;
}

void StringLinkedList::removeFront()
{
    if (!isEmpty())
    {
        StringNode *temp = head;
        head = temp->next;
        delete temp;
        size--;
    }
    else
    {
        cout << "The list is empty. " << endl;
    }
}

void StringLinkedList::print()
{
    StringNode *temp = head;        //set pointer to head of list

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
    StringLinkedList list;
    list.addFront("Kyle");
    list.addFront("Megan");
    list.print();
    list.addFront("Tyler");
    list.addFront("Greg");
    list.removeFront();
    list.print();
    cout << list.getSize() << endl;

    return 0;
}