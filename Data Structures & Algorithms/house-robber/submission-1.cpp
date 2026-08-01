class Solution {
public:
    int rob(vector<int>& nums) {
        /*
        Approach:
            Similar to fibonacci
            overlapping subproblems
            dp[i] = amount robbed by including ith house
                - so dp[i] = arr[i] + dp[i-2];
                - bottom up tabulation
            ans would be max of all DPs
            can be optimized to 2 variables in O(1) aux space
            dry run on examples

            updated dp conditions after failure case
            nums=[5,1,2,10,6,2,7,9,3,1]
            dp[i] = max robbed amount till ith element
            dp[i] = max(arr[i] + dp[i-2], dp[i-1])
                // pattern: include-exclude approach
                // include ith element or exclude ith element
        */

        int n = nums.size();
        if(n==0)
        {
            return 0;
        }
        if(n==1)
        {
            return nums[0];
        }
        int dp[n];
        dp[0] = nums[0];
        dp[1] = max(dp[0], nums[1]);
        for(int i=2; i<n; i++)
        {
            dp[i] = max(nums[i] + dp[i-2], dp[i-1]);
        }
        return dp[n-1];
    }
};
