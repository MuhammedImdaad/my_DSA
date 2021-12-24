#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *next;
};
class Queue
{
    // with two pointers at the front and rear, queue implementation is rather straightforward using list
    Node *front = NULL;
    Node *rear = NULL;

public:
    bool isEmpty()
    {
        // if the queue is empty, front and rear both would be -1
        if (rear == NULL && front == NULL)
            return true;
        else
            return false;
    }

    void enqueue(int elem)
    {
        Node *newNode = new Node;
        newNode->data = elem;
        newNode->next = NULL;

        if (isEmpty())
        {
            front = rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void printList()
    {
        Node *curHead = front;
        while (curHead != NULL)
        {
            cout << curHead->data << " ";
            curHead = curHead->next;
        }
        cout << endl;
    }

    int top()
    {
        if (isEmpty())
        {
            cout << "queue is empty\n";
            return -1;
        }
        return front->data;
    }

    void dequeue()
    {
        if (isEmpty())
        {
            cout << "queue is empty\n";
            return;
        }

        Node *dltNode = front;

        // when queue contain only one element
        if (front == rear)
        {
            front = rear = NULL;
        }
        else
        {
            front = dltNode->next;
        }
        delete dltNode;
    }
};

int main()
{
    Queue q;
    int n = 11;
    while (n--)
    {
        q.enqueue(n);
        q.printList();
    }

    n = 11;
    while (n--)
    {
        q.dequeue();
        q.printList();
    }
}