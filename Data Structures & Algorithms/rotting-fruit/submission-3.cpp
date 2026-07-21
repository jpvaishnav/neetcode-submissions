class Solution {
public:

    const int dr[4] = {-1,1,0,0};
    const int dc[4] = {0,0,-1,1};

    bool isValidIndex(int r, int c, int m, int n)
    {
        return (r>=0 && c>=0 && r<m && c<n);
    }

    void BFS(vector<vector<int>> & grid,
            int r, int c,
            int m, int n,
            vector<vector<int>> & dist)
    {
        queue<vector<int>> q;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        // queue of (x,y, time counter)
        vector<int> temp(2);
        temp[0] = r;
        temp[1] = c;
        q.push(temp); // insert node
        visited[r][c] = true;
        dist[r][c] = 0;

        while(q.empty() == false)
        {
            vector<int> t = q.front();
            q.pop();

            int top_r = t[0];
            int top_c = t[1];

            for(int k=0; k<4; k++)
            {
                int r1=top_r+dr[k];
                int c1=top_c+dc[k];

                if(isValidIndex(r1,c1,m,n) 
                    && grid[r1][c1] == 1
                    && visited[r1][c1] == false)
                {
                    // insert in queue
                    temp[0] = r1;
                    temp[1] = c1;
                    q.push(temp);
                    //grid[r1][c1] = 2;
                    dist[r1][c1] = min(dist[r1][c1], dist[top_r][top_c] + 1);
                    visited[r1][c1] = true;
                    //cout<<"Marking fruite as rotten "<<r1<<" "<<c1<<" "<<(counter+1)<<endl;
                }
            }
        }
    }

    int orangesRotting(vector<vector<int>>& grid) {
        /*
        Approach: Traversal
        DFS can be applied as clean code,
        but BFS would suite better as minimum number of minutes(or max levels)
        is required as answer
        Each level of BFS would maintain a counter on time
            - similar to shorted path in unidrected unweighted graph
        Time complexity: O(m*n)
        Aus space: O(m*n) for queue

        Test case: [[2,1,1],[1,1,1],[0,1,2]]
        it means a fruit can be rotten by more than 1 rotten fruit chain
        and we need to pick minimum one
        when traversing current BFS, use visited array to indicate if fruite is visited
        and maintain a dist variable for (i,j) which represents min time
            - so that dist of a node can be updated by other nodes
                - similar to relaxation
            - also helpful in checking if a node is fresh fruite and its dist is 0
                - then it means it wasn't reached/rotten and return -1
        */

        int m = grid.size();
        if(m==0)
        {
            return 0;
        }
        int n = grid[0].size();

        int ans = 0;

        vector<vector<int>> dist(m, vector<int>(n, INT_MAX));

        for(int i=0; i<m; i++)
        {
            for(int j=0; j<n;j++)
            {
                if(grid[i][j] == 2)
                {
                    //cout<<"Starting BFS on "<<i<<" "<<j<<endl;
                    // apply BFS
                    BFS(grid,i,j,m,n,dist);
                }
            }
        }

        // if any fresh fruit is remaining return -1;
        for(int i=0; i<m; i++)
        {
            for(int j=0; j<n;j++)
            {
                if(grid[i][j] == 1)
                {
                    if(dist[i][j] == INT_MAX)
                    {
                        return -1;
                    }
                    ans = max(ans, dist[i][j]);
                }
            }
        }

        return ans;
    }
};
