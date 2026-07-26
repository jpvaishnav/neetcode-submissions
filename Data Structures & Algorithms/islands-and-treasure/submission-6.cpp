class Solution {
public:

    int dx[4] = {-1,1,0,0};
    int dy[4] = {0,0,-1,1};

    int inf = 2147483647;

    bool isValidIndex(int i, int j, int m, int n)
    {
        return (i>=0 && j>=0 && i<m && j<n);
    }

    void BFS(vector<vector<int>> & grid,
            vector<vector<bool>> & visited,
            int i, int j, int m, int n)
    {
        queue<pair<int, int>> q;
        q.push(make_pair(i,j));
        visited[i][j] = true;

        while(q.empty() == false)
        {
            pair<int, int> t = q.front();
            q.pop();
            for(int k=0; k<4; k++)
            {
                int i1 = t.first + dx[k];
                int j1 = t.second + dy[k];

                if(isValidIndex(i1,j1,m,n)
                    && visited[i1][j1] == false
                    && grid[i1][j1] > grid[t.first][t.second] + 1)
                    {
                        grid[i1][j1] = grid[t.first][t.second] + 1;
                        q.push(make_pair(i1,j1));
                        visited[i1][j1] = true;
                    }
            }
        }
    }

    void DFS(vector<vector<int>>& grid,
            vector<vector<bool>> & visited,
            int i, int j,
            int m, int n)
    {
        // mark source
        visited[i][j] = true;

        for(int k=0; k<4; k++)
        {
            int i1 = i + dx[k];
            int j1 = j + dy[k];

            if(isValidIndex(i1,j1,m,n)
                && visited[i1][j1] == false
                && grid[i1][j1] > grid[i][j] + 1)
                {
                    grid[i1][j1] = grid[i][j] + 1;
                    DFS(grid, visited, i1, j1, m, n);
                }
        }
    }

    void multiSourceBFS(vector<vector<int>> & grid, 
                        int m, int n)
    {
        queue<pair<int, int>> q;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        for(int i=0; i<m; i++)
        {
            for(int j=0; j<n; j++)
            {
                if(grid[i][j] == 0)
                {
                    q.push(make_pair(i,j));
                    visited[i][j] = true;
                }
            }
        }

        while(q.empty() == false)
        {
            pair<int, int> t = q.front();
            q.pop();
            for(int k=0; k<4; k++)
            {
                int i1 = t.first + dx[k];
                int j1 = t.second + dy[k];

                if(isValidIndex(i1,j1,m,n)
                    && visited[i1][j1] == false
                    && grid[i1][j1] > grid[t.first][t.second] + 1)
                    {
                        grid[i1][j1] = grid[t.first][t.second] + 1;
                        q.push(make_pair(i1,j1));
                        visited[i1][j1] = true;
                    }
            }
        }

        return;
    }

    void islandsAndTreasure(vector<vector<int>>& grid) {
        /*
        Approach: 
            1. source to destination
                Pick each INF node, and keep on updating it
            2. destination to source
                Pick destination treasure chest node and keep updating INF reachable nodes
                similar to uphill traversal in rising water problem
            Use DFS,
                maintain visited array in DFS traversal
                traverse using 4 directional neighbors,
                    // ignore -1
                update distance & apply DFS on neighbor node

        DFS fails here
            grid=[[2147483647,2147483647,2147483647],[2147483647,-1,2147483647],[0,2147483647,2147483647]]
        because problem is shortest distance:
            so, need to apply BFS:
            push source in queue
            while q is not empty
            put neighbors in bfs queue
            and keep on updating dist
        
        Time complexity is O(m*n*m*n)
        Optimization:
            Djikstra?
                - Keep finalized set and not yet finalized set
                - keep all cells in second(not finalized set)
                    - distance of 0 nodes is 0
                    - distance of INF nodes is INF
                - Now pick min distance node,
                    and update its immediate neighbor
                    - keep doing this until not yet finalized set has a node with non-INF nodes
                time: Picking each vertex and updating neighbor distance * get min
                        O(m*n * m*n)
                        - if getMin is implemented using priority queue
                        then it becomes
                        O(m*n * log(m*n))
            Any other optimization?
                Union-find?
                BFS from source?
                Multi source BFS is O(m*n)?
            Multi source BFS is modification of simple BFS:
                in simple disconnected BFS traversal:
                    we find a node with source condition,
                        and complete BFS on that source
                In multi source:
                    we put all source nodes in queue,
                        and start traversal.
                    Here first level is all nodes with 0 distance
                    Second level is all nodes with 1 distance
                    Third level will covered all nodes with distance 2,
                    and so on
                    till queue is completed.
                    every node is covered at most once, achieving O(m*n) time complexity
        Check visual of GIF or png images here
            https://github.com/jpvaishnav/Profile/blob/main/images/multi_source_bfs_grid_growth.gif
        
        */

        int m = grid.size();
        if(m==0)
        {
            return;
        }
        int n = grid[0].size();

        multiSourceBFS(grid, m, n);

        // for(int i=0; i<m; i++)
        // {
        //     for(int j=0; j<n; j++)
        //     {
        //         if(grid[i][j] == 0)
        //         {
        //             vector<vector<bool>> visited(m, vector<bool>(n, false));
        //             //DFS(grid, visited, i, j, m, n);
        //             BFS(grid, visited, i, j, m, n);
        //         }
        //     }
        // }

    }
};
