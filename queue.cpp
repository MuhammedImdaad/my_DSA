#include <iostream>
using namespace std;

template <typename T>
class Queue
{
    int front;
    int rear;
    T *q;
    // circular array (current element i, next element (i+1)%N))
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
        // if the queue is empty, front and rear both would be -1
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
        // if front is the next value of rear, queue is full
        if (front == (rear + 1) % N)
            return true;
        else
            return false;
    }

    void enqueue(T elem)
    {
        if (isFull())
        {
            cout << "queue is full\n";
            return;
        }

        if (isEmpty()) // if empty, front and rear will both point to 0th location
            front = rear = 0;
        else
            rear = (rear + 1) % N; //rear++
        q[rear] = elem;
    }

    void dequeue()
    {
        if (isEmpty())
        {
            cout << "queue is empty\n";
            return;
        }
        //when queue contain only one element
        if (front == rear) 
            front = rear = -1;
        else
            front = (front + 1) % N; //front++
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
    {
        q.enqueue(n);
        q.print();
    }
    q.enqueue(n);
    n = 11;
    while (n--)
    {
        q.dequeue();
        q.print();
    }
}