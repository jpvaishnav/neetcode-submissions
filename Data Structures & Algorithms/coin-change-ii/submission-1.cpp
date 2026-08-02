class Solution {
public:
    int change(int amount, vector<int>& coins) {
        /*
        Har written in coin change 1
        Similar to question: number of ways to make amount
                - which uses 2 dimensionsal DP[N+1][Sum+1]
                - Include-exclude pattern
                at given index i, with total sum
                include ith element in combination,
                    remaining sum = sum - arr[i]
                exclude ith element,
                    sum, i-1
                - Top down similar to LCS
                - Recursion -> overlapping subproblems -> DP
                - Tabulation
                dp[n+1][s+1]
                if s = 0, then dp[i][0] = 1;
                if n = 0, then dp[0][j] = 0;
                dp[i][j] = dp[i-1][j] + dp[i][j-arr[i-1]]
        Visuals in textbook solution
        */

        int n = coins.size();
        int dp[n+1][amount+1];

        for(int i=0; i<=n; i++)
        {
            dp[i][0] = 1;
        }

        for(int j=1; j<=amount; j++)
        {
            dp[0][j] = 0;
        }

        for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=amount; j++)
            {
                if(j-coins[i-1] >= 0)
                {
                    dp[i][j] = dp[i-1][j] + dp[i][j-coins[i-1]];
                }
                else
                {
                    dp[i][j] = dp[i-1][j];
                }
            }
        }

        return dp[n][amount];
    }
};
