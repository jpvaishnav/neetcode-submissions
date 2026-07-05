class Solution {
public:

    bool isValidNode(int i, int j, int m, int n)
    {
        return (i>=0 && j>=0 && i<m && j<n);
    }

    const int row_directions[4] = {0,0,-1,1};
    const int col_directions[4] = {-1,1,0,0};
    
    void DFS(vector<vector<char>>& board,
            int i, int j, int m, int n)
    {
        //cout << " entering dfs "<< i << " " << j << endl;
        // mark the node as visited, by marking o to Y (so that in end, we can switch back to o)
        board[i][j] = 'Y';

        for (int k = 0; k < 4; k++)
        {
            int row_index = i + row_directions[k];
            int col_index = j + col_directions[k];
            if(isValidNode(row_index, col_index, m, n) && board[row_index][col_index] == 'O')
            {
                DFS(board, row_index, col_index, m, n);
            }
        }
    }
    void solve(vector<vector<char>>& board) {
        /*
        Approach: 
            if any of edge node is open, and if it is connected to any other open nodes, 
                then that node is also not surrounded
            So, un-surroundable nodes can be found out by applying DFS on edge open nodes
            and temporarily updating them to N
            After one traversal, the nodes which are still O in grid are surround and can be updated to X
            and re-update N to X before returning.

            Why we didn't simply went to a non boundary node which is 'O' and updated it directly to 'X'?
                - because we dont yet know if that node can be connected to any open node at boundary

            Pattern: Based on question example, visualisations
            DFS TRAVERSAL PATTERN(4 directions) is similar to islands count problem, only difference is start constraint
            Time complexity: O(M*N)

            perf optimizations by Gemini
            merge last 2 loops in 1: agreed
            use const in direction array, because if changed to const
            -> then compiler does not create array each time
            -> rather it creates 4 conditions ad applies values directly when compiling/building
        */

        int m = board.size();
        if(m==0)
        {
            return;
        }
        int n = board[0].size();

        // traverse all corner elements
        for(int j = 0; j < n; j++)
        {
            // 1st and last row
            if(board[0][j] == 'O')
            {
                // cout << "starting dfs: "<< 0 << " "<< j << endl;
                DFS(board, 0, j, m, n);
            }
            if(board[m-1][j] == 'O')
            {
                // cout << "starting dfs: "<< m-1 << " "<< j << endl;
                DFS(board, m-1, j, m, n);
            }
        }

        // 1st and last column
        for(int i = 0; i < m ; i++)
        {
            // j = 0 and j = n-1
            if(board[i][0] == 'O')
            {
                // cout << "starting dfs: "<< i << " "<< 0 << endl;
                DFS(board, i, 0, m, n);
            }
            if(board[i][n-1] == 'O')
            {
                // cout << "starting dfs: "<< i << " "<< n-1 << endl;
                DFS(board, i, n-1, m, n);
            } 
        }

        // now all o can be surrounded by x
        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(board[i][j] == 'O')
                {
                    board[i][j] = 'X';
                }

                // optimizations, avoid a traversal
                if(board[i][j] == 'Y')
                {
                    board[i][j] = 'O';
                }
            }
        }

        // // restore all y un-surroundabled by o
        // for(int i = 0; i < m; i++)
        // {
        //     for(int j = 0; j < n; j++)
        //     {
        //         if(board[i][j] == 'Y')
        //         {
        //             board[i][j] = 'O';
        //         }
        //     }
        // }
    }
};
