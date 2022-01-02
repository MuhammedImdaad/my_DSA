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

    Node *newElem(int data)
    {
        Node *node = new Node;
        node->data = data;
        node->next = node->prev = NULL;
        return node;
    }

public:
    void insertatN(int elem, int pos = 0);
    void printList();
    void deleteatN(int pos = 0);
    void printListR();
};

/* node insertion for double list */
void DoubleList::insertatN(int elem, int pos)
{
    // creata new node
    Node *newNode = newElem(elem);

    // if pos=0, head should point to the new node
    if (pos == 0)
    {
        newNode->next = head;
        head = newNode;
        // if the list is not empty, previous head node should now point the new node in prev
        if (newNode->next != NULL)
        {
            newNode->next->prev = newNode;
        }
        cout << "insert node at 0\n";
        return;
    }

    Node *curHead = head; // to traverse the list
    int i = pos;
    while (--pos) // move to the pos-1 node
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

    // update prev and next pointes with pos-1 and pos+1 nodes
    newNode->next = curHead->next;
    curHead->next = newNode;
    newNode->prev = curHead;
    // if pos+1 node it should contain the new node in prev pointer
    if (newNode->next != NULL)
        newNode->next->prev = newNode;

    cout << "insert node at " << i << endl;
}

/* traverse the list in forward*/
void DoubleList::printList()
{
    Node *curHead = head;
    while (curHead != NULL)
    {
        cout << curHead->data << " ";
        curHead = curHead->next;
    }
    cout << endl;
}

/* traverse the list in backward */
void DoubleList::printListR()
{
    Node *curHead = head;
    while (curHead->next != NULL) // move to the last node
    {
        curHead = curHead->next;
    }
    while (curHead != NULL) // move back to the front
    {
        cout << curHead->data << " ";
        curHead = curHead->prev;
    }
    cout << endl;
}

/* delete a node in the list*/
void DoubleList::deleteatN(int pos)
{
    if (head == NULL)
        return;
    if (pos == 0)
    {
        // update the head+1 node's prev pointer and head move forward
        Node *dltNode = head;
        //since head is not NULL
        dltNode->next->prev = NULL;
        head = dltNode->next;
        delete dltNode;
        cout << "\nfirst node deleted\n";
        return;
    }

    Node *curHead = head; // to move to pos-1
    while (--pos)         // move to the pos-1 node and update pos-1 and pos+1 nodes
    {
        if (curHead == NULL)
        {
            cout << "out of range\n";
            return;
        }
        curHead = curHead->next;
    }


    Node *dltNode = curHead->next;
    curHead->next = dltNode->next;
    if (dltNode->next != NULL)
        dltNode->next->prev = curHead;
    delete dltNode;
    cout << "node deleted\n";
}

int main()
{
    DoubleList d;
    int n = 5;
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