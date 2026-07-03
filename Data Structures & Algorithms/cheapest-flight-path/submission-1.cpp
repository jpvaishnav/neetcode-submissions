class Solution {
public:

    void DFS(vector<vector<pair<int,int>>> & adjList, 
            vector<bool> & visited, 
            int source, 
            int & dest, 
            int stops, 
            int & k, 
            int cost, 
            int & ans)
    {
        cout << "source: " << source << " stops: "<< stops << " cost: " << cost << endl;
        // trim non-solution paths
        if(stops > k)
        {
            return;
        }
        if(cost > ans)
        {
            return; // If cost was negative then we would have to avoid this
        }
        // mark source node as visited
        visited[source] = true;
        // check if destination
        if(source == dest)
        {
            ans = min(ans, cost);
        }

        // pick all unvisited neighbors
        for(auto neighbor: adjList[source])
        {
            int node = neighbor.first;
            int weight = neighbor.second;
            if(visited[node] == false)
            {
                DFS(adjList, visited, node, dest, stops+1, k, cost + weight, ans);
            }
            // Problem with this approach is that -
            // the code is not visiting the same node again, if it has already been visited
            // for example: 0 -> 1 -> 2 -> 3 DFS: 3 is visited
            // so 0 -> 1-> 3 won't be there
            // we need to unvisit nodes.
            visited[node] = false;
        }

        return;

    }
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        /*
        If the question was find cheapest flight between source to destination,
        then we would choose Djikstra, because graph is directed weighted graph.
        But the condition says at most K stops, so we can't apply Djikstra,
        because Djikstra looks for weight based optimisation among 2 path, and while doing
        that, it might eliminate the path which has lessert stops.

        Apply traditional BFS from source to destination.
        Find all paths from src to dest
            -> If any path goes beyond K stops -> eliminate it{backtracking - cutting non-solution paths}
            -> If any path goes beyond current min cost -> eliminate it {backtracking - cutting non-solution paths}
            Otherwise reach dest and update cost
        
        // Data structure conversion: COnvert into adjacency list
        n vectors, one for each vertex.
        each vector<pair<int,int>> contains neighbor and cost as pair
        */

        // convert to adjacency list
        vector<vector<pair<int,int>>> adjList(n);
        for(auto flight: flights)
        {
            int from_airport = flight[0];
            int to_airport = flight[1];
            int cost = flight[2];
            adjList[from_airport].push_back(make_pair(to_airport, cost));
        }

        int cheapest_cost = INT_MAX;

        // Traverse BFS
        vector<bool> visited(n);
        // queue<pair<int,int>> q; // source, stops
        // q.push(make_pair(src,0));
        // visited[src] = true;
        // while(q.empty()==false)
        // {
        //     pair<int,int> top = q.top();
        //     q.pop();
        //     if(top.first == dst)
        //     {
        //         cheapest_cost = min(cheapest_cost, top.)
        //         // we need to store cost till node top as well while pushing
        //         // but triplets aren't supported in c++
        //         // so, we can use dfs here and pass all these variables in function parameters
        //     }
        // }

        // stops count should be -1 for source because stops does not include source and destination
        DFS(adjList, visited, src, dst, -1, k, 0, cheapest_cost);

        if(cheapest_cost != INT_MAX)
        {
            return cheapest_cost;
        }
        return -1;
    }
};
