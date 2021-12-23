#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node *next;
};

class Stack
{
    Node *top;

public:
    Stack()
    {
        top = NULL;
    }

    void push(int elem)
    {
        Node* newNode = new Node;
        newNode->data = elem;
        newNode->next = top;
        top = newNode;
    }

    void pop()
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