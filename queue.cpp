#include <iostream>
using namespace std;

template <typename T>
class Queue
{
    int front;
    int rear;
    T *q;
    int N;

public:
    Queue(int size)
    {
        N = size;
        q = new T[size];
        front = rear = -1;
    }
    T top()
    {
        return q[front];
    }
    bool isEmpty()
    {
        if (rear == -1 && front == -1)
            return true;
        else
            return false;
    }
    void print()
    {
        if (!isEmpty())
        {
            for (int i = front; i < rear + 1; i++)
                cout << q[i] << " ";
        }
        cout << endl;
    }
    bool isFull()
    {
        if (front == (rear + 1) % N)
            return true;
        else
            return false;
    }
    void enqueue(T elem)
    {
        if (isFull())
            return;
        if (isEmpty())
            front = rear = 0;
        else
            rear = (rear + 1) % N;
        q[rear] = elem;
    }

    void dequeue()
    {
        if (isEmpty())
            return;
        if (front == rear)
            front = rear = -1;
        else
            front = (front + 1) % N;
    }
    ~Queue()
    {
        delete[] q;
    }
};

int main()
{
    int n = 11;

    Queue<int> q(n);
    while (n--)
        q.enqueue(n);
    q.print();
    n = 11;
    while (n--)
    {
        q.dequeue();
        q.print();
    }
}