#include <bits/stdc++.h>
#include "linkedList.h"
using namespace std;

class CustomStack
{
public:
    int size;
    SinglyLinkedList *list;

    CustomStack()
    {
        this->size = 0;
        this->list = new SinglyLinkedList();
    }

    void push(int data)
    {
        list->insertAtBeginning(data);
        size++;
    }

    int pop()
    {
        if (list->head)
        {
            int data = list->head->data;
            list->deleteFromBeginning();
            size--;
            return data;
        }
        return INT_MAX;
    }

    int top()
    {
        if (list->head)
        {
            int data = list->head->data;
            return data;
        }
        return INT_MAX;
    }

    int length()
    {
        return size;
    }
};

class ArrStack
{
public:
    int size;
    int capacity;
    int *arr;

    ArrStack()
    {
        size = 0;
        capacity = 2;
        arr = (int *)malloc(capacity * sizeof(int));
    }

    void push(int data)
    {
        if (size == capacity)
        {
            capacity *= 2;
            arr = (int *)realloc(arr, capacity * sizeof(int));
        }
        arr[size++] = data;
    }

    int pop()
    {
        if (size > 0)
        {
            return arr[--size];
        }
        return INT_MAX;
    }

    int top()
    {
        if (size > 0)
        {
            return arr[size - 1];
        }
        return INT_MAX;
    }

    int length()
    {
        return size;
    }
};

int main()
{
    CustomStack *st = new CustomStack();
    int n;
    cin >> n;
    cout << st->pop() << endl;

    for (int i = 0; i < n; i++)
    {
        int temp;
        cin >> temp;
        st->push(temp);
    }

    for (int i = 0; i < n; i++)
    {
        cout << st->top() << " ";
        cout << st->pop() << " ";
    }

    cout << endl;

    ArrStack *stk = new ArrStack();
    int m;
    cin >> m;

    cout << stk->pop() << endl;

    for (int i = 0; i < m; i++)
    {
        int temp;
        cin >> temp;
        stk->push(temp);
    }

    for (int i = 0; i < n; i++)
    {
        cout << stk->top() << " ";
        cout << stk->pop() << " ";
    }

    cout << endl;
    return 0;
}
