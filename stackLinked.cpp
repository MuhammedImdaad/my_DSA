#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node *next;
};

//since push and pop will happend from the beginning of the list, head will be the top of stack
class Stack
{
    Node *top; 

public:
    Stack()
    {
        top = NULL;
    }

    void push(int elem) //equivalent to insert at pos=0
    {
        Node* newNode = new Node;
        newNode->data = elem;
        newNode->next = top;
        top = newNode;
    }

    void pop() //equivalent to delete at pos=0
    {
        if (top==NULL)
        {
            cout << "stack underflow\n";
            return;
        }

        Node* dltNode = top;
        top = dltNode->next;
        delete dltNode;
    }

    void print()
    {
        Node* curHead = top;
        while(curHead!=NULL)
        {
            cout << curHead->data << " ";
            curHead = curHead->next;
        }
        cout << endl;


    }
};

int main()
{
    Stack stack;
    stack.pop();
    stack.push(4);
    stack.push(2);
    stack.push(5);
    stack.print();
    stack.pop();
    stack.print();
}