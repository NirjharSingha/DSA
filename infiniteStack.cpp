#include <bits/stdc++.h>
using namespace std;

class InfiniteStack
{
public:
    int *arr;
    int *sz;
    int size;
    int totalCapacity;
    int capacityOfAStack;
    int numOfStack;

    InfiniteStack(int capacity)
    {
        cout << "null  ";
        arr = (int *)malloc(10 * capacity * sizeof(int));
        sz = (int *)malloc(200005 * sizeof(int));
        for (int i = 0; i < 200005; i++)
        {
            sz[i] = 0;
        }
        totalCapacity = 10 * capacity;
        capacityOfAStack = capacity;
        numOfStack = 0;
        size = 0;
    }

    void push(int val)
    {
        cout << "null  ";
        for (int i = 0; i <= numOfStack; i++)
        {
            if (sz[i] < capacityOfAStack)
            {
                int idx = i * capacityOfAStack + sz[i];
                arr[idx] = val;
                sz[i]++;
                if (sz[i] == capacityOfAStack)
                    numOfStack++;
                return;
            }
        }
        if (capacityOfAStack * (numOfStack - 1) == totalCapacity)
        {
            totalCapacity *= 2;
            arr = (int *)realloc(arr, totalCapacity * sizeof(int));
        }
        arr[size++] = val;
        if (sz[numOfStack] == capacityOfAStack)
        {
            numOfStack++;
        }
        sz[numOfStack]++;
    }

    int pop()
    {
        for (int i = numOfStack; i >= 0; i--)
        {
            if (sz[i] > 0)
            {
                int idx = i * capacityOfAStack + sz[i] - 1;
                int ans = arr[idx];
                sz[i]--;
                if (sz[i] == 0)
                    numOfStack--;
                return ans;
            }
        }
        return -1;
    }

    int popAtStack(int index)
    {
        if (index > numOfStack || sz[index] == 0)
            return -1;
        sz[index]--;
        int idx = (index)*capacityOfAStack + sz[index];
        return arr[idx];
    }
};

int main()
{
    InfiniteStack *st = new InfiniteStack(2);
    st->push(1);
    st->push(2);
    st->push(3);
    st->push(4);
    st->push(5);
    cout << st->popAtStack(0) << "  ";
    st->push(20);
    st->push(21);
    cout << st->popAtStack(0) << "  ";
    cout << st->popAtStack(2) << "  ";
    cout << st->pop() << "  ";
    cout << st->pop() << "  ";
    cout << st->pop() << "  ";
    cout << st->pop() << "  ";
    cout << st->pop() << "  ";
    cout << endl;
    return 0;
}
