#include <climits>
#include <algorithm>
#include <iostream>

using namespace std;


void selectionSort(int *A, int size)
{
    //iteraate size-1 times
    for (int i = 0; i < size - 1; i++)
    {
        int minIndex = i;
        //make minIndex as i and iterate from i+1 to size,
        //compare and update the minIndex 
        for (int j = i + 1; j < size; j++)
        {
            if (A[j] < A[minIndex])
                minIndex = j;
        }
        //swap the minimum value with the ith location
        //[sorted, unsorted]
        std::swap(A[i], A[minIndex]);
    }
}


void bubbleSort(int *A, int size)
{
    //iteraate size-1 times
    for (int i = 0; i < size - 1; i++)
    {
        bool swapped = false;
        //iterate from start to size-i [unsorted, sorted]
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (A[j] > A[j + 1])
            {
                //bubble up the largest element to the end
                std::swap(A[j], A[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) //if no swaps detected array is sorted
            break;
    }
}


void insertionSort(int *A, int size)
{
    //iterate from 1st elem to end
    for (int i = 1; i < size; i++)
    {
        int hole = i;
        int temp = A[hole]; //temp contain the hole value
        //while previous values before hole is larger than temp
        while (A[hole - 1] > temp && hole > 0)
        {
            //shift the values until no more values are larger than temp
            A[hole] = A[hole - 1];
            --hole;
        }
        //replace the temp to new hole
        A[hole] = temp;
    }
    //[sorted, unsorted]
}


void merge(int *O, int *A, int *B, int na, int nb)
{
    //go through the both lists and append the smallest value one at a time
    int i = 0, j = 0, k = 0;
    while (i < na && j < nb)
    {
        if (A[i] < B[j])
            O[k++] = A[i++];
        else
            O[k++] = B[j++];
    }
    while (i < na)
        O[k++] = A[i++];

    while (j < nb)
        O[k++] = B[j++];
}

void mergeSort(int *A, int size)
{
    if (size < 2)
        return;
    int mid = size / 2;
    //create left and right arrays
    int R[mid];
    int L[size - mid];
    for (int i = 0; i < mid; i++)
        R[i] = A[i];
    for (int i = 0; i < size - mid; i++)
        L[i] = A[mid + i];

    mergeSort(R, mid); //will return the sorted right array
    mergeSort(L, size - mid); //will return the sorted left array
    //merge two sorted arrays into output array
    merge(A, R, L, mid, size - mid);
}

int partition(int *A, int start, int end)
{
    int pivot = A[end-1]; //pivot is chosen to be the last element
    int pIndex = start;
    for (int i=start; i< end-1; i++)
    {
        if (A[i] <= pivot) 
        //shift values until pivet become smaller
            swap(A[i], A[pIndex++]);
    }
    //pIndex will point to the value which is immediate to the largest value which is smaller than pivot. once index value is swapped with pivot, array requirement is met
    swap(A[pIndex], A[end-1]); //swap take references
    //[smaller, pivot, larger]
    return pIndex;
}


void qSort(int *A, int start, int end)
{
    if (start < end)
    {
        int pivot = partition(A, start, end);
        //keep the pivot value and sort the right and left sub arrays 
        qSort(A, start, pivot);
        qSort(A, pivot + 1, end);
    }
}

void quickSort(int *A, int size)
{
    qSort(A, 0, size);
}


int main()
{
    int n = 8;
    int A[n]{7,2,1,6,8,5,3,4};
    for (int i = 0; i < n; i++)
        std::cout << A[i] << " ";
    std::cout << std::endl;
    // selectionSort(A, n);
    // bubbleSort(A, n);
    // insertionSort(A, n);
    // mergeSort(A, n);
    quickSort(A, n);
    for (int i = 0; i < n; i++)
        std::cout << A[i] << " ";
    std::cout << std::endl;

    // int a[50]{0,1,2};
    // std::fill_n(a+3, 50, 5);
    // for (int i=0; i<50; i++) std::cout << a[i] << " ";
    // std::cout << std::endl;
    // int b[50]{};
    // for (int i=0; i<50; i++) std::cout << b[i] << " ";
    // std::cout << std::endl;
    // int c[50]{1};
    // for (int i=0; i<50; i++) std::cout << c[i] << " ";
}