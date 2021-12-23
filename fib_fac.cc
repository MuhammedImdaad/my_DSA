#include <iostream>
#include <vector>

using namespace std;

int fibRec(int n)
{
    if (n == 1 || n == 2)
        return 1;
    return fibRec(n - 1) + fibRec(n - 2);
}

int fibMem(int n, vector<int> &mem)
{
    if (mem[n] != 0)
        return mem[n];
    int result;
    if (n == 1 || n == 2)
        result = 1;
    else
        result = fibMem(n - 1, mem) + fibMem(n - 2, mem);
    mem[n] = result;
    return result;
}

int fibRecMem(int n)
{
    vector<int> f(n + 1, 0);
    return fibMem(n, f);
}

int fibDyn(int n)
{
    if (n == 1 || n == 2)
        return 1;
    vector<int> arr(n + 1, 0);
    arr[1] = arr[2] = 1;
    for (int i = 3; i < n + 1; i++)
    {
        arr[i] = arr[i - 1] + arr[i - 2];
    }
    return arr[n];
}

int fibDyn2(int n)
{
    if (n == 1 || n == 2)
        return 1;
    int n_1 = 1, n_2 = 1, result;

    for (int i = 3; i < n + 1; i++)
    {
        result = n_1 + n_2;
        n_2 = n_1;
        n_1 = result;
    }
    return result;
}

int factRec(int n)
{
    if (n < 2)
        return 1;
    return n * factRec(n - 1);
}

int fact(int n)
{
    if (n < 2)
        return 1;
    else
    {
        int result = 1;
        for (int i = 2; i < n + 1; i++)
        {
            result *= i;
        }
        return result;
    }
}

int main()
{
    cout << "40th fib - Recursion : " << fibRec(40) << endl;
    cout << "48th fib - Recursion with Memoization : " << fibRecMem(48) << endl;
    cout << "48th fib - Dynamic Programming : " << fibDyn(48) << endl;
    cout << "48th fib - Iteration : " << fibDyn2(48) << endl;
    cout << "16th fac - Recursion : " << factRec(16) << endl;
    cout << "16th fac - Iteration : " << fact(16) << endl;
}