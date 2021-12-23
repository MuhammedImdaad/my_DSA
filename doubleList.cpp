#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node *next;
    Node *prev;
};

class DoubleList
{
    Node *head = NULL;

    public:
    void insertatN(int elem, int pos = 0);
    void printList();
    void deleteatN(int pos = 0);
    void printListR();
};

void DoubleList::insertatN(int elem, int pos)
{
    Node *newNode = new Node;
    newNode->data = elem;
    newNode->prev = NULL;
    newNode->next = NULL;

    if (pos == 0)
    {
        newNode->next = head;
        head = newNode;
        if (newNode->next != NULL)
        {
            newNode->next->prev = newNode;
        }
        cout << "insert node at 0\n";
        return;
    }
    Node *curHead = head;
    int i=pos;
    while (--pos)
    {
        if (curHead == NULL)
        {
            cout << "out of range\n";
            return;
        }
        curHead = curHead->next;
    }
    if (curHead == NULL)
    {
        cout << "out of range\n";
        return;
    }
    newNode->prev = curHead;
    newNode->next = curHead->next;
    if (curHead != NULL)
        curHead->next->prev = newNode;
    curHead->next = newNode;
    cout << "insert node at " << i<<endl;
}

void DoubleList::printList()
{
    Node* curHead = head;
    while (curHead != NULL)
    {
        cout << curHead->data << " ";
        curHead = curHead->next;
    }
    cout << endl;
}

void DoubleList::printListR()
{
    Node* curHead = head;
    while (curHead->next != NULL)
    {
        curHead = curHead->next;
    }
    while (curHead != NULL)
    {
        cout << curHead->data << " ";
        curHead = curHead->prev;
    }
    cout << endl;
}

void DoubleList::deleteatN(int pos)
{

    if (pos == 0)
    {
        Node *dltNode = head;
        dltNode->next->prev = NULL;
        head = dltNode->next;
        delete dltNode;
        cout << "\nfirst node deleted\n";
        return;
    }
    Node *curHead = head;
    while (pos--)
    {
        if (curHead == NULL)
        {
            cout << "out of range\n";
            return;
        }
        curHead = curHead->next;
    }
    curHead->prev->next = curHead->next;
    if (curHead->next != NULL)
        curHead->next->prev = curHead->prev;
    delete curHead;
    cout << "node deleted\n";
}


int main()
{
    DoubleList d;
    int n=5;
    while (n--)
    {
        d.insertatN(n);
        d.printList();
    }
    d.insertatN(10, 3);
    d.printList();
    d.insertatN(11, 3);
    d.printList();
    d.insertatN(9, 10);
    d.printList();
    d.insertatN(14, 9);
    d.printList();
    d.printListR();
    d.deleteatN();
    d.printList();
    d.deleteatN(2);
    d.printList();
    d.deleteatN(9);
    d.printList();
    return 0;
}