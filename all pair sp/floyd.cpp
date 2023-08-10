#include <iostream>
#include <vector>
#define INF 0x3f3f3f3f

using namespace std;

void show(int vertex, vector<vector<int>> &graph)
{
    cout << "Shortest Distance Matrix" << endl;
    for (int i = 0; i < vertex; i++)
    {
        for (int j = 0; j < vertex; j++)
        {
            if (graph[i][j] == INF)
                cout << "INF"
                     << " ";
            else
                cout << graph[i][j] << " ";
        }
        cout << endl;
    }
}

void flWarshall(int vertex, vector<vector<int>> graph)
{
    for (int i = 0; i < vertex; i++)
    {
        for (int j = 0; j < vertex; j++)
        {
            for (int k = 0; k < vertex; k++)
            {
                if (graph[j][k] > graph[j][i] + graph[i][k])
                    graph[j][k] = graph[j][i] + graph[i][k];
            }
        }
    }
    show(vertex, graph);
}

void matrixMultiplication(int vertex, vector<vector<int>> graph)
{
    vector<vector<int>> tempGraph = graph;
    for (int z = 0; z < vertex; z++)
    {
        for (int i = 0; i < vertex; i++)
        {
            for (int j = 0; j < vertex; j++)
            {
                for (int k = 0; k < vertex; k++)
                {
                    tempGraph[i][j] = min(tempGraph[i][k] + tempGraph[k][j], tempGraph[i][j]);
                }
            }
        }
        for (int m = 0; m < vertex; m++)
        {
            if (tempGraph[m][m] < 0)
            {
                cout << "Negative Cycle Presents" << endl;
                return;
            }
        }

        if (graph == tempGraph)
            break;
        else
            graph = tempGraph;
    }
    show(vertex, graph);
}

int main()
{
    // freopen("./Testcases/tc03/in.txt", "r", stdin);
    // freopen("./testcases/tc03/kruskal.txt", "w", stdout);

    int vertex = 0, edge = 0;
    cin >> vertex >> edge;
    if (vertex == 0 || edge == 0)
        return 0;

    vector<vector<int>> graph(vertex, vector<int>(vertex, INF));

    for (int i = 0; i < edge; i++)
    {
        int u = 0, v = 0, w = 0;
        cin >> u >> v >> w;
        u--;
        v--;
        graph[u][v] = w;
    }
    for (int i = 0; i < vertex; i++)
    {
        graph[i][i] = 0;
    }

    flWarshall(vertex, graph);
    matrixMultiplication(vertex, graph);

    // fclose(stdin);
    // fclose(stdout);
}
