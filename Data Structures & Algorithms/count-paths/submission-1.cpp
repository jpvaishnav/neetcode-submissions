class Solution {
public:
    int uniquePaths(int m, int n) {
        /*
        Approach-
            recursion:
                (i,j) can be reached by (i-1,j) or (i,j-1)
                - make recursion call to both, and add
                - funtion return value is total ways to reach last cell
                - recursion base case is when call reaches to source (0,0)
                    then return 1
                    otherwise return 0
                -> overlapping subproblem -> DP

                dp[m][n]
                // base: dp[0][0] = 1
                // for entire 1st row, the value is 1, because only 1 unique path possible
                // for entire 1st col, the value is 1, because only 1 unique path possible
                dp[i][j] = dp[i-1][j] + dp[i][j-1]
                where dp[i][j] represents possible unique path count
                time:O(m*n)
                aux space:O(m*n)
                    - can be reduced to O(2*n) given that only 2 rows required
        */

        vector<int> prev(n, 1);
        if(m==1)
        {
            return prev[n-1];
        }
        vector<int> curr(n, 0);

        for(int i=1; i<m; i++)
        {
            curr[0] = 1; // 1st col base case
            for(int j=1; j<n;j++)
            {
                //dp[i][j] = dp[i-1][j] + dp[i][j-1];
                // dp[i] is equivalent to curr
                // dp[i-1] is equivalent to prev
                curr[j] = prev[j] + curr[j-1];
            }
            prev = curr;
        }

        return curr[n-1];
    }
};
