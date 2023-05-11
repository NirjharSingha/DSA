#include <bits/stdc++.h>
using namespace std;

int graph[1000][1000];
int Size[1000];
int ans[1000];
bool vis[1000];

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

void dfs(int &node, int &ansSize)
{
    vis[node] = true;
    ans[ansSize++] = node;
    for (int i = 0; i < Size[node]; i++)
    {
        if (!vis[graph[node][i]])
        {
            dfs(graph[node][i], ansSize);
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
            dfs(i, ansSize);
        }
    }

    cout << "The DFS traversal is : " << endl;
    for (int i = 0; i < ansSize; i++)
    {
        cout << ans[i] << " ";
    }
    cout << endl;

    return 0;
}