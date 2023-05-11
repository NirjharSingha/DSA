#include <iostream>
#include <vector>

using namespace std;

class disjointSet
{
private:
    int *parent;
    int *rank;

public:
    disjointSet()
    {
        parent = new int[1000];
        rank = new int[1000];

        for (int i = 0; i < 1000; i++)
        {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }

        return parent[x];
    }

    void unionSets(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY)
        {
            return;
        }

        if (rank[rootX] < rank[rootY])
        {
            parent[rootX] = rootY;
        }
        else if (rank[rootX] > rank[rootY])
        {
            parent[rootY] = rootX;
        }
        else
        {
            parent[rootX] = rootY;
            rank[rootY]++;
        }
    }
};

int main()
{
    disjointSet ds;
    ds.unionSets(0, 1);
    ds.unionSets(2, 3);
    ds.unionSets(4, 5);
    ds.unionSets(6, 7);
    ds.unionSets(0, 2);
    ds.unionSets(4, 6);
    ds.unionSets(0, 4);

    for (int i = 0; i < 8; i++)
    {
        cout << "parent of " << i << ": " << ds.find(i) << endl;
    }

    return 0;
}
