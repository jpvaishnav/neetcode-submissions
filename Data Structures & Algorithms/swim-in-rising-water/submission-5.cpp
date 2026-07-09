class Solution {
public:

    const int r_dir[4] = {-1,1,0,0};
    const int c_dir[4] = {0,0,-1,1};

    bool isValidIndex(int i, int j, int n)
    {
        return (i>=0 && i<n && j>=0 && j<n);
    }

    void DFS(vector<vector<int>> & grid,
            vector<vector<bool>> & visited,
            int & ans,
            int i, int j,
            int t,
            int n)
    {
        // mark as visited
        visited[i][j] = true;

        // cout << "entered DFS for node "<<i<<" "<<j<<" at time "<<t<<endl;

        if(i==n-1 && j==n-1)
        {
            ans = min(ans, t);
            visited[i][j] = false; // backtrack - found via debugging console statement
            return;
        }

        // early exit if time elapsed is greater than ans
        if(t >= ans)
        {
            visited[i][j] = false;
            return;
        }

        // traverse neighbors
        for(int k=0; k<4; k++)
        {
            int adj_r = i + r_dir[k];
            int adj_c = j + c_dir[k];
            if(isValidIndex(adj_r,adj_c,n)&& visited[adj_r][adj_c] == false)
            {
                int adj_height = grid[adj_r][adj_c];
                // timeToReachAdj is the time taken where swimming through adjacent is possible
                // why 0? -ve means neighbor node is already submerged, and at current time, the pointer can swim
                int timeToReachAdj = max(0, adj_height-t);
                int timeElapsed = t + timeToReachAdj;
                //int timeElapsed = (timeToReachAdj > 0) ? (t + timeToReachAdj) : t;
                // if time to reach adjacent is 0, that means with current time t, we are reaching, otherwise add required time
                DFS(grid, visited, ans, adj_r, adj_c, timeElapsed, n);
            } 
        }

        visited[i][j] = false;
        return;
    }

    pair<int,int> getMinDistNodeNotInFinalisedSet(vector<vector<bool>> & finalised, 
                                                vector<vector<int>> & dist, int n)
    {
        int min_dist = INT_MAX;
        pair<int,int> min_node = make_pair(-1,1);
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(finalised[i][j] == false && dist[i][j] < min_dist)
                {
                    min_dist = dist[i][j];
                    min_node = make_pair(i,j);
                }
            }
        }
        return min_node;
    }


    int swimInWater(vector<vector<int>>& grid) {
        /*
        Used AI to understand question, as question statement is not that clear
        Think of this problem as a 2D hiking grid where each cell has a specific height (elevation). Instead of walking over the hills, a flood is rising globally across the entire grid at a rate of 1 unit of height per second.You want to swim from the top-left corner (0, 0) to the bottom-right corner (n-1, n-1). You can move to an adjacent square only if the water has completely submerged both your current square and the next square.

        - from top left (0,0) we start a DFS, keep time counter,
        and traverse all neighbor nodes and update ans
            - if a neighbor path is already greater than our ans, then we can cut that solution
                - cutting down non-solution path in backtracking
                - this is only when weight is positive
            - Backtrack the node
                - when entering in DFS< mark visited = true
                - when going out, mark visited = false
                    - so that other paths can traverse through this node
        */

        /*
        ran into TLE error, as give code time complexity is O(4^N square)
        Time Limit Exceeded. You may have an infinite loop or your code is too inefficient.
        - we dont have any code path to optimize in this approach
        - so change the approach
        -- based on AI suggestions and problem statement visualisation:
            - Djikstra's shortest path algo fits here
            - source is (0,0), target is (n-1,n-1)
            - and need to find minimum time taking path
            - it means there can be multiple paths between source and dest
            - and the one we need to find is minimum/shortest
        - Algo:
            - put all nodes of grid in not yet finalized set
            - pick source node, put it in finalized and update distance of neighbor
                - distance here means time taken to reach neighbor n
                - timeToReach[adj] = min(timeToReach[adj], timeToReach[source] + (Height diff between source and adj if >=0))
            - if destination node is reached, that is already minimum distance/time path.
            - distance is equivalent to time reached in this question.
        
        */

        int n = grid.size();
        if(n ==0)
        {
            return 0;
        }

        vector<vector<bool>> finalised(n, vector<bool>(n, false));
        vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
        // source = 0,0
        // time to reach source = value of source
        // from this case, found that time has to be source height value, otherwise the pointer can't swim
        // grid=[[3,2],[0,1]]

        //Djikstra(grid, finalised, dist, i, j, n);
        //mark source node
        //finalised[0][0] = true;
        // it will be picked by first iteration and marked as finalised
        dist[0][0] = grid[0][0];

        while(true)
        {
            pair<int,int> p = getMinDistNodeNotInFinalisedSet(finalised, dist, n);
            if(p.first == -1 && p.second == -1)
            {
                // no min distance node found in not finalised set;
                break;
            }
            //cout<< "Node picked: "<<p.first<<" "<<p.second<<" dist: "<<dist[p.first][p.second]<<endl;
            finalised[p.first][p.second] = true;
            if(p.first == n-1 && p.second == n-1)
            {
                return dist[p.first][p.second];
            }

            // update neighbors
            for(int k=0; k<4; k++)
            {
                int adj_i = p.first + r_dir[k];
                int adj_j = p.second + c_dir[k];

                if(isValidIndex(adj_i, adj_j, n)
                    && finalised[adj_i][adj_j] == false)
                {
                    int timeElapsedTillMin = dist[p.first][p.second];
                    // this condition found from failing test case: [[10,12,4,6],[9,11,3,5],[1,7,13,8],[2,0,15,14]]
                    // visualisation idea: if we are at u node, and neighbor is v node
                        // then time to reach v would be = time take to reach u + extra time required at v
                        // and extra time required at v would be if v's height is greater than u's current water level(dist[i][j])
                            // then the diff between v height and u's current water level would be accounted as extra time required
                            // see in example where in first row we move from 4 to 6.
                            // time to reach 4 = 12, 
                            // time to reach 6, no extra time needed, because 12 <= 6, its already submerged
                            // while in last column, when going from 8 to 14
                                // time to reach 8 = 12,
                                // extra time needed to reach 14 = 14 - 12 = 2
                    //int cost = max(0, grid[adj_i][adj_j] - grid[p.first][p.second]);
                    int cost = max(0, grid[adj_i][adj_j] - timeElapsedTillMin);
                    
                    dist[adj_i][adj_j] = min(dist[adj_i][adj_j], 
                                        dist[p.first][p.second] + cost);
                }
            }
        }

        // DFS(grid, visited, ans, 0, 0, grid[0][0], n);
        return INT_MAX;
        //return ans;
    }
};
