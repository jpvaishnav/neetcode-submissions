class Solution {
public:
    int minDistance(string word1, string word2) {
        /*
        Write recursion with top down approach -> 
        Overlapping sub-problems ->
        DP

        m = word1.length(), n = word2.length();
        f(s1,s2,m,n)
            - if last chars match than return f(s1, s2, m-1, n-1)
            - doesn't match
                - perform operation
                1 + min(3 options)
                3 options
                    - insert
                        - inserted s2 current position char at end of s1
                        - length of s2 is reduced by 1
                        - now remaining is f(s1,s2,m, n-1)
                    - delete
                        - delete last chart from s1
                        - length of s1 is reduced by 1, becomes m-1
                        - f(s1,s2, m-1, n)
                    - replace
                        - matching s1 last char with s2 last char
                        - length of both reduced by 1
                        - f(s1, s2, m-1, n-1)
            - create dp with length index
            dp[m+1][n+1]
            dp[m][n] represents min operations needed for s1 of length m, and s2 of length n
            base case is 
                when m=0, dp[0][j] = j
                when n=0, dp[i][0] = i
            ans is dp[m][n]

            can this be optimized further by using 4 variables that are needed in grid?
            (i-1,j-1) (i-1,j)
            (i, j-1)  (i,j)
            O(1) aux space
        */

        int m = word1.length();
        int n = word2.length();
        
        int dp[m+1][n+1];
        for(int i=0; i<=m; i++)
        {
            dp[i][0] = i;
        }
        for(int j=0; j<=n; j++)
        {
            dp[0][j] = j;
        }

        for(int i=1; i<=m; i++)
        {
            for(int j=1; j<=n; j++)
            {
                // i is length of word1
                // j is length of word2
                if(word1[i-1] == word2[j-1])
                {
                    dp[i][j] = dp[i-1][j-1];
                }
                else
                {
                    dp[i][j] = 1 + min(dp[i-1][j],
                                    min(dp[i][j-1], dp[i-1][j-1]));
                }
            }
        }

        return dp[m][n];
    }
};
