class Solution {
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        /*
        Approach: Based on given examples
        Tree definition is not given in question
        so, if there is no cycle in graph, then it is tree
        cycle detection in undirected graph:
            - use bfs
            - while traversing neighbor nodes
            - if we find any neighbor node n is already in queue
                - that means source to n exists
                - and n is connected to current node
                    source - n - current node- source creates cycle
                - a node's neighbor is its parent as well which is already visited
                - and can be assumed as cycle, so we need to exclude parent when comparing
        corner case:
            if disconnected trees exist: are they also valid solution?
        source node:
            - any node can be assumed source/root of tree.
            - 0
        */
        // convert edges into adjacency list for O(1) access of neighbors

        if (edges.size() != n-1)
        {
            return false;
        }

        vector<vector<int>> adjList(n, vector<int>(0));
        for(int i=0; i<edges.size(); i++)
        {
            int u = edges[i][0];
            int v = edges[i][1];
            adjList[u].push_back(v);
            // undirected graph, so has to push both u -> v and v->u
            adjList[v].push_back(u);
            //cout << "u -> v " << u<<" "<<v<<endl;
        }

        queue<int> q;
        vector<bool> visited(n, false);
        vector<int> parent(n, -1);
        q.push(0);
        visited[0] = true;

        while(q.empty() == false)
        {
            int t = q.front();
            q.pop();
            //cout << "Adjacent of "<<t<<endl;
            for(auto adjacent: adjList[t])
            {
                cout << adjacent << endl;
                if(visited[adjacent] == true && adjacent != parent[t])
                {
                    //cout<< "Found cycle forming node" << adjacent << endl;
                    // it means cycle exists -> not a tree
                    return false;
                }
                if(visited[adjacent] == false)
                {
                    q.push(adjacent);
                    visited[adjacent] = true;
                    parent[adjacent] = t;
                }
            }
        }

        // in case of forest like (0,1) (2,3) -> it is not tree
        // Simple check: if any of the node is unvisited after 1 iteration, it means there are multiple tree
        for(int i =0; i < n; i++)
        {
            if(visited[i] == false)
            {
                return false;
            }
        }
        return true;
    }
};
