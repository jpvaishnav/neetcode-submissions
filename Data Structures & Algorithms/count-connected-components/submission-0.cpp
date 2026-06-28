class Solution {
public:

    void DFS(vector<vector<int>>& adjList, vector<bool> & visited, int source)
    {
        // mark as visited, if coming to DFS; similar to BFS queue
        visited[source] = true;

        // pick all unvisited nodes, and process
        for(auto neighbor: adjList[source])
        {
            if(visited[neighbor] == false)
            {
                DFS(adjList, visited, neighbor);
            }
        }
        return;
    }

    int countComponents(int n, vector<vector<int>>& edges) {

        // directed graph has different algorithms
        // like Kosaraju, low time - discovery time comparison
        // undirected graph should be doable by simple dfs
        // Mark all nodes as unvisited,
        // Pick a node, if not already visited - then increase counter
            // And apply DFS for that node, all connected noes to that node will be mark as visited now
        // next iterations get one of remaining unvisited node, we mark that as source and then do DFS

        // first, convert to adjacency list, so that DFS is O(V + E)
        
        vector<vector<int>> adjList(n); // custom initialization not needed
        // vector<vector<int>> adjList(n) = new vector<vector<int>>();
        // for(int i = 0; i < n; i++)
        // {
        //     vector<int> temp = new vector<int>();
        //     adjList.push_back(temp);
        // }
        for(int i = 0; i < edges.size(); i++)
        {
            //pick each edge
            vector<int> edge = edges[i];
            int u = edge[0];
            int v = edge[1];
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }

        vector<bool> visited(n); // by default, initialized to false

        int components = 0;

        for(int i = 0; i < n; i++)
        {
            if(visited[i] == false)
            {
                components++;
                DFS(adjList, visited, i);
            }
        }

        return components;

    }
};
