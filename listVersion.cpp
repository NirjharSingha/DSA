#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int roll;
    string name;
    Node *left;
    Node *right;

    Node()
    {
        this->left = NULL;
        this->right = NULL;
    }

    Node(int roll, string name)
    {
        this->roll = roll;
        this->name = name;
        this->left = NULL;
        this->right = NULL;
    }
};

class bst
{
public:
    Node *root;

    bst()
    {
        root = NULL;
    }
};

class CircularArrQueue
{
public:
    int frontIdx;
    int lastIdx;
    int capacity;
    int size;
    Node *arr[1000];

    CircularArrQueue()
    {
        frontIdx = 0;
        lastIdx = 0;
        capacity = 1000;
        size = 0;
    }

    void pushRear(Node *newNode)
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

    Node *popFront()
    {
        if (size > 0)
        {
            Node *temp = arr[frontIdx];
            frontIdx = (frontIdx + 1) % capacity;
            size--;
            return temp;
        }
        cout << "Queue is empty" << endl;
        return new Node();
    }

    void pushFront(Node *newNode)
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

    Node *popRear()
    {
        if (size > 0)
        {
            lastIdx = (lastIdx - 1 + capacity) % capacity;
            Node *temp = arr[lastIdx];
            size--;
            return temp;
        }
        cout << "Queue is empty" << endl;
        return new Node();
    }

    Node *front()
    {
        if (size > 0)
        {
            return arr[frontIdx];
        }
        return new Node();
    }

    Node *last()
    {
        if (size > 0)
        {
            return arr[lastIdx - 1];
        }
        return new Node();
    }

    int length()
    {
        return size;
    }
};

Node *insert(Node *&root, int roll, string name)
{
    Node *node = new Node(roll, name);
    if (root == NULL)
    {
        root = node;
        return root;
    }

    if (roll < root->roll)
        insert(root->left, roll, name);
    else
        insert(root->right, roll, name);

    return root;
}

Node *deleteNode(Node *root, int k)
{
    if (root == NULL)
        return root;

    if (root->roll > k)
    {
        root->left = deleteNode(root->left, k);
        return root;
    }
    else if (root->roll < k)
    {
        root->right = deleteNode(root->right, k);
        return root;
    }

    if (root->left == NULL)
    {
        Node *temp = root->right;
        delete root;
        return temp;
    }
    else if (root->right == NULL)
    {
        Node *temp = root->left;
        delete root;
        return temp;
    }

    else
    {
        Node *succParent = root;
        Node *succ = root->right;
        while (succ->left != NULL)
        {
            succParent = succ;
            succ = succ->left;
        }

        if (succParent != root)
            succParent->left = succ->right;
        else
            succParent->right = succ->right;

        root->roll = succ->roll;

        delete succ;
        return root;
    }
}

void searchNode(Node *root, int roll, bool &flag)
{
    if (root == NULL)
    {
        return;
    }
    if (root->roll == roll)
    {
        flag = true;
        return;
    }
    searchNode(root->left, roll, flag);
    searchNode(root->right, roll, flag);
}

void search(Node *root, int roll)
{
    bool flag = false;
    searchNode(root, roll, flag);
    if (flag)
    {
        cout << "Found" << endl;
    }
    else
    {
        cout << "Not Found" << endl;
    }
}

bool isLeftSkewed(Node *root)
{
    if (root == NULL)
    {
        cout << "Left Skewed" << endl;
        return true;
    }
    while (root)
    {
        if (root->right != NULL)
        {
            cout << "Not Left Skewed" << endl;
            return false;
        }
        root = root->left;
    }
    cout << "Left Skewed" << endl;
    return true;
}

bool isRightSkewed(Node *root)
{
    if (root == NULL)
    {
        cout << "Right Skewed" << endl;
        return true;
    }
    while (root)
    {
        if (root->left != NULL)
        {
            cout << "Not Right Skewed" << endl;
            return false;
        }
        root = root->right;
    }
    cout << "Right Skewed" << endl;
    return true;
}

void inOrderTraversal(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    inOrderTraversal(root->left);
    cout << root->roll << "  " << root->name << endl;
    inOrderTraversal(root->right);
}

void preOrderTraversal(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    cout << root->roll << "  " << root->name << endl;
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
}

void postOrderTraversal(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    postOrderTraversal(root->left);
    postOrderTraversal(root->right);
    cout << root->roll << "  " << root->name << endl;
}

pair<bool, int> isBalancedFast(Node *root)
{
    pair<bool, int> p, left, right;
    if (root == NULL)
    {
        p = make_pair(true, 0);
        return p;
    }
    left = isBalancedFast(root->left);
    right = isBalancedFast(root->right);
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

bool isBalanced(Node *root)
{
    if (isBalancedFast(root).first == true)
        cout << "Balanced" << endl;
    else
        cout << "Not Balanced" << endl;
    return isBalancedFast(root).first;
}

bool full(Node *&root)
{
    if (root == NULL)
    {
        return true;
    }
    if (root->left == NULL && root->right == NULL)
    {
        return true;
    }
    if (root->left != NULL && root->right != NULL)
        return (full(root->left) && full(root->right));

    return false;
}

bool isFull(Node *&root)
{
    if (full(root))
    {
        cout << "Full" << endl;
        return true;
    }
    cout << "Not Full" << endl;
    return false;
}

bool isPerfect(Node *root)
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
            Node *n = q->front();
            q->popFront();
            c++;
            if (n->left)
                q->pushRear(n->left);
            if (n->right)
                q->pushRear(n->right);
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

bool isComplete(Node *root)
{
    if (root == NULL)
    {
        cout << "Complete" << endl;
        return true;
    }

    CircularArrQueue *q = new CircularArrQueue();
    q->pushRear(root);

    bool flag = false;
    while (q->length() > 0)
    {
        Node *temp = q->front();
        q->popFront();
        if (temp->left)
        {
            if (flag)
            {
                cout << "Not Complete" << endl;
                return false;
            }
            q->pushRear(temp->left);
        }
        else
        {
            flag = true;
        }
        if (temp->right)
        {
            if (flag)
            {
                cout << "Not Complete" << endl;
                return false;
            }
            q->pushRear(temp->right);
        }
        else
        {
            flag = true;
        }
    }
    cout << "Complete" << endl;
    return true;
}

int main()
{
    bst *tree = new bst();
    Node *root = tree->root;
    Node *temp;
    // insert(root, 2, "first");
    // insert(root, 4, "first");
    // insert(root, 5, "first");
    // insert(root, 6, "first");

    insert(root, 4, "first");
    insert(root, 1, "first");
    insert(root, 7, "first");
    insert(root, 3, "first");
    insert(root, 2, "first");
    insert(root, 0, "first");
    // insert(root, 11, "first");
    // insert(root, 13, "first");
    insert(root, 8, "first");
    // insert(root, 1, "A");
    deleteNode(root, 2);
    insert(root, 6, "first");
    // insert(root, 8, "first");
    // deleteNode(root, 5);
    // insert(root, 2, "first");
    cout << "inorder" << endl;
    inOrderTraversal(root);
    cout << "preorder" << endl;
    preOrderTraversal(root);
    cout << "postorder" << endl;
    postOrderTraversal(root);
    cout << isLeftSkewed(root) << endl;
    cout << isRightSkewed(root) << endl;
    search(root, 6);

    cout << isPerfect(root) << endl;
    cout << isBalanced(root) << endl;
    cout << isComplete(root) << endl;
    cout << isFull(root) << endl;
    search(root, 14);

    return 0;
}