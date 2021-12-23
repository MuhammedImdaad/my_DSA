#include <iostream>
#include <vector>

int stone(int y, std::vector<int> &s)
{
    for (auto &i : s)
    {
        if (y!=i && y%i==0)
            return 1 + (y/i)*stone(i, s);  
    }
    return 0;
}


int main()
{
    int y=12;
    std::vector<int>s{4,3,2};
    int moves = stone(y, s);
    std::cout << moves;
}