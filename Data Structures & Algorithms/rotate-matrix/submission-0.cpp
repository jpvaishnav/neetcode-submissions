class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        /*
        Approach: pattern based on one of previous solved problem.
            - where in rotation, reverse operations were used 2 times
        Same here as well
        first reverse all rows or columns
        then apply diagonal swapping
        Time;O(n square)
        Space: O(1)
        */

        int n = matrix.size();

        // reverse all columns
        for(int col=0; col<n; col++)
        {
            for(int row=0; row<n/2; row++)
            {
                //swap arr[row][col] and arr[n-row-1][col]
                int temp = matrix[row][col];
                matrix[row][col] = matrix[n-row-1][col];
                matrix[n-row-1][col] = temp;
            }
        }

        // now perform diagonal swapping
        // arr[i][j], arr[j][i]

        for(int row=0; row<n; row++)
        {
            for(int col=0; col<row; col++)
            {
                int temp = matrix[row][col];
                matrix[row][col] = matrix[col][row];
                matrix[col][row] = temp;
            }
        }
    }
};
