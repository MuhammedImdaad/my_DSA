#include <iostream>

using namespace std;

template <typename T>
class Stack
{
    int top;
    int size;
    T *arrayPtr;

public:
    Stack(int size)
        : size(size), top(-1)
    {
        arrayPtr = new T[size];
        cout << "created stack\n";
    };

    void push(T elem)
    {
        if (top == size - 1)
        {
            cout << "stack overflow\n";
            return;
        }
        arrayPtr[++top] = elem; // overwrite the value and increment the top
    }

    void pop()
    {
        if (top == -1)
        {
            cout << "stack underflow\n";
            return;
        }
        --top; // decrement the top
    }

    int getTop()
    {
        return arrayPtr[top];
    }

    bool is_empty()
    {
        return top == -1;
    }

    void printStack()
    {
        for (int i = 0; i < top + 1; i++)
        {
            cout << arrayPtr[i] << " ";
        }
        cout << endl;
    }

    ~Stack()
    {
        delete[] arrayPtr;
        cout << "deleted array\n";
    }
};

int main()
{
    Stack<int> stack(3);
    stack.push(1);
    stack.printStack();
    stack.push(2);
    stack.printStack();
    stack.push(3);
    stack.printStack();
    stack.push(4);
    stack.printStack();
    stack.pop();
    stack.printStack();
    stack.pop();
    stack.printStack();
    stack.pop();
    stack.printStack();
    stack.pop();
    stack.printStack();
}