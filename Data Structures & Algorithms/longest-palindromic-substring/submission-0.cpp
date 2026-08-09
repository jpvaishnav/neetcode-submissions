class Solution {
public:
    string longestPalindrome(string s) {
        /*
        Approach:
            is it variation of LCS: NO
                - LCS is subsequence, but this is substring
            Apply top down recursive function
            Two conditions:
                s[i] == s[j], then dp[i][j] = 2 + dp[i+1][j-2](if this value is not default/-1)
                s[i] != s[j], then dp[i][j] = 0
            base case:
                2 diagonals
                when string length is 1
                when string length is 2
            
            start dp computation from string length = 3 or gap = 2
            maintain max palindrome length as answer, and also maintain start and end index(i,j), which will be used in the end to return ans

            time complexity: O(n*n)
            Aux space: O(n*n)
        */

        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        // base case, length =1
        for(int i=0; i<n; i++)
        {
            dp[i][i] = 1;
        }
        //initialise ans:
        int max_length = 1;
        int ans_i = 0;
        int ans_j = 0;

        for(int i=0; i+1<n; i++)
        {
            if(s[i] == s[i+1])
            {
                dp[i][i+1] = 2;
                max_length = 2;
                ans_i = i;
                ans_j = i+1;
            }
            // else is no-op, dp[i][i+1] is 0 by default
        }

        for(int gap=2; gap<n; gap++)
        {
            for(int i=0; i+gap < n; i++)
            {
                int j = i+gap;
                if(s[i] != s[j])
                {
                    dp[i][j] = 0;
                    // this is no-op, it's zero by default
                }
                else
                {
                    if(dp[i+1][j-1] > 0)
                    {
                        dp[i][j] = 2 + dp[i+1][j-1];
                        if(dp[i][j] > max_length)
                        {
                            max_length = dp[i][j];
                            ans_i = i;
                            ans_j = j;
                        }
                    }
                    // else , dp[i][j] is 0, no-op
                }
            }
        }

        string lps="";
        for(int ind=ans_i; ind<=ans_j; ind++)
        {
            lps = lps + s[ind];
        }

        return lps;
    }
};
