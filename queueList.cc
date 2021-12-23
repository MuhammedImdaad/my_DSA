#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *next;
};
class Queue
{
    Node *front = NULL;
    Node *rear = NULL;

    public:
    void enqueue(int elem)
    {
        Node *newNode = new Node;
        newNode->data = elem;
        newNode->next = NULL;

        if (front == NULL && rear == NULL)
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
        Node* curHead = front;
        while(curHead!=NULL)
        {
            cout << curHead->data << " ";
            curHead = curHead->next;
        }
        cout << endl;
    }

    int top()
    {
        return front->data;
    }

    void dequeue()
    {
        if (front==NULL) return;
        Node* dltNode = front;
        if(front==rear)
        {
            front=rear=NULL;
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
    int n=10;
    while(n--) q.enqueue(n);
    q.printList();
    n=10;
    while(n--)
    {
        q.dequeue();
        q.printList();
    }
    

}