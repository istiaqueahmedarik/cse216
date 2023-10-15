#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    int src, dest, weight;
};

class Graph
{
    int V, E;
    vector<Edge> edges;

public:
    Graph(int V, int E)
    {
        this->V = V;
        this->E = E;
    }

    void addEdge(int src, int dest, int weight)
    {
        Edge edge = {src, dest, weight};
        edges.push_back(edge);
    }

    void bellmanFord(int src)
    {
        vector<int> dist(V, INT_MAX);
        dist[src] = 0;

        for (int i = 1; i <= V - 1; i++)
        {
            for (auto edge : edges)
            {
                int u = edge.src;
                int v = edge.dest;
                int w = edge.weight;
                if (dist[u] != INT_MAX && dist[u] + w < dist[v])
                {
                    dist[v] = dist[u] + w;
                }
            }
        }

        for (auto edge : edges)
        {
            int u = edge.src;
            int v = edge.dest;
            int w = edge.weight;
            if (dist[u] != INT_MAX && dist[u] + w < dist[v])
            {
                cout << "Graph contains negative weight cycle" << endl;
                return;
            }
        }

        cout << "Vertex Distance from Source" << endl;
        for (int i = 0; i < V; i++)
        {
            cout << i << "\t\t" << dist[i] << endl;
        }
    }
};

int main()
{
    int V = 5, E = 8;
    Graph graph(V, E);

    graph.addEdge(0, 1, -1);
    graph.addEdge(0, 2, 4);
    graph.addEdge(1, 2, 3);
    graph.addEdge(1, 3, 2);
    graph.addEdge(1, 4, 2);
    graph.addEdge(3, 2, 5);
    graph.addEdge(3, 1, 1);
    graph.addEdge(4, 3, -3);

    graph.bellmanFord(0);

    return 0;
}
