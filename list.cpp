#include <iostream>
#include <stack>

using namespace std;

struct Node
{
    int data;
    Node *next;
};

class LinkedList
{
    Node *head = NULL;

    Node* newNode(int value)
    {
        Node *newNode = new Node; // newNode pointer variable contains the address of the new Node
        newNode->data = value;
        newNode->next = NULL;
        return newNode;
    }

public:
    Node *getHead() const { return head; }
    void printList();
    void printListRecF(Node *localHead);
    void printListRecR(Node *localHead);

    void insertatN(int value, int pos = 0);
    void deleteatN(int pos = 0);

    void reverseIter();
    void reverseRec(Node *currentHead);
    void reverseStck();
};

/* print the list in reverse order using recursion*/
void LinkedList::printListRecR(Node *localHead)
{
    if (localHead == NULL)
    {
        return;
    }
    printListRecR(localHead->next);
    // print the node while recursively moving back
    cout << localHead->data << " ";
}

/* print the list in forward using recursion*/
void LinkedList::printListRecF(Node *localHead)
{
    if (localHead == NULL)
    {
        cout << endl;
        return;
    }
    cout << localHead->data << " ";
    // print the current node and move forward
    printListRecF(localHead->next);
    // no work to do while moving back
}

/* print the list using while loop*/
void LinkedList::printList()
{
    Node *localHead = head;
    while (localHead != NULL)
    {
        cout << localHead->data << " ";
        localHead = localHead->next;
    }
    cout << endl;
}

/* delete a node from the list */
void LinkedList::deleteatN(int pos)
{
    if (pos < 0)
    {
        cout << "provide nonneg position\n";
        return;
    }
    Node *curHead = head; // in order to delete the node
    if (pos == 0)
    {
        // empty list
        if (curHead == NULL)
        {
            cout << "empty list\n";
            return;
        }
        // move head to the next node and delete the first node
        head = curHead->next;
        delete curHead;
        cout << "deleted 0th node\n";
        return;
    }

    int i = pos;
    while (--pos) // move to the pos-1
    {
        if (curHead == NULL)
        {
            cout << "out of range\n";
            return;
        }
        curHead = curHead->next;
    }
    if (curHead == NULL) // while loop will not check if the pos-1 node is a null
    {
        cout << "out of range\n";
        return;
    }
    Node *dltNode = curHead->next; // need a pointer to the dlt node to delete it
    if (dltNode == NULL)
    {
        cout << "out of range\n";
        return;
    }
    // pos-1 node should point to the next of the delete node
    // if the delete node is the last element then the current node will point to null
    curHead->next = dltNode->next;
    delete dltNode;
    cout << "deleted " << i << "th node\n";
}

/* insert a new node to the list*/
void LinkedList::insertatN(int value, int pos)
{
    if (pos < 0)
    {
        cout << "provide nonneg position\n";
        return;
    }
    if (pos == 0)
    {
        Node* newNode = LinkedList::newNode(value);

        newNode->next = head; // next should contain the address of the node which head points
        head = newNode;       // head should now point to the new Node
        cout << "inserted node at " << pos << endl;
        return;
    }

    Node *curHead = head;
    int i = pos;
    while (--pos) // move to pos-1
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
    Node* newNode = LinkedList::newNode(value);

    // new node should contain the address of the next node and the previous node should contain the address of the new node
    newNode->next = curHead->next;
    curHead->next = newNode;
    cout << "inserted new node at " << i << endl;
}

/* reverse a list using iteration */
void LinkedList::reverseIter()
{

    Node *prevNode = NULL;
    Node *nextNode;
    Node *current = head;
    while (current != NULL)
    {
        nextNode = current->next;
        current->next = prevNode;
        prevNode = current;
        current = nextNode;
    }
    head = prevNode;
}

/* reverse a list using recursion */
void LinkedList::reverseRec(Node *currentHead)
{
    if (currentHead->next == NULL)
    {
        head = currentHead;
        return;
    }
    reverseRec(currentHead->next);
    currentHead->next->next = currentHead;
    currentHead->next = NULL; // new last link will not have null next value
}

/* reverse a list using stack*/
void LinkedList::reverseStck()
{
    stack<Node *> s;
    Node *curHead = head;
    // push all the addresses of the nodes
    while (curHead != NULL)
    {
        s.push(curHead);
        curHead = curHead->next;
    }
    // assign the last node to head
    head = s.top();
    s.pop();

    // move back through the stack and update the next value in nodes
    curHead = head;
    while (!s.empty())
    {
        curHead->next = s.top();
        s.pop();
        curHead = curHead->next;
    }
    // update the last nodes next to NULL
    curHead->next = NULL;
}

int main()
{
    LinkedList l;
    int n = 5;
    while (n--)
    {
        l.insertatN(n);
        l.printList();
    }
    l.insertatN(11, 1);
    l.printList();
    l.insertatN(12, 2);
    l.printList();
    l.insertatN(13, 7);
    l.printList();
    l.insertatN(14, 9);
    l.printList();
    l.deleteatN();
    l.printList();
    l.deleteatN(2);
    l.printList();
    l.deleteatN(22);

    cout << "recursive forward print\n";
    l.printListRecF(l.getHead());
    cout << "recursive backward print\n";
    l.printListRecR(l.getHead());

    cout << "\nreverse list using iteration\n";
    l.reverseIter();
    l.printList();
    cout << "reverse list using recursion\n";
    l.reverseRec(l.getHead());
    l.printList();
    cout << "reverse list using stack\n";
    l.reverseStck();
    l.printList();
}