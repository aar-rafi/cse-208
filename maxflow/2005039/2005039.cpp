 
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
#define INF 0x3f3f3f3f

using namespace std;

bool BFS(vector<vector<int>> &residualCapacity,
         unordered_map<int, int> &parent,
         int s, int t)
{
    vector<bool> visited(residualCapacity.size(), 0);
    queue<int> Q;
    Q.push(s);
    visited[s] = 1;
    bool foundPath = false;

    while (!Q.empty())
    {
        int u = Q.front();
        for (int v = 0; v < residualCapacity.size(); v++)
        {
            if (!visited[v] && residualCapacity[u][v])
            {
                parent.insert({v, u});
                visited[v] = 1;
                Q.push(v);
                if (v == t)
                {
                    foundPath = true;
                    break;
                }
            }
        }
    }
    return foundPath;
}

vector<vector<int>> fordFulkerson(vector<vector<int>> &graph, int s, int t)
{
    vector<vector<int>> residualCapacity = graph;

    unordered_map<int, int> parent;

    vector<vector<int>> augmentedPaths;
    int maxFlow = 0;

    while (BFS(residualCapacity, parent, s, t))
    {
        vector<int> augmentedPath;
        int flow = INF;
        int v = t;
        while (v != s)
        {
            augmentedPath.push_back(v);
            int u = parent[v];
            min(flow, residualCapacity[u][v]);
            v = u;
        }
        augmentedPath.push_back(s);
        reverse(augmentedPath.begin(), augmentedPath.end());
        augmentedPaths.push_back(augmentedPath);

        maxFlow += flow;
        v = t;
        while (v != s)
        {
            int u = parent[v];
            residualCapacity[u][v] -= flow;
            residualCapacity[v][u] += flow;
            v = u;
        }
    }
    return residualCapacity;
}

int main()
{
    int vertex = 0;
    cin >> vertex;
    vector<vector<int>> faceOff;
    vector<vector<int>> info;

    vector<string> vs;

    // vs = {"ami"};
    // cout << vs[0][0];

    for (int i = 0; i < vertex; i++)
    {
        string s;
        int w, l, r;
        cin >> s >> w >> l >> r;
        vs.push_back(s);
        vector<int> v = {w, l, r};
        info.push_back(v);
        v.clear();
        vector<int> v1;
        for (int j = 0; j < vertex; j++)
        {
            int a;
            cin >> a;

            v1.push_back(a);
        }
        faceOff.push_back(v1);
    }
    // for (int i = 0; i < vertex; i++)
    // {
    //     cout << info[i].size() << " " << faceOff[i].size();
    // }

    unordered_map<string, int> gMap;
    int edge = 1;
    int s = 0;
    int t = vertex * (vertex - 1) + vertex + 1;
    vector<vector<int>> graph(t + 1, vector<int>(t + 1, 0));

    for (int i = 0; i < vertex; i++, edge++)
    {
        gMap.insert({vs[i], edge});
        // graph.push_back({edge, t, 0}); // max(info[i][], 0)
        // graph[edge][t]= 0;
    }
    for (int i = 0; i < vertex; i++)
    {
        for (int j = 0; j < vertex; j++)
        {
            if (i != j)
            {
                string temp = vs[i] + vs[j];
                // vs.push_back(temp);
                gMap.insert({temp, edge});
                graph[s][gMap[temp]] = faceOff[i][j];
                // graph.push_back({s, edge, faceOff[i][j]});
                edge++;
            }
        }
    }
    for (int i = 0; i < vertex; i++)
    {
        for (int j = 0; j < vertex; j++)
        {
            string stemp = vs[i] + (vs[j]);
            int temp = gMap[stemp];
            // graph.push_back({temp, gMap[vs[i]], INF});
            // graph.push_back({temp, gMap[vs[j]], INF});
            graph[temp][gMap[vs[i]]] = INF;
            graph[temp][gMap[vs[j]]] = INF;
        }
    }

    // cout << "Adjacency Matrix:" << endl;
    //  for (int i = 0; i < info.size(); ++i)
    //  {
    //      // for (int j = 0; j <= t ; ++j)
    //      // {
    //      // if (graph[i][j] == INF)
    //      // {
    //      //     cout << "INF\t";
    //      // }
    //      // else
    //      // {
    //      //     cout << graph[i][j] << "\t";
    //      // }
    //      cout << info[1][1]; // << " " << info[i][1] << " " << info[i][2]; //<< " " <<
    //      // cout << faceOff[i][0] << " " << faceOff[i][1] << " " << faceOff[i][2];
    //      // }
    //      // cout << endl;
    //  }

    // vector<vector<int>> residual = fordFulkerson(graph, s, t);
    // for (int i = 0; i < vertex; i++)
    // {
    //     for (int j = 0; j < vertex; j++)
    //     {
    //         string stemp = vs[i].append(vs[j]);
    //         int temp = gMap[stemp];
    //         if(residual[s][temp] != 0){
    //             cout<<temp<<"gets eliminated"<<endl;
    //         }
    //     }
    // }

    //
    // gMap.insert({"ba", 10});
    // gMap.insert({"aa", 100});

    // unordered_map<string, int>::iterator it;
    // for (it = gMap.begin(); it != gMap.end(); it++)
    // {
    //     cout << it->first << " " << it->second;
    // }
}
