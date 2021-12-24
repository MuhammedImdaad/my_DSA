#include <stack>
#include <iostream> 

using namespace std;

class queue
{
    //last in last out
    stack<int> s1;
    stack<int> s2;

    public:

    void enqueue(int elem)
    {
        //the old values will be at the top of the stack
        s1.push(elem);
    }

    void dequeue()
    {
        if (s1.empty() && s2.empty()) 
        {
            cout << "queue is empty\n";
            return;
        }

        if(s2.empty())
        {
            //remove all the elements from the s1 stack and push to s2 stack. now top of s2 will be the oldest element
            while(!s1.empty())
            {
                s2.push(s1.top());
                s1.pop();
            }
            cout << "removed " << s2.top() << endl;
            s2.pop();
            return;
        }
        //if s2 is not empty it contain the oldest elements
        cout << "removed " << s2.top() << endl;
        s2.pop();
    }

};

int main()
{
    queue q;
    int n=5;
    while(n--)
    {
        q.enqueue(n);
    }
    while(n++<5)
    {
        q.dequeue();
    }
}