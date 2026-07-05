class Solution {
public:

    int getShortestDistNode(vector<bool> & finalized, vector<int> & dist, int n)
    {
        int shortest_dist = INT_MAX;
        int shortest_node = -1;
        for(int i = 0; i < n; i++)
        {
            if(finalized[i] == false)
            {
                if(dist[i] < shortest_dist)
                {
                    shortest_node = i;
                    shortest_dist = dist[i];
                }
            }
        }
        return shortest_node;
    }

    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        /*
        Apply djikstra algorithm to find shortest distance for all nodes
        (given then cost/time is not negative)
        once djikstra gives shortest distance/cost from source to all nodes,
        find the node that is farthest, and return its distance. because that's the overall minimum time take to visit all nodes

        // maintain 2 sets finalized and not yet finalized
        // use boolean array to maintain these sets
        while there is a node in not finalized set,
            pick the node with shortest distance,
            mark it as finalized
            and get all its neighbors in non-finalized set
                and update their index using relax algorithm
                dist[v] = min(dist[v], dist[u] + cost[u][v]);
                // this exercise is similar to updating all neighbor nodes after popping bfs top or after entering a dfs loop
        */

        // create adjacency list, so that neighbros can be fetched in O(1)

        // labelling is from 1 to n
        // so either convert array size to n+1, in that case will have to handle arr[0] as a special case
        // or encrypt nodes to -1, so that they are indexed from 0 to n-1
        vector<vector<pair<int, int>>> adjList(n);
        for(int i = 0; i < times.size(); i++)
        {
            vector<int> edge = times[i];
            int src = edge[0]-1;
            int dest = edge[1]-1;
            int cost = edge[2];
            adjList[src].push_back(make_pair(dest, cost));
        }

        vector<bool> finalized(n, false);
        vector<int> dist(n, INT_MAX);
        // INT_MAX represents currently all nodes are unreachable

        dist[k-1] = 0;
        // it will be finalized by first iteration of loop

        do
        {
            // get shortest distance node from finalized node, if not available break
            int shortest_node = getShortestDistNode(finalized, dist, n);
            if(shortest_node == -1)
            {
                break;
            }

            cout << "Processing shortest distance node"<< shortest_node << " "<<dist[shortest_node]<<endl;
            // process shortest distance node
            finalized[shortest_node] = true;
            for(auto neighbor: adjList[shortest_node])
            {
                int neighbor_node = neighbor.first;
                int cost = neighbor.second;
                dist[neighbor_node] = min(dist[neighbor_node], dist[shortest_node] + cost);
            }
        }
        while(true);

        int ans = INT_MIN;
        for(int i = 0; i < n; i++)
        {
            if(dist[i] == INT_MAX)
            {
                // it means ith node was unreachable
                return -1;
            }
            ans = max(ans, dist[i]);
        }
        return ans;
    }
};
