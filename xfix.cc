#include <iostream>
#include <stack>

using namespace std;

int evaluateInfix(const string &);
int evaluatePostfix(const string &);
string infixToPostfix(const string &);
bool isHigherPrecid(char first, char second);

int main()
{
    // cout << evaluatePostfix("23*54*+9-") << endl;
    // cout << evaluateInfix("-+*23*549") << endl;
    cout << infixToPostfix("A+B*C-D*E") << endl;
    cout << infixToPostfix("((A+B)*C-D)*E") << endl;
    cout << infixToPostfix("A*(B+C)") << endl;
}

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
            s.push(i - '0');
    }
    return s.top();
}

int evaluateInfix(const string &expr)
{
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

string infixToPostfix(const string &expr)
{
    stack<char> s;
    string ret;
    for (auto &i : expr)
    {
        if (i == '(')
        {
            s.push(i);
        }
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
            while (!s.empty() && !isHigherPrecid(i, s.top()) && s.top() != '(')
            {
                ret += s.top();
                s.pop();
            }
            s.push(i);
        }
        else
        {
            ret += i;
        }
    }
    while (!s.empty())
    {
        ret += s.top();
        s.pop();
    }
    return ret;
}

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