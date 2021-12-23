#include <climits>
#include <algorithm>
#include <iostream>

using namespace std;

void selectionSort(int *A, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < size; j++)
        {
            if (A[j] < A[minIndex])
                minIndex = j;
        }
        std::swap(A[i], A[minIndex]);
    }
}

void bubbleSort(int *A, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        bool swapped = false;
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (A[j] > A[j + 1])
            {
                std::swap(A[j], A[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

void insertionSort(int *A, int size)
{
    for (int i = 1; i < size; i++)
    {
        int hole = i;
        int temp = A[hole];
        while (A[hole - 1] > temp && hole > 0)
        {
            A[hole] = A[hole - 1];
            --hole;
        }
        A[hole] = temp;
    }
}

void merge(int *O, int *A, int *B, int na, int nb)
{
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
    int R[mid];
    int L[size - mid];
    for (int i = 0; i < mid; i++)
        R[i] = A[i];
    for (int i = 0; i < size - mid; i++)
        L[i] = A[mid + i];
    mergeSort(R, mid);
    mergeSort(L, size - mid);
    merge(A, R, L, mid, size - mid);
}

int partition(int *A, int start, int end)
{
    int pivot = A[end-1];
    int pIndex = start;
    for (int i=start; i< end-1; i++)
    {
        if (A[i] <= pivot)
            swap(A[i], A[pIndex++]);
    }
    swap(A[pIndex], A[end-1]);
    return pIndex;
}

void qSort(int *A, int start, int end)
{
    if (start < end)
    {
        int pivot = partition(A, start, end);
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

}