#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> graph;
vector<vector<int>> weight;
int main()
{
    int n, e;
    cin >> n >> e;
    graph.resize(n + 1);
    weight.resize(n + 1, vector<int>(n + 1, 0));
    for (int i = 0; i < e; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back(v);
        graph[v].push_back(u);
        weight[u][v] = w;
        weight[v][u] = w;
    }
    int src;
    cin >> src;
    vector<int> dist(n + 1, INT_MAX);
    dist[src] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src});
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        for (int v : graph[u])
        {
            if (dist[v] > dist[u] + weight[u][v])
            {
                dist[v] = dist[u] + weight[u][v];
                pq.push({dist[v], v});
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        cout << dist[i] << " ";
    }
    cout << endl;
}