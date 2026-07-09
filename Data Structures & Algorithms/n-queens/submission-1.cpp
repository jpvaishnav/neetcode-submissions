class Solution {
public:

    bool isFeasible(vector<vector<bool>> & visited, 
                    int i, int j, int n)
    {
        // check row-wise
        for(int col=0; col<j; col++)
        {
            // 0 0 0 0 1 0 0 1(i,j) 0 0 0 0
            if(visited[i][col] == true)
            {
                //cout<< "returning false in row for "<<i<<" "<<j<<endl;
                return false;
            }
        }

        // check column wise
        for(int row=0; row<i;  row++)
        {
            if(visited[row][j] == true)
            {
                //cout<< "returning false in column for "<<i<<" "<<j<<endl;
                return false;
            }
        }

        // diagonal check
        // pattern: (0,0) (1,1) (2,2) ... (i,j)
        // (i+1,j).... (n-1,j) is not possible because our traversal is from top to bottom
        // but (i-1, j+1),.. (i-2)(j+2),....(0,n-1) is possible
        // upper left diagonal, since start can be any row, 
        // so lets start from the pointer itself, and keep decreasing
        int diag_i = i-1;
        int diag_j = j-1;
        while(diag_i>=0 && diag_j>=0)
        {
            if(visited[diag_i][diag_j] == true)
            {
                //cout<< "returning false in left diagonal for "<<i<<" "<<j<<" "<<"conflicting with "<<diag_i<<" "<<diag_j<<endl;
                return false;
            }
            diag_i--;
            diag_j--;
        }

        // upper right diaognal
        diag_i = i-1;
        diag_j = j+1;
        while(diag_i>=0 && diag_j<=n-1)
        {
            if(visited[diag_i][diag_j] == true)
            {
                // cout<< "returning false in right diagonal for "<<i<<" "<<j<<endl;
                return false;
            }
            diag_i--;
            diag_j++;
        }
        // all checks passed, and reached here
        return true;
    }

    bool backTrack(vector<vector<bool>> & visited, int n,
                    int row, vector<vector<string>> & ans)
    {
        if(row==n)
        {
            vector<string> solution;
            // answer is reached, put 1 value as Q
            for(int i=0; i<n; i++)
            {
                string rowString="";
                for(int j=0;j<n;j++)
                {
                    if(visited[i][j] == true)
                    {
                        rowString = rowString + 'Q';
                    }
                    else
                    {
                        rowString = rowString + '.';
                    }
                }
                solution.push_back(rowString);
            }
            ans.push_back(solution);
            return true;
        }

        for(int j=0; j<n; j++)
        {
            if(isFeasible(visited, row, j, n))
            {
                visited[row][j] = true;
                //cout << "visited "<<row<<" "<<j<<endl;
                backTrack(visited, n, row+1, ans);
                // backtrack, given that we want to return all solutions
                // so, not returning if backTrack returns true
                // if question was to find if N queen is possible, then 
                // we could have returned true from here itself, optimizing the solution
                //cout << "unvisited "<<row<<" "<<j<<endl;
                visited[row][j] = false;
            }
        }

        return false;
    }

    vector<vector<string>> solveNQueens(int n) {
        /*
        Approach: Backtracking solution
        for each row,
            - place a queen at each position/column
                - if feasible
                    - then try same for next row through recursion function
                - if exit_code of recursion is true, that means we have reached to final solution
                    - ans answer is already inserted when visiting last row
                    - no op
                - if exit_code of recursion is false, then backtrack by marking node value to false
                // to keep backtrack logic simple, we should backtrack when traversing neighbor node itself, not at start and end of recursion.                
        Time complexity: O(2^N Square)
            - At each position, either position queen or not position
        // perf optimization: no need to maintain visited,
        we can simply check conditions with Q and .
        but having visited is a cleaner code.                
        */

        vector<vector<bool>> visited(n, vector<bool>(n, false));
        vector<vector<string>> ans;
        backTrack(visited, n, 0, ans);

        return ans;
    }
};
