#include <bits/stdc++.h>
using namespace std;

class BinaryHeap
{
public:
    int *arr;
    int n;

    BinaryHeap()
    {
        arr = (int *)malloc(1000 * sizeof(int));
        n = 0;
    }

    BinaryHeap(int *arr, int size)
    {
        // arr = (int *)realloc(arr, 1000 * sizeof(int));
        this->arr = arr;
        this->n = size;
        buildHeap(arr, size - 1);
    }

    void heapify(int i)
    {
        if (i >= n)
            return;
        int largest;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < n && right < n)
        {
            largest = (arr[left] > arr[right] ? left : right);
        }
        else if (left < n)
        {
            largest = left;
        }
        else
        {
            return;
        }
        if (arr[largest] > arr[i])
        {
            swap(arr[i], arr[largest]);
            heapify(largest);
        }
    }
    void buildHeap(int *arr, int n)
    {
        for (int i = n / 2 - 1; i >= 0; i--)
        {
            heapify(i);
        }
    }
    void insert(int element)
    {
        arr[n] = element;
        int i = n;
        int parent = (n - 1) / 2;
        n++;
        while (i >= 0)
        {
            if (arr[i] > arr[parent])
            {
                swap(arr[i], arr[parent]);
                i = parent;
                parent = (i - 1) / 2;
            }
            else
            {
                return;
            }
        }
    }
    int del()
    {
        int maxi = arr[0];
        arr[0] = arr[n - 1];
        n--;
        heapify(0);
        return maxi;
    }
};

int main()
{
    int *arr = (int *)malloc(1000 * sizeof(int));

    arr[0] = 5;
    arr[1] = 2;
    arr[2] = 12;
    arr[3] = 1;
    arr[4] = 3;
    arr[5] = 9;
    arr[6] = -3;
    arr[7] = 7;
    arr[8] = 17;
    arr[9] = 11;
    arr[10] = 23;
    arr[11] = -8;
    arr[12] = -3;

    BinaryHeap *heap = new BinaryHeap(arr, 13);

    heap->insert(-5);
    heap->insert(13);
    heap->insert(-1);
    heap->insert(17);
    heap->insert(-7);

    int size = heap->n;

    for (int i = 0; i < size; i++)
    {
        cout << heap->del() << endl;
    }

    return 0;
}