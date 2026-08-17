class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        /*
        Approach:
            recursive approach is putting 3 pointers i,j,k
                and if s1[i] matches to s3[k], then check 
                    f(i-1,j,k-1)
                        if true, then return true
                else if
                    s2[j] matches to s3[k]
                    then call f(i,j-1,k-1)
                    if true, then return true
                else,
                    return false
            recursion returns whether given string is interleaving or not
            base case:
                when i becomes 0 -> remaining s2 == remaining s3 -> true, else false
                when j becomes 0 -> remaining s1 == remaining s3 -> true, else false
                when k becomes 0 -> both s1, and s2 are remaining, so return false
                dp[0][0][0] is true
            what about the wierd condition of |n-m| <=1
                will it always be maintained automatically through this way of traversal?
                Looks like, need to validate through test case
            recursion -> overlapping subproblem -> dp

            time complexity: O(m*n*(m+n))
            Aux space: O(m*n*(m+n))

            Optimization hint by Gemini:
                is there optimization scope in string interleaving question? just give me hint only, not detailed solution. 

                1. Eliminate the Third Dimension (Time & Space Optimization)Look closely at your pointers: if you have consumed i characters from s1 and j characters from s2, how many characters must you have consumed from s3?Hint: k is not independent. You can entirely eliminate the k loop and the third dimension of your DP table because k is always a direct function of i and j. This brings your time complexity down to \(O(m \times n)\).
        */

        // int m = s1.length();
        // int n = s2.length();
        // int p = s3.length();
        // if(m+n != p)
        // {
        //     return false;
        // }
        // vector<vector<vector<bool>>> dp(m+1, 
        //                             vector<vector<bool>>(n+1, vector<bool>(p+1,false)));
        // dp[0][0][0] = true;
        // // when m is 0
        // for(int j=1; j<=n; j++)
        // {
        //     for(int k=1; k<=p; k++)
        //     {
        //         if(j==k)
        //         {
        //             string sub_s2 = s2.substr(0,j);
        //             string sub_s3 = s3.substr(0,k);
        //             if(sub_s2 == sub_s3)
        //             {
        //                 dp[0][j][k] = true;
        //             }
        //         }
        //         // otherwise already set to false
        //     }
        // }
        // // when n is 0
        // for(int i=1; i<=m; i++)
        // {
        //     for(int k=1; k<=p; k++)
        //     {
        //         if(i==k)
        //         {
        //             string sub_s1 = s1.substr(0,i);
        //             string sub_s3 = s3.substr(0,k);
        //             if(sub_s1 == sub_s3)
        //             {
        //                 dp[i][0][k] = true;
        //             }
        //         }
        //         // otherwise already set to false
        //     }
        // }
        // //when k is 0, and i and j are non zero, its false, which is already set

        // for(int i=1; i<=m; i++)
        // {
        //     for(int j=1; j<=n; j++)
        //     {
        //         for(int k=1; k<=p; k++)
        //         {
        //             // visualise pointers and comparison decision on recursive condition here, because 3d DP is hard to imagine
        //             if(s1[i-1] == s3[k-1])
        //             {
        //                 if(dp[i-1][j][k-1])
        //                 {
        //                     dp[i][j][k] = true;
        //                 }
        //             }

        //             if(s2[j-1] == s3[k-1])
        //             {
        //                 if(dp[i][j-1][k-1])
        //                 {
        //                     dp[i][j][k] = true;
        //                 }
        //             }

        //             // otherwise, it is already false
        //         }
        //     }
        // }

        // return dp[m][n][p];

        // eliminating k pointer
        int m = s1.length();
        int n = s2.length();
        int p = s3.length();
        if(m+n != p)
        {
            return false;
        }
        // it means m+n is equal to p here
        vector<vector<bool>> dp(m+1, vector<bool>(n+1,false));
        dp[0][0] = true;
        // when m is 0, and n is non-zero it will be true, because picking "" from s1 and entire s2 can become s3 if s2 == s3
        for(int j=1; j<=n; j++)
        {
            if(s2[j-1] == s3[j-1] && dp[0][j-1] == true)
            {
                dp[0][j] = true; 
            }
        }
        // when m is 0, and n is non-zero it will be true, because picking "" from s2 and entire s1 can become s3 if s1 == s3
        for(int i=1; i<=m; i++)
        {
            if(s1[i-1] == s3[i-1] && dp[i-1][0] == true)
            {
                dp[i][0] = true;
            }
        }

        for(int i=1; i<=m; i++)
        {
            for(int j=1; j<=n; j++)
            {
                int k = i+j;
                // visualise recursive function decision here
                // combination matching to s1
                if(s1[i-1] == s3[k-1])
                {
                    if(dp[i-1][j])
                    {
                        dp[i][j] = true;
                    }
                }

                if(s2[j-1] == s3[k-1])
                {
                    if(dp[i][j-1])
                    {
                        dp[i][j] = true;
                    }
                }
                // otherwise, it is already false
            }
        }

        return dp[m][n];
    }
};
