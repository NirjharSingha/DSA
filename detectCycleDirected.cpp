#include <bits/stdc++.h>
using namespace std;

int graph[1000][1000];
int Size[1000];
bool vis[1000];
bool dfsVis[1000];

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
    }
}

bool dfs(int &node)
{
    vis[node] = true;
    dfsVis[node] = true;
    for (int i = 0; i < Size[node]; i++)
    {
        if (!vis[graph[node][i]])
        {
            bool ans = dfs(graph[node][i]);
            if (ans)
            {
                return true;
            }
        }
        else if (dfsVis[graph[node][i]])
        {
            return true;
        }
    }
    dfsVis[node] = false;
    return false;
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

    for (int i = 0; i < vertex; i++)
    {
        if (!vis[i])
        {
            bool ans = dfs(i);
            if (ans)
            {
                cout << "cycle present" << endl;
                return 0;
            }
        }
    }
    cout << "cycle not present" << endl;
    return 0;
}