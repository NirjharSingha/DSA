#include <bits/stdc++.h>
#include <cstring>

using namespace std;

class CircularArrQueue
{
public:
    int frontIdx;
    int lastIdx;
    int capacity;
    int size;
    int arr[1000];

    CircularArrQueue()
    {
        frontIdx = 0;
        lastIdx = 0;
        capacity = 1000;
        size = 0;
    }

    void pushRear(int newNode)
    {
        if (size == capacity)
        {
            cout << "Cannot push more data" << endl;
        }
        else
        {
            arr[lastIdx] = newNode;
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

    void pushFront(int newNode)
    {
        if (size == capacity)
        {
            cout << "Cannot push more data" << endl;
        }
        else
        {
            frontIdx = (frontIdx - 1 + capacity) % capacity;
            arr[frontIdx] = newNode;
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

class BST
{

private:
    int *tree;
    int max_size;

    int inOrderSuccessor(int index)
    {
        while (tree[2 * index + 1] != 0)
        {
            index = 2 * index + 1;
        }
        return index;
    }
    int inOrderPredecessor(int index)
    {
        while (tree[2 * index + 2] != 0)
        {
            index = 2 * index + 2;
        }
        return index;
    }

public:
    BST(int size)
    {
        tree = new int[size];
        memset(tree, 0, sizeof(int) * size);
        max_size = size;
    }

    ~BST()
    {
        delete[] tree;
    }

    void insert(int key)
    {
        if (tree[0] == 0)
        {
            tree[0] = key;
        }
        else
        {
            int index = 0;
            while (index < max_size)
            {
                if (tree[index] == 0)
                {
                    tree[index] = key;
                    break;
                }
                else if (key < tree[index])
                {
                    index = 2 * index + 1;
                }
                else
                {
                    index = 2 * index + 2;
                }
            }
        }
    }

    void deleteNode(int root, int key)
    {
        if (tree[root] == 0)
        {
            return;
        }
        if (tree[root] == key)
        {
            int left = 2 * root + 1;
            int right = 2 * root + 2;
            // no child
            if (tree[left] == 0 and tree[right] == 0)
            {
                tree[root] = 0;
                return;
            }
            // only left child
            else if (tree[left] != 0 and tree[right] == 0)
            {
                int inOrderPre = inOrderPredecessor(left);
                tree[root] = tree[inOrderPre];
                deleteNode(left, tree[inOrderPre]);
                return;
            }
            else
            {
                int inOrderSuc = inOrderSuccessor(right);
                tree[root] = tree[inOrderSuc];
                deleteNode(right, tree[inOrderSuc]);
                return;
            }
        }
        else if (tree[root] > key)
        {
            deleteNode(2 * root + 1, key);
        }
        else
        {
            deleteNode(2 * root + 2, key);
        }
    }

    void delNode(int key)
    {
        deleteNode(0, key);
    }

    bool search(int key)
    {
        int index = 0;

        while (index < max_size and tree[index] != 0)
        {
            if (key == tree[index])
            {
                return true;
            }
            else if (key < tree[index])
            {
                index = 2 * index + 1;
            }
            else
            {
                index = 2 * index + 2;
            }
        }
        return false;
    }

    void preorder(int index)
    {
        if (index < max_size and tree[index] != 0)
        {
            cout << tree[index] << " ";
            preorder(2 * index + 1);
            preorder(2 * index + 2);
        }
    }

    void inorder(int index)
    {
        if (index < max_size and tree[index] != 0)
        {
            inorder(2 * index + 1);
            cout << tree[index] << " ";
            inorder(2 * index + 2);
        }
    }

    void postorder(int index)
    {
        if (index < max_size and tree[index] != 0)
        {
            postorder(2 * index + 1);
            postorder(2 * index + 2);
            cout << tree[index] << " ";
        }
    }

    void help(int array[], int index, int &ct)
    {
        if (index < max_size and tree[index] != 0)
        {
            array[ct++] = tree[index];
            help(array, 2 * index + 1, ct);
            help(array, 2 * index + 2, ct);
        }
    }

    void leftSkewed()
    {
        int array[1000];
        int sz = 0;
        help(array, 0, sz);
        for (int i = 1; i < sz; i++)
        {
            if (array[i] > array[i - 1])
            {
                cout << "Not left skewed \n";
                return;
            }
        }
        cout << "left skewed \n";
    }

    void rightSkewed()
    {
        int array[1000];
        int sz = 0;
        help(array, 0, sz);
        for (int i = 1; i < sz; i++)
        {
            if (array[i] < array[i - 1])
            {
                cout << "Not right skewed \n";
                return;
            }
        }
        cout << "right skewed \n";
    }

    bool full(int &root)
    {
        if (tree[root] == 0)
        {
            return true;
        }
        if (tree[2 * root + 1] == 0 and tree[2 * root + 2] == 0)
        {
            return true;
        }
        if (tree[2 * root + 1] != 0 and tree[2 * root + 2] != 0)
        {
            int left = 2 * root + 1;
            int right = 2 * root + 2;
            return (full(left) and full(right));
        }
        cout << tree[root] << endl;
        return false;
    }

    bool isFull()
    {
        int root = 0;
        if (full(root))
        {
            cout << "Full" << endl;
            return true;
        }
        cout << "Not Full" << endl;
        return false;
    }

    pair<bool, int> isBalancedFast(int root)
    {
        pair<bool, int> p, left, right;
        if (tree[root] == 0)
        {
            p = make_pair(true, 0);
            return p;
        }
        left = isBalancedFast(2 * root + 1);
        right = isBalancedFast(2 * root + 2);
        bool leftAns = left.first;
        bool rightAns = right.first;
        bool dif = abs(left.second - right.second) <= 1;
        if (leftAns && rightAns && dif)
        {
            p.first = true;
        }
        else
        {
            p.first = false;
        }
        p.second = max(left.second, right.second) + 1;
        return p;
    }

    bool isBalanced()
    {
        if (isBalancedFast(0).first == true)
            cout << "Balanced" << endl;
        else
            cout << "Not Balanced" << endl;
        return isBalancedFast(0).first;
    }

    bool isPerfect(int root)
    {
        int c = 0;
        int l = 0;
        CircularArrQueue *q = new CircularArrQueue();
        q->pushRear(root);
        while (q->length() > 0)
        {
            int s = q->length();
            for (int i = 0; i < s; i++)
            {
                int n = q->front();
                q->popFront();
                c++;
                if (tree[2 * n + 1])
                    q->pushRear(2 * n + 1);
                if (tree[2 * n + 2])
                    q->pushRear(2 * n + 2);
            }
            l++;
        }
        if (pow(2, l) - 1 != c)
        {
            cout << "Not Perfect" << endl;
            return false;
        }
        cout << "Perfect" << endl;
        return true;
    }

    bool isComplete(int root)
    {
        if (tree[root] == 0)
        {
            cout << "Complete" << endl;
            return true;
        }

        CircularArrQueue *q = new CircularArrQueue();
        q->pushRear(root);

        bool flag = false;
        while (q->length() > 0)
        {
            int temp = q->front();
            q->popFront();
            if (tree[2 * temp + 1])
            {
                if (flag)
                {
                    cout << "Not Complete" << endl;
                    return false;
                }
                q->pushRear(2 * temp + 1);
            }
            else
            {
                flag = true;
            }
            if (tree[2 * temp + 2])
            {
                if (flag)
                {
                    cout << "Not Complete" << endl;
                    return false;
                }
                q->pushRear(2 * temp + 2);
            }
            else
            {
                flag = true;
            }
        }
        cout << "Complete" << endl;
        return true;
    }
};

int main()
{
    BST *tree = new BST(1000);
    // insert(root, 2, "first");
    // insert(root, 4, "first");
    // insert(root, 5, "first");

    tree->insert(11);
    tree->insert(4);
    tree->insert(2);
    tree->insert(1);
    tree->insert(3);
    tree->insert(5);
    tree->insert(8);
    tree->insert(7);
    // tree->insert(5);
    tree->insert(15);
    tree->insert(13);
    tree->insert(18);
    tree->insert(12);
    tree->insert(14);
    tree->insert(17);
    tree->insert(20);
    tree->delNode(4);
    tree->insert(6);
    tree->delNode(20);
    tree->delNode(17);
    tree->delNode(18);
    // tree->delNode(2);
    // tree->dele(4);
    // tree->insert(6);
    // tree->insert(1);
    // tree->insert(4);
    // tree->insert(5);
    // tree->insert(7);
    // tree->insert(8);
    // tree->insert(9);

    cout << "inorder" << endl;
    tree->inorder(0);
    cout << endl;
    cout << "preorder" << endl;
    tree->preorder(0);
    cout << endl;
    cout << "postorder" << endl;
    tree->postorder(0);
    cout << endl;
    // tree->leftSkewed();
    // tree->rightSkewed();
    cout << tree->search(6) << endl;
    cout << tree->search(4) << endl;
    cout << tree->isPerfect(0) << endl;
    cout << tree->isBalanced() << endl;
    cout << tree->isComplete(0) << endl;
    cout << tree->isFull() << endl;
    cout << tree->search(14) << endl;

    return 0;
}