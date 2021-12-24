#include <queue>
#include <iostream>
using namespace std;

class stack
{
    // last in first out
    queue<int> q1;
    queue<int> q2;
    int curSize = 0;

    public:
    void push(int elem)
    {
        //front of q1 contain the old values
        q1.push(elem);
        ++curSize;
    }
    void pop()
    {
        if (curSize == 0)
        {
            cout << "empty queue\n";
            return;
        }
        if (curSize == 1)
        {
            //since only one element in the queue, dequeus will perform expected pop
            cout << "remove " << q1.front() << endl;
            q1.pop();
            --curSize;
            return;
        }
        int count = curSize;
        while (--count) //curSize-1
        {
            //remove all the elements except the last in element and enqueue elements to q2
            q2.push(q1.front());
            q1.pop();
        }
        cout << "remove " << q1.front() << endl;
        q1.pop();
        --curSize;

        //since now q2 contains the elements swap the names
        queue<int> temp;
        temp = q1;
        q1 = q2;
        q2 = temp;
    }
};

int main()
{
    stack s;
    s.push(5);
    s.push(1);
    s.push(2);
    s.push(6);
    s.pop();
    s.push(3);
    s.pop();
    s.pop();
    s.pop();
    s.pop();
    s.pop();

}