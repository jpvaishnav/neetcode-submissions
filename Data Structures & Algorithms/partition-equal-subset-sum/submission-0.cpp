class Solution {
public:
    bool canPartition(vector<int>& nums) {
        /*
        Approach-
            standard recursion, ith pointer at last n-1 element
                - 2 options:
                    - include ith element in subset 1
                    - include ith element in subset 2
                    take or operations of these 2 and return
                - base case:
                    when n = 0,
                        if sum1 of subset1 == sum2 of subset 2
                            return true
                        else,
                            return false
                - f(arr, n, sum1, sum2)
                    f(arr, n-1, sum1 + arr[n-1], sum2)
                    f(arr, n-1, sum1, sum2 + arr[n-1])
                - overlapping subproblems -> DP -> 3 variables
                    - n, sum1, sum2
                    - can be reduced to 2 similar to string interleaving problem
                    because sum1 + sum2 = total_sum in the end, because only 2 partitions
                    - which leads to another conclusion:
                        - target condition;
                            sum1 == sum2
                            and total_sum = sum1 + sum2
                            => sum1 = total_sum/2
                            problem is reduced to find if sum1 exists as subsequence in given array
                            - given n elements, find if given sum subsequence exists?
                                - subset sum dp problem
                                time complexity: O(n*m)
                            - dp[n+1][sum+1]
                            - if sum = 0, then dp[i][0] = true
                            - if n is zero, but sum is non-zero, then false
                            - answer is dp[n][sum]
                            - dp[i][j] = dp[i-1][j-arr[i-1]] || dp[i-1][j]


        */

        int n = nums.size();
        int total_sum = 0;
        for(auto num: nums)
        {
            total_sum += num;
        }

        if(total_sum%2 !=0)
        {
            return false;
            // early exit, odd sum can't be divided in 2 partitions with equal sum of each
        }
        int sum = total_sum/2;
        vector<vector<bool>> dp(n+1, vector<bool>(sum+1));

        // if sum is zero, fill true
        for(int i=0; i<n; i++)
        {
            dp[i][0] = true;
        }

        // if n is zero, sum is non-zero, fill false
        for(int j=1; j<=sum; j++)
        {
            dp[0][j] = false;
        }

        for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=sum; j++)
            {
                // (i-1)the last element becomes part of subset or excluded from subset
                if(j-nums[i-1] >= 0)
                {
                    dp[i][j] = dp[i-1][j-nums[i-1]] || dp[i-1][j];
                }
                else
                {
                    dp[i][j] = dp[i-1][j];
                }

            }
        }

        return dp[n][sum];
    }
};
