#include <list>
#include <queue>
#include <stack>
#include <iostream>
#include <climits>

using namespace std;

class Graph
{
    int nodes;
    list<int> *adj;

public:
    Graph(int n)
    {
        nodes = n;
        adj = new list<int>[nodes];
    }
    ~Graph()
    {
        delete[] adj;
        adj = NULL;
    }

    void addEdge(int startNode, int endNode)
    {
        adj[startNode].push_back(endNode);
        // adj[endNode].push_back(startNode); // undirected
    }

    void BFS(int s = 0)
    {
        int visited[nodes]{0};
        int distance[nodes]{INT_MAX};

        queue<int> q;
        q.push(s);
        visited[s] = 1;
        distance[s] = 0;

        while (!q.empty())
        {
            int cur = q.front();
            q.pop();
            cout << cur << " ";
            for (auto &i : adj[cur])
            {
                if (!visited[i])
                {
                    // in a graph unlike trees there can be cycles. therefore need to avoid visiting a node if it's already visited.
                    q.push(i);
                    visited[i] = 1;
                    distance[i] = distance[cur]+1;
                     /*in dijkstra algorithm, we follow the same concept except, when updaing the distance we get the minimum value.
                     however the adjacency list should have another cell to carry info regarding the weights. 
                     std::list<std::pair<int, int>> list[nodes];
                     if (distance[i] > distance[cur]+weight[i]) ? distance[i] = distance[cur]+weight[i] */
                }
            }
        }
        cout << endl;
        for (int i=0; i<nodes; i++)
        {
            cout << s << " -> " << i << " : " << distance[i] << endl;
        }
    }
    
    void DFS(int src)
    {
        int visited[nodes]{0};
        stack<int> s;
        visited[src] = 1;
        s.push(src);
        while (!s.empty())
        {
            int cur = s.top();
            s.pop();
            cout << cur << " ";
            for (auto &i : adj[cur])
            {
                if (!visited[i])
                {
                    s.push(i);
                    visited[i] = 1;
                }
            }
        }
    }

    void DFSUtil(int s, int *v)
    {
        v[s] = 1;
        cout << s << " ";
        for (auto &i : adj[s])
        {
            if (!v[i])
            {
                DFSUtil(i, v);
            }
        }
    }

    void DFSRec(int s)
    {
        int visited[nodes]{0};
        DFSUtil(s, visited);
        cout << endl;
    }
};

int main()
{
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);
    g.BFS(0);

    Graph g1(4);
    g1.addEdge(0, 1);
    g1.addEdge(0, 2);
    g1.addEdge(1, 2);
    g1.addEdge(2, 0);
    g1.addEdge(2, 3);
    g1.addEdge(3, 3);
    g1.DFSRec(2);
    g1.DFS(2);
    
    return 0;
}