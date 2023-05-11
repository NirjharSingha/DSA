#include <bits/stdc++.h>
#include "linkedList.h"
using namespace std;

class LinkedListQueue
{
public:
    int size;
    Node *head;
    Node *tail;

    LinkedListQueue()
    {
        this->size = 0;
        this->head = NULL;
        this->tail = NULL;
    }

    void push(int data)
    {
        Node *newNode = new Node(data);
        if (!head)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = tail->next;
        }
        size++;
    }

    int pop()
    {
        if (head)
        {
            int data = head->data;
            head = head->next;
            size--;
            return data;
        }
        return INT_MAX;
    }

    int front()
    {
        if (head)
        {
            int data = head->data;
            return data;
        }
        return INT_MAX;
    }

    int length()
    {
        return size;
    }
};

class ArrQueue
{
public:
    int frontIdx;
    int lastIdx;
    int capacity;
    int size;
    int *arr;

    ArrQueue()
    {
        frontIdx = 0;
        lastIdx = -1;
        capacity = 1;
        arr = (int *)malloc(capacity * sizeof(int));
        size = 0;
    }

    void push(int data)
    {
        if (size == capacity)
        {
            int temp[size];
            int idx = 0;
            int i = frontIdx;
            while (1)
            {
                temp[idx++] = arr[i];
                i = (i + 1) % capacity;
                if (i == frontIdx)
                    break;
            }
            capacity *= 2;
            arr = (int *)malloc(capacity * sizeof(int));
            frontIdx = 0;
            lastIdx = size;
            for (int i = 0; i < size; i++)
            {
                arr[i] = temp[i];
            }
            arr[size] = data;
        }
        else
        {
            lastIdx = (lastIdx + 1) % capacity;
            arr[lastIdx] = data;
        }
        size++;
    }

    int pop()
    {
        if (size > 0)
        {
            int temp = arr[frontIdx];
            frontIdx = (frontIdx + 1) % capacity;
            return temp;
        }
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

    int length()
    {
        return size;
    }
};

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

    void solve(int x)
    {
        vector<int> temp, ans;
        int sum = 0;

        for (int i = 0, j = 0; j < size;)
        {
            sum += arr[j];
            temp.push_back(arr[j]);
            while (sum >= x)
            {
                int p = j - i + 1;
                if (p < temp.size())
                {
                    temp.clear();
                    for (int k = i; k <= j; k++)
                    {
                        temp.push_back(arr[k]);
                    }
                }
                if (temp.size() < ans.size() || ans.empty())
                    ans = temp;
                sum -= arr[i++];
            }
            j++;
        }
        for (int i = 0; i < ans.size(); i++)
        {
            cout << ans[i] << " ";
        }
        cout << endl;
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
    // vector<bool> v(n, true);
    int x;
    cin >> x;
    vector<vector<int>> temp(n);
    for (int i = 0; i < x; i++)
    {
        int a, b;
        cin >> a >> b;
        // v[a] = false;
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
                    // for (int j = idx + 1; j < temp[i].size(); j++)
                    // {
                    //     temp[i][j] = temp[i][j - 1];
                    // }
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
    // LinkedListQueue *que = new LinkedListQueue();
    // int n;
    // cin >> n;

    // cout << que->pop() << endl;

    // for (int i = 0; i < n; i++)
    // {
    //     int temp;
    //     cin >> temp;
    //     que->push(temp);
    // }

    // while (que->head)
    // {
    //     cout << que->front() << " ";
    //     cout << que->pop() << " ";
    // }

    // cout << endl;

    // CircularArrQueue *qu = new CircularArrQueue();
    // int m;
    // cin >> m;

    // cout << qu->popFront() << endl;
    // cout << qu->popRear() << endl;

    // for (int i = 0; i < m; i++)
    // {
    //     int temp;
    //     cin >> temp;
    //     qu->pushFront(temp);
    //     qu->pushRear(temp);
    // }

    // for (int i = 0; i < 2 * (m - 2); i++)
    // {
    //     cout << qu->front() << " ";
    //     cout << qu->last() << " ";
    //     cout << qu->popFront() << " ";
    //     cout << qu->popRear() << " ";
    // }

    // cout << endl;

    // qu->pushFront(10);
    // qu->pushRear(20);

    // cout << qu->popFront() << " ";
    // cout << qu->popRear() << " ";
    // cout << qu->popFront() << " ";
    // cout << qu->popRear() << " ";

    // cout << endl;
    // qu->pushRear(1);
    // qu->pushRear(2);
    // qu->pushRear(3);
    // qu->pushRear(4);
    // qu->pushRear(5);
    // qu->pushRear(6);

    // qu->solve(6);
    solve();

    return 0;
}
