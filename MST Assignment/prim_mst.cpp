#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;
using PII = pair<int, int>;

int prim(int u, vector<vector<PII>> graph, vector<PII> &print)
{
    priority_queue<PII, vector<PII>, greater<PII>> PQ; // min heap pq
    vector<bool> visited(graph.size(), false);

    int tWeight = 0, count = 0;

    PQ.push(make_pair(0, u));
    while (!PQ.empty())
    {
        PII top_p = PQ.top();
        PQ.pop();

        u = top_p.second;

        if (visited[u])
            continue;

        visited[u] = true;

        int w = top_p.first;

        tWeight += w;

        print.push_back(make_pair(w, u));

        for (const PII &neighbor : graph[u])
        {
            int v = neighbor.second;
            if (!visited[v])
                PQ.push(neighbor);
        }
    }
    return tWeight;
}

int main()
{
    freopen("./Testcases/tc01/in.txt", "r", stdin);
    freopen("./testcases/tc01/prim.txt", "w", stdout);

    int vertex = 0, edge = 0;
    cin >> vertex >> edge;
    if (vertex == 0 || edge == 0)
        return 0;

    vector<vector<PII>> graph(vertex);
    vector<PII> print;

    for (int i = 0; i < edge; i++)
    {
        int u = 0, v = 0, d = 0;
        cin >> u >> v >> d;

        graph[u].push_back(make_pair(d, v));
        graph[v].push_back(make_pair(d, u));
    }

    int root = 0;
    int cost = prim(root, graph, print);

    cout << "Total Weight = " << cost << endl;
    cout << "Root Node = " << root << endl;

    for (int i = 1, j = 0; i < (vertex);) // O(E)
    {
        int w = print[i].first, u = print[i].second;
        if (graph[u][j].first == w)
        {
            cout << graph[u][j].second << " " << u << endl;
            i++;
            j = 0;
        }
        else
        {
            j++;
        }
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}