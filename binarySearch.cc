#include <iostream>
#include <vector>

int binarySearch(std::vector<int> &arr, int x)
{
    int start = 0, end = arr.size()-1;
    while(start<=end)
    {
        int mid = start+(end-start)/2;
        if (arr.at(mid)==x) return mid;
        else if (arr.at(mid)<x) start=mid+1;
        else end = mid -1;
    }
    return -1;
}

int binarySearchR(std::vector<int> &arr, int x, int start, int end)
{
    if (start>end) return -1;
    int mid = start+(end-start)/2;
    if (arr.at(mid)==x) return mid;
    else if (arr.at(mid)<x) return binarySearchR(arr, x, mid+1, end);
    else return binarySearchR(arr, x, start, mid-1);

}

int main()
{
    std::vector<int> a = {1,3,4,6,8,26,34,36,88,99};
    std::cout << binarySearch(a, 88) << std::endl;
    std::cout << binarySearch(a, 87) << std::endl;
    std::cout << binarySearchR(a, 88, 0,9) << std::endl;
    std::cout << binarySearchR(a, 87,0,9) << std::endl;
}