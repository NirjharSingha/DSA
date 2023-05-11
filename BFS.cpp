#include <bits/stdc++.h>
using namespace std;

int graph[1000][1000];
int Size[1000];
int ans[1000];
bool vis[1000];

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

class Edge
{
public:
    int u;
    int v;
};

void makeEdgecencyList(Edge edges[], int noOfEdges)
{
    for (int j = 0; j < noOfEdges; j++)
    {
        int u = edges[j].u;
        int v = edges[j].v;
        graph[u][Size[u]++] = v;
        graph[v][Size[v]++] = u;
    }
}

void bfs(int &node, int &ansSize)
{
    CircularArrQueue q;
    q.pushRear(node);
    vis[node] = true;
    while (q.size > 0)
    {
        int frontNode = q.front();
        q.popFront();
        ans[ansSize++] = frontNode;
        for (int i = 0; i < Size[frontNode]; i++)
        {
            if (!vis[graph[frontNode][i]])
            {
                vis[graph[frontNode][i]] = true;
                q.pushRear(graph[frontNode][i]);
            }
        }
    }
}

int main()
{
    int noOfEdge;
    int vertex;
    cout << "Enter total number of vertex" << endl;
    cin >> vertex;
    cout << "Enter total number of edges" << endl;
    cin >> noOfEdge;
    cout << "Enter all the edges" << endl;
    Edge edges[noOfEdge];

    for (int i = 0; i < noOfEdge; i++)
    {
        Edge edge;
        cin >> edge.u >> edge.v;
        edges[i] = edge;
    }

    makeEdgecencyList(edges, noOfEdge);

    cout << "The adjecency list is : " << endl;
    for (int i = 0; i < vertex; i++)
    {
        for (int j = 0; j < Size[i]; j++)
        {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }

    int ansSize = 0;

    for (int i = 0; i < vertex; i++)
    {
        if (!vis[i])
        {
            bfs(i, ansSize);
        }
    }

    cout << "The BFS traversal is : " << endl;
    for (int i = 0; i < ansSize; i++)
    {
        cout << ans[i] << " ";
    }
    cout << endl;

    return 0;
}