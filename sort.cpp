#include <bits/stdc++.h>
using namespace std;

void countSort(int arr[], int n)
{
    int mx = -1;

    for (int i = 0; i < n; i++)
    {
        mx = max(mx, arr[i]);
    }

    int count[mx + 1];
    int output[n];

    for (int i = 0; i <= mx; i++)
    {
        count[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        count[arr[i]]++;
    }

    for (int i = 1; i <= mx; i++)
    {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--)
    {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    for (int i = 0; i < n; i++)
    {
        arr[i] = output[i];
    }
}

void countSort(int arr[], int n, int exp)
{
    int count[10];
    int output[n];

    for (int i = 0; i <= 9; i++)
    {
        count[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        count[(arr[i] / exp) % 10]++;
    }

    for (int i = 1; i <= 9; i++)
    {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--)
    {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++)
    {
        arr[i] = output[i];
    }
}

void radixSort(int arr[], int n)
{
    int mx = arr[0];

    for (int i = 1; i < n; i++)
    {
        mx = max(mx, arr[i]);
    }

    int exp = 1;

    while (mx / exp > 0)
    {
        countSort(arr, n, exp);
        exp *= 10;
    }
}

void bucketSort(double arr[], int noOfBuckets, int n)
{
    double max_ele = -100000;
    double min_ele = 100000;

    for (int i = 0; i < n; i++)
    {
        max_ele = max(arr[i], max_ele);
        min_ele = min(arr[i], min_ele);
    }

    double rnge = (max_ele - min_ele) / noOfBuckets;

    vector<vector<double>> temp;

    for (int i = 0; i < noOfBuckets; i++)
    {
        temp.push_back(vector<double>());
    }

    for (int i = 0; i < n; i++)
    {
        double diff = (arr[i] - min_ele) / rnge - int((arr[i] - min_ele) / rnge);

        if (diff == 0 && arr[i] != min_ele)
        {
            temp[int((arr[i] - min_ele) / rnge) - 1]
                .push_back(arr[i]);
        }
        else
        {
            temp[int((arr[i] - min_ele) / rnge)].push_back(
                arr[i]);
        }
    }

    for (int i = 0; i < temp.size(); i++)
    {
        if (!temp[i].empty())
        {
            sort(temp[i].begin(), temp[i].end());
        }
    }

    int k = 0;
    for (vector<double> &lst : temp)
    {
        if (!lst.empty())
        {
            for (double i : lst)
            {
                arr[k] = i;
                k++;
            }
        }
    }
}

void merge(int arr[], int l, int mid, int r)
{
    // Your code here
    int v[l + r + 1];
    int i = l, j = mid + 1, k = l;
    while (i <= mid && j <= r)
    {
        if (arr[i] <= arr[j])
        {
            v[k] = arr[i];
            i++;
        }
        else
        {
            v[k] = arr[j];
            j++;
        }
        k++;
    }
    while (i <= mid)
    {
        v[k] = arr[i];
        k++;
        i++;
    }
    while (j <= r)
    {
        v[k] = arr[j];
        k++;
        j++;
    }
    for (int i = l; i <= r; i++)
    {
        arr[i] = v[i];
    }
}

void mergeSort(int arr[], int l, int r)
{
    // code here
    if (l < r)
    {
        int mid = (l + r) / 2;
        mergeSort(arr, l, mid);
        mergeSort(arr, mid + 1, r);
        merge(arr, l, mid, r);
    }
}

int partition(int arr[], int low, int high)
{
    // Your code here
    int element = arr[high];
    int pivot = low;
    for (int i = low; i <= high - 1; i++)
    {
        if (arr[i] <= element)
        {
            swap(arr[pivot], arr[i]);
            pivot++;
        }
    }
    swap(arr[pivot], arr[high]);
    return pivot;
}

void quickSort(int arr[], int low, int high)
{
    // code here
    if (low < high)
    {
        int pivot = partition(arr, low, high);
        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}

void insertionSort(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int j = i - 1;
        int t = arr[i];
        while (j >= 0 && arr[j] > t)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = t;
    }
}

void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        bool flag = true;

        for (int j = 0; j < n - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                flag = false;
            }
        }

        if (flag)
            break;
    }
}

void selectionSort(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        int min_idx = i;

        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }
        swap(arr[i], arr[min_idx]);
    }
}

int main()
{
    int n;
    cin >> n;
    int arr[7][n];

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> arr[i][j];
        }
    }

    double arr1[n];

    for (int i = 0; i < n; i++)
    {
        cin >> arr1[i];
    }

    selectionSort(arr[0], n);
    bubbleSort(arr[1], n);
    insertionSort(arr[2], n);
    quickSort(arr[3], 0, n - 1);
    mergeSort(arr[4], 0, n - 1);
    countSort(arr[5], n);
    radixSort(arr[6], n);
    bucketSort(arr1, 3, n);

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < n; i++)
    {
        cout << arr1[i] << " ";
    }
    cout << endl;

    return 0;
}