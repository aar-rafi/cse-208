#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
#include <cmath>
#define INF 0x3f3f3f3f

using namespace std;
using PII = pair<int, int>;

void print(vector<int> &parent, int D)
{
    stack<int> s;
    int i = D;
    while (i != -1)
    {
        s.push(i);
        i = parent[i];
    }

    while (!s.empty())
    {
        cout << s.top();
        s.pop();
        if (!s.empty())
            cout << " -> ";
    }
    cout << endl
         << endl;
}

void dijkstra(vector<vector<PII>> graph, int S, int D)
{
    priority_queue<PII, vector<PII>, greater<PII>> PQ;
    vector<int> distance(graph.size(), INF);
    vector<int> parent(graph.size(), -1);
    int shortDistance = 0;

    distance[S] = 0;

    PQ.push(make_pair(0, S));
    while (!PQ.empty())
    {
        PII temp = PQ.top();
        PQ.pop();
        int u = temp.second;
        for (auto neighbour : graph[u])
        {
            int v = neighbour.second;
            int w = neighbour.first;

            if (distance[v] > distance[u] + w)
            {
                distance[v] = distance[u] + w;
                PQ.push(make_pair(distance[v], v));
                parent[v] = u;
            }
        }
    }
    cout << "Dijkstra Algorithm: " << endl;
    cout << distance[D] << endl;
    print(parent, D);
}

void bellmanFord(vector<vector<int>> graph, int vertex, int S, int D)
{
    cout << "Bellman Ford Algorithm:" << endl;

    int len = graph.size(); // edge
    vector<int> distance(vertex, INF);
    distance[S] = 0;
    vector<int> parent(vertex, -1);

    for (int i = 0; i < len - 1; i++)
    {
        for (vector<int> vec : graph)
        {
            int u = vec[0];
            int v = vec[1];
            int w = vec[2];
            if ((distance[v] > distance[u] + w))
            {
                distance[v] = distance[u] + w;
                parent[v] = u;
            }
        }
    }

    for (vector<int> vec : graph)
    {
        int u = vec[0];
        int v = vec[1];
        int w = vec[2];
        if ((distance[v] > distance[u] + w))
        {
            cout << "Negative weight cycle present" << endl
                 << endl;
            return;
        }
    }
    cout << distance[D] << endl;

    print(parent, D);
}

int main()
{
    freopen("./IOs/io2/in.txt", "r", stdin);
    freopen("./ios/io2/out.txt", "w", stdout);

    int vertex = 0, edge = 0;
    cin >> vertex >> edge;
    if (vertex == 0 || edge == 0)
        return 0;

    vector<vector<PII>> graph(vertex);
    vector<vector<int>> graphBellman(edge);
    for (int i = 0; i < edge; i++)
    {
        int u = 0, v = 0, d = 0;
        cin >> u >> v >> d;

        graph[u].push_back(make_pair(abs(d), v));
        vector<int> vec{u, v, d};
        graphBellman[i] = (vec);
    }

    int s = 0, d = 0;
    cin >> s >> d;

    bellmanFord(graphBellman, vertex, s, d);
    dijkstra(graph, s, d);

    fclose(stdout);
    fclose(stdin);
}