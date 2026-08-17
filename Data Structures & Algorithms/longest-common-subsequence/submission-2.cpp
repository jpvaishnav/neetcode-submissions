class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        /*
        Approach - apply recursion for string of length m, and string of length n
        compare last characters
            - if equal,
                then 1 + recursion for m-1 length, n-1 length
            - else
                pick max of recursion(m-1,n), recursion(m,n-1)
        overlapping subproblems -> DP
        base case:
            if m=0, then dp[0][n] = 0
            if n=0, then dp[m][0] = 0
        dp[i][j] = length of LCS of string s1 of length i, and string s2 of length j
        indexing is on length, so dp[m+1][n+1]
        answer is dp[m][n] -> LCS of length m and length n

        time complexity: O(m*n) time, O(m*n) Aux space

        space optimization:
            dp[i][j] has dependency on current row and previous row
            so can be reduced to 2 rows
            aux space = O(2*n)
        visual at - https://github.com/jpvaishnav/Profile/blob/main/images/dp_lcs_visual.jpg
        */

        // int m = text1.length();
        // int n = text2.length();

        // vector<vector<int>> dp(m+1, vector<int>(n+1,0));

        // // base case is already initialized as part of vector initialization

        // for(int i=1; i<=m; i++)
        // {
        //     for(int j=1; j<=n; j++)
        //     {
        //         // i is length, so last index would be i-1
        //         // j is length, so last index would be j-1
        //         if(text1[i-1] == text2[j-1])
        //         {
        //             dp[i][j] = 1 + dp[i-1][j-1];
        //         }
        //         else
        //         {
        //             dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        //         }
        //     }
        // }

        // return dp[m][n];

        int m = text1.length();
        int n = text2.length();

        vector<int> prev(n+1,0);
        vector<int> curr(n+1,0);

        // base case is already initialized as part of vector initialization

        for(int i=1; i<=m; i++)
        {
            prev[0] = 0;
            curr[0] = 0;
            for(int j=1; j<=n; j++)
            {
                // i is length, so last index would be i-1
                // j is length, so last index would be j-1
                if(text1[i-1] == text2[j-1])
                {
                    //dp[i][j] = 1 + dp[i-1][j-1];
                    curr[j] = 1 + prev[j-1];
                }
                else
                {
                    //dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                    curr[j] = max(prev[j], curr[j-1]);
                }
            }
            prev = curr;
        }

        return curr[n];
    }
};
