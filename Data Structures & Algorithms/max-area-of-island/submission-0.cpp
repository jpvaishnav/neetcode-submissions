class Solution {
public:

    // direction array
    int row_direction[4] = {0,0,-1,1};
    int col_direction[4] = {-1,1,0,0};

    bool isValidIndex(int i, int j, int m, int n)
    {
        return (i>=0 && j>=0 && i<m && j<n);
    }

    // is ValidNode is equivalent to isSafe here
    bool isValidNode(vector<vector<int>> & grid, 
            int i, 
            int j, 
            int m,
            int n)
    {
        if(isValidIndex(i,j,m,n) && grid[i][j]==1)
        {
            return true;
        }
        return false;
    }

    void DFS(vector<vector<int>> & grid, 
            int i, 
            int j,
            int m,
            int n,
            int & area)
    {
        // marking as 0 means either in-accessisible or already visited
        grid[i][j] = 0;
        area++;
        // pick neighbors
        // i,j -> i+1,j; i-1,j; i, j+1; i, j-1;
        for(int k=0; k < 4; k++)
        {
            int neighbor_row = i + row_direction[k];
            int neighbor_col = j + col_direction[k];
            if(isValidNode(grid, neighbor_row, neighbor_col, m, n))
            {
                DFS(grid, neighbor_row, neighbor_col, m, n, area);
            }
        }
        return;
    }

    int maxAreaOfIsland(vector<vector<int>>& grid) {
        /*
        Approach - same as counting number of islands
        DFS with valid index neighbors and visited array

        When calling DFS, pass a variable called area
        incremenet are when visiting a node

        time complexity: O(n*n), total number of nodes
        Aux space: O(n*n), for recurive calls in function stack

        */

        int m = grid.size(); // numer of rows
        int ans = 0;
        if (m == 0)
        {
            return ans;
        }
        int n = grid[0].size();
        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(grid[i][j] == 1)
                {
                    int area = 0;
                    DFS(grid, i, j, m, n, area);
                    ans = max(ans, area);
                }
            }
        }

        return ans;
    }
};
