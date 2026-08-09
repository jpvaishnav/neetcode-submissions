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

            need optimization: 64 ms time

            Asking for optimization hint to AI

Your current dynamic programming approach runs in O(n²) time and uses O(n²) space.
To optimize this code further, consider these two sequential hints depending on what you want to improve:
## Hint 1: Optimizing Space from O(n²) to O(1) (Simplest Optimization)
Look closely at how a palindrome grows. A palindrome is completely symmetric around its center. Instead of building a table from the outside-in (like DP), think about what happens if you pick a single character (or a pair of characters) and try to expand outwards as far as possible.

* Pattern: Two-Pointers / Center Expansion.
* Impact: Keeps the O(n²) time but drops your space complexity to O(1) auxiliary space.

## Hint 2: Optimizing Time from O(n²) to O(n) (Ultimate Optimization)
If your goal is to beat the 64 ms runtime drastically, you need a linear time algorithm. There is a specialized string algorithm that builds upon the "center expansion" idea but uses information from previously found palindromes (mirroring) to skip redundant character comparisons entirely.

* Pattern / Algorithm: Manacher's Algorithm.
* Impact: Drops the time complexity to a blazing-fast O(n).

------------------------------
💡 Which optimization path do you want to explore first? If you choose one, I can provide a conceptual breakdown of how it works without giving you any code!


        */

        // int n = s.size();
        // vector<vector<int>> dp(n, vector<int>(n, 0));
        // // base case, length =1
        // for(int i=0; i<n; i++)
        // {
        //     dp[i][i] = 1;
        // }
        // //initialise ans:
        // int max_length = 1;
        // int ans_i = 0;
        // int ans_j = 0;

        // for(int i=0; i+1<n; i++)
        // {
        //     if(s[i] == s[i+1])
        //     {
        //         dp[i][i+1] = 2;
        //         max_length = 2;
        //         ans_i = i;
        //         ans_j = i+1;
        //     }
        //     // else is no-op, dp[i][i+1] is 0 by default
        // }

        // for(int gap=2; gap<n; gap++)
        // {
        //     for(int i=0; i+gap < n; i++)
        //     {
        //         int j = i+gap;
        //         if(s[i] != s[j])
        //         {
        //             dp[i][j] = 0;
        //             // this is no-op, it's zero by default
        //         }
        //         else
        //         {
        //             if(dp[i+1][j-1] > 0)
        //             {
        //                 dp[i][j] = 2 + dp[i+1][j-1];
        //                 if(dp[i][j] > max_length)
        //                 {
        //                     max_length = dp[i][j];
        //                     ans_i = i;
        //                     ans_j = j;
        //                 }
        //             }
        //             // else , dp[i][j] is 0, no-op
        //         }
        //     }
        // }

        // string lps="";
        // for(int ind=ans_i; ind<=ans_j; ind++)
        // {
        //     lps = lps + s[ind];
        // }

        // return lps;

        // applying O(1) aux space solution by using centre expansion technique
        // pick ith character
            // keep ith at centre and grow in both sides using two pointer
            // keep ith and i+1th(if equal) at central and keep growing in both sides using two pointers

            int n = s.size();

            int max_len=0;
            int ans_i=0;
            int ans_j=0;

            for(int i=0; i<n; i++)
            {
                cout<<"Index "<<i<<endl;
                // ith at centre
                int left = i-1;
                int right = i+1;
                int curr_len=1;
                while(left >=0 && right<n)
                {
                    if(s[left] == s[right])
                    {
                        curr_len = curr_len + 2;
                        //cout<<"curr_len at index i "<<curr_len<<endl;
                        if(curr_len > max_len)
                        {
                            max_len = curr_len;
                            ans_i = left;
                            ans_j = right;
                        }

                        left--;
                        right++;
                    }
                    else
                    {
                        break;
                    }
                }

                // ith and i+1th at centre
                if(i+1<n && s[i] == s[i+1])
                {
                    curr_len=2;
                    //cout<<"curr_len at index i "<<curr_len<<endl;
                    // for length =2, set ans
                    if(curr_len > max_len)
                    {
                        max_len = curr_len;
                        ans_i = i;
                        ans_j = i+1;
                    }

                    left = i-1;
                    right =i+2;
                    while(left >=0 && right<n)
                    {
                        if(s[left] == s[right])
                        {
                            curr_len = curr_len + 2;
                            if(curr_len > max_len)
                            {
                                max_len = curr_len;
                                ans_i = left;
                                ans_j = right;
                            }

                            left--;
                            right++;
                        }
                        else
                        {
                            break;
                        }
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
