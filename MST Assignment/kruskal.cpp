#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct DisjointSet
{
    vector<int> parent, rank;

    DisjointSet(int n)
    {
        parent.resize(n);
        rank.resize(n, 0);

        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }

    int rootFind(int x)
    {
        if (parent[x] != x)
            parent[x] = rootFind(parent[x]);
        return parent[x];
    }

    void unionOperaion(int uParent, int vParent)
    {
        if (rank[uParent] > rank[vParent])
            parent[vParent] = uParent;
        else if (rank[uParent] < rank[vParent])
            parent[uParent] = vParent;
        else
        {
            parent[vParent] = uParent;
            rank[uParent]++;
        }
    }
};

bool compare(vector<int> v1, vector<int> v2)
{
    return v1[2] < v2[2];
}

int kruskal(vector<vector<int>> &graph, int n, vector<pair<int, int>> &print)
{
    sort(graph.begin(), graph.end(), compare);

    DisjointSet ds(n);
    int tWeight = 0;

    for (const vector<int> &edge : graph)
    {
        int u = edge[0];
        int v = edge[1];

        int uParent = ds.rootFind(u);
        int vParent = ds.rootFind(v);
        if (uParent != vParent)
        {
            print.push_back(make_pair(u, v));
            // cout << u << " " << v << endl;
            tWeight += edge[2];
            ds.unionOperaion(uParent, vParent);
        }
    }
    return tWeight;
}

int main()
{
    freopen("./Testcases/tc03/in.txt", "r", stdin);
    freopen("./testcases/tc03/kruskal.txt", "w", stdout);

    int vertex = 0, edge = 0;
    cin >> vertex >> edge;
    if (vertex == 0 || edge == 0)
        return 0;

    vector<vector<int>> graph(edge);

    for (int i = 0; i < edge; i++)
    {
        int u = 0, v = 0, d = 0;
        cin >> u >> v >> d;
        vector<int> temp{u, v, d};
        graph[i] = (temp);
    }
    vector<pair<int, int>> print;
    int tWeight = kruskal(graph, edge, print);

    cout << "Kruskal's Algorithm: " << endl;
    cout << "Total Weight = " << tWeight << endl;

    for (int i = 0; i < print.size(); i++)
    {
        cout << print[i].first << " " << print[i].second << endl;
    }

    fclose(stdin);
    fclose(stdout);
}
