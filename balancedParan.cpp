#include <stack>
#include <iostream>

using namespace std;

bool is_balanced(string bracs)
{
    stack<char> s;
    for (int i = 0; i < bracs.size(); i++)
    {
        if (bracs[i] == '[' || bracs[i] == '(' || bracs[i] == '{')
        {
            s.push(bracs[i]);
        }
        else
        {
            if (s.empty())
                return false;
            if (bracs[i] == ')')
            {
                if (s.top() == '(')
                    s.pop();
                else
                    return false;
            }
            else if (bracs[i] == ']')
            {
                if (s.top() == '[')
                    s.pop();
                else
                    return false;
            }
            else if (bracs[i] == '}')
            {
                if (s.top() == '{')
                    s.pop();
                else
                    return false;
            }
        }
    }
    if (s.empty())
        return true;
    else
        return false;
}

int main()
{
    cout << is_balanced("[{()()}]") << endl;
    cout << is_balanced("[{())()}]") << endl;
    cout << is_balanced("[{()()}]]") << endl;

}