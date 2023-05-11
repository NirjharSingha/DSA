#include <bits/stdc++.h>
using namespace std;

class CircularArrQueue
{
public:
    int frontIdx;
    int lastIdx;
    int capacity;
    int size;
    int *arr;

    CircularArrQueue()
    {
        frontIdx = 0;
        lastIdx = 0;
        capacity = 1000;
        arr = (int *)malloc(capacity * sizeof(int));
        size = 0;
    }

    void pushRear(int data)
    {
        if (size == capacity)
        {
            cout << "Cannot push more data" << endl;
        }
        else
        {
            arr[lastIdx] = data;
            lastIdx = (lastIdx + 1) % capacity;
        }
        size++;
    }

    int popFront()
    {
        if (size > 0)
        {
            int temp = arr[frontIdx];
            frontIdx = (frontIdx + 1) % capacity;
            size--;
            return temp;
        }
        cout << "Queue is empty" << endl;
        return INT_MAX;
    }

    void pushFront(int data)
    {
        if (size == capacity)
        {
            cout << "Cannot push more data" << endl;
        }
        else
        {
            frontIdx = (frontIdx - 1 + capacity) % capacity;
            arr[frontIdx] = data;
        }
        size++;
    }

    int popRear()
    {
        if (size > 0)
        {
            lastIdx = (lastIdx - 1 + capacity) % capacity;
            int temp = arr[lastIdx];
            size--;
            return temp;
        }
        cout << "Queue is empty" << endl;
        return INT_MAX;
    }

    int front()
    {
        if (size > 0)
        {
            return arr[frontIdx];
        }
        return INT_MAX;
    }

    int last()
    {
        if (size > 0)
        {
            return arr[lastIdx - 1];
        }
        return INT_MAX;
    }

    int length()
    {
        return size;
    }
};

int isPresent(vector<int> &v, int x)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] == x)
            return i;
    }
    return -1;
}

void solve()
{
    int n;
    cin >> n;
    int x;
    cin >> x;
    vector<vector<int>> temp(n);
    for (int i = 0; i < x; i++)
    {
        int a, b;
        cin >> a >> b;
        temp[a].push_back(b);
    }
    CircularArrQueue *q = new CircularArrQueue();
    for (int i = 0; i < n; i++)
    {
        q->pushRear(i);
    }
    vector<int> ans;
    while (q->size > 0)
    {
        int front = q->front();
        if (temp[front].size() == 0)
        {
            ans.push_back(front);
            for (int i = 0; i < n; i++)
            {
                if (isPresent(temp[i], front) != -1)
                {
                    int idx = isPresent(temp[i], front);
                    temp[i].erase(temp[i].begin() + idx * sizeof(int));
                }
            }
            q->popFront();
        }
        else
        {
            q->popFront();
            q->pushRear(front);
        }
    }
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }
    cout << endl;
}

int main()
{
    solve();
    return 0;
}