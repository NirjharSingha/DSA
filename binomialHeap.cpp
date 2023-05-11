#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int data, degree;
    Node *sibling, *parent, *child;

    Node()
    {
        this->data = 0;
        this->degree = 0;
        this->sibling = this->parent = this->child = NULL;
    }

    Node(int data)
    {
        this->data = data;
        this->degree = 0;
        this->sibling = this->parent = this->child = NULL;
    }
};

class binomialHeap
{
public:
    Node *root;
    Node *min;

    binomialHeap()
    {
        this->root = NULL;
    }
    binomialHeap(Node *x)
    {
        this->root = x;
    }

    void mergeTreeUtil(Node *y, Node *z)
    {
        y->parent = z;
        y->sibling = z->child;
        z->child = y;
        z->degree = z->degree + 1;
    }

    Node *mergeRoots(binomialHeap *x, binomialHeap *y)
    {
        // merge two linked list sorted according to their degree
        Node *merged = new Node();
        Node *end = merged;

        Node *L1 = x->root;
        Node *L2 = y->root;
        if (L1 == NULL)
            return L2;
        if (L2 == NULL)
            return L1;
        while (L1 != NULL || L2 != NULL)
        {
            if (L1 == NULL)
            {
                end->sibling = L2;
                end = end->sibling;
                L2 = L2->sibling;
            }
            else if (L2 == NULL)
            {
                end->sibling = L1;
                end = end->sibling;
                L1 = L1->sibling;
            }
            else
            {
                if (L1->degree < L2->degree)
                {
                    end->sibling = L1;
                    end = end->sibling;
                    L1 = L1->sibling;
                }
                else
                {
                    end->sibling = L2;
                    end = end->sibling;
                    L2 = L2->sibling;
                }
            }
        }
        return (merged->sibling);
    }

    bool isEmpty()
    {
        if (this->root == NULL)
            return 1;
        else
            return 0;
    }

    void insert(Node *x)
    {
        this->merge(new binomialHeap(x));
    }

    void merge(binomialHeap *h2)
    {
        binomialHeap *tempHeap = new binomialHeap();
        tempHeap->root = mergeRoots(this, h2);

        if (tempHeap->root == NULL)
        {
            this->root = NULL;
            this->min = NULL;
            return;
        }

        Node *prev = NULL;
        Node *curr = tempHeap->root;
        Node *next = curr->sibling;
        // merging binomial trees of same degree
        while (next != NULL)
        {
            if (curr->degree != next->degree || (next->sibling != NULL && next->sibling->degree == curr->degree))
            {
                prev = curr;
                curr = next;
            }
            else if (curr->data <= next->data)
            {
                curr->sibling = next->sibling;
                mergeTreeUtil(next, curr);
            }
            else
            {
                if (prev == NULL)
                    tempHeap->root = next;
                else
                    prev->sibling = next;
                mergeTreeUtil(curr, next);
                curr = next;
            }
            next = curr->sibling;
        }
        this->root = tempHeap->root;
        this->min = tempHeap->root;
        Node *tmp = this->root;
        while (tmp != NULL)
        {
            if (tmp->data < this->min->data)
                this->min = tmp;
            tmp = tmp->sibling;
        }
    }

    Node *extractMin()
    {
        Node *minNode = this->min;
        Node *prev = NULL;
        Node *x = this->root;
        while (x != minNode)
        {
            prev = x;
            x = x->sibling;
        }
        if (prev == NULL)
            this->root = x->sibling;
        else
            prev->sibling = x->sibling;

        Node *revChd = NULL;
        Node *tmp = minNode->child;
        // reverse a linked list
        while (tmp != NULL)
        {
            Node *next = tmp->sibling;
            tmp->sibling = revChd;
            revChd = tmp;
            tmp = next;
        }

        binomialHeap *tempHeap = new binomialHeap();
        tempHeap->root = revChd;
        this->merge(tempHeap);

        return minNode;
    }

    void decreaseKey(Node *x, int newKey)
    {
        x->data = newKey;
        Node *y = x;
        Node *z = y->parent;

        while (z != NULL && y->data < z->data)
        {
            swap(y->data, z->data);

            y = z;
            z = y->parent;
        }
        if (y->data < this->min->data)
            this->min = y;
    }

    void Delete(Node *x)
    {
        decreaseKey(x, INT_MIN);
        extractMin();
    }
};

int main()
{
    binomialHeap *h2 = new binomialHeap();

    Node *x = new Node(11);
    Node *y = new Node(5);

    h2->insert(x);
    h2->insert(y);
    h2->insert(new Node(3));
    h2->insert(new Node(8));
    h2->insert(new Node(4));

    h2->decreaseKey(x, 2);

    while (!h2->isEmpty())
    {
        printf("%d ", h2->extractMin()->data);
    }
    printf("\n");
    return 0;
}