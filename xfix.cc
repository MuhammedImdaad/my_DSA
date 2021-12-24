#include <iostream>
#include <stack>

using namespace std;

int evaluateInfix(const string &);
int evaluatePostfix(const string &);
string infixToPostfix(const string &);
bool isHigherPrecid(char first, char second);

int main()
{
    cout << evaluatePostfix("23*54*+9-") << endl;
    cout << evaluatePrefix("-+*23*549") << endl;
    cout << infixToPostfix("A+B*C-D*E") << endl;
    cout << infixToPostfix("((A+B)*C-D)*E") << endl;
    cout << infixToPostfix("A*(B+C)") << endl;
}

/* derive the value of a sequence written in postfix notation*/
int evaluatePostfix(const string &expr)
{
    stack<int> s;
    for (auto &i : expr)
    {
        if (i == '+' || i == '-' || i == '*' || i == '/')
        {
            int op1 = s.top();
            s.pop();
            int op2 = s.top();
            s.pop();
            cout << "op1 " << op1 << " ,op2 " << op2 << endl;
            if (i == '+')
                s.push(op2 + op1);
            else if (i == '-')
                s.push(op2 - op1);
            if (i == '*')
                s.push(op2 * op1);
            if (i == '/')
                s.push(op2 / op1);
        }
        else
            s.push(i - '0'); //char to int 
    }
    return s.top(); 
}

/* derive the value of a sequence written in Infix notation*/
int evaluatePrefix(const string &expr)
{
    //except for iterating backward logic is identical to post fix notation
    stack<int> s;
    for (auto i = expr.rbegin(); i < expr.rend(); i++)
    {
        if (*i == '+' || *i == '-' || *i == '*' || *i == '/')
        {
            int op1 = s.top();
            s.pop();
            int op2 = s.top();
            s.pop();
            cout << "op1 " << op1 << " ,op2 " << op2 << endl;
            if (*i == '+')
                s.push(op1 + op2);
            else if (*i == '-')
                s.push(op1 - op2);
            else if (*i == '*')
                s.push(op1 * op2);
            else if (*i == '/')
                s.push(op1 / op2);
        }
        else
            s.push(*i - '0');
    }
    return s.top();
}

/* convert an infix sequence to post fix notation*/
string infixToPostfix(const string &expr)
{
    stack<char> s;
    string ret;
    for (auto &i : expr)
    {
        if (i == '(') //if its an opening paranthesis add to the stack
        {
            s.push(i);
        }
        //if its a closing paranthesis add append all the elements in the stack and finally remove the opening paranthesis
        else if (i == ')')
        {
            while (s.top() != '(')
            {
                ret += s.top();
                s.pop();
            }
            s.pop();
        }

        else if (i == '+' || i == '-' || i == '*' || i == '/')
        {
            // while the stack is not empty and the opcode inside of the stack is of higher precident and its not an opening paranthesis add them to the string
            while (!s.empty() && !isHigherPrecid(i, s.top()) && s.top() != '(')
            {
                ret += s.top();
                s.pop();
            }
            //now push the lower precident opcode
            s.push(i);
        }

        else
        {
            ret += i; //operands will be added to the string
        }
    }
    while (!s.empty()) //lastly add the remaining values in the stack
    {
        ret += s.top();
        s.pop();
    }
    return ret;
}

/* return true if the second opcode is of higher precident*/ 
bool isHigherPrecid(char first, char second)
{
    if (first == '/')
    {
        if (second == '/')
            return false;
        else
            return true;
    }
    else if (first == '*')
    {
        if (second == first || second == '/')
            return false;
        else
            return true;
    }
    else if (first == '+')
    {
        if (first == second || first == '/' || first == '*')
            return false;
        else
            return true;
    }
    else if (first == '-')
        return false;
    return true;
}