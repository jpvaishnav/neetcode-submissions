class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        /*
        Approach:
            Similar to question: number of ways to make amount
                - which uses 2 dimensionsal DP[N+1][Sum+1]
                - Include-exclude pattern
                - similar can also be used here
                - take min of 2 options
                dp[i][j] = min(1 + dp[i][j-arr[i-1]], dp[i-1][j])
                if(sum==0) {dp[][0] = 1}
                if(n==0) {dp[][0] = INT_MAX; so that}
            
            - Can we use simple 1 dimensional DP here?
            dp[sum] = min(1 + dp[sum-arr[0]], 1 + dp[sum-arr[1]], ...., 1 + dp[sum-arr[n-1]])
            - initialize all array values x to dp[x] = 1
            - given that an element can be included multiple times
                - similar to rope cut recursion problem
                f(n) = min(f(n-a), f(n-b), f(n-c))
            
            time complexity: O(amount * coins)
            Aux space: O(amount) in 1-d, O(amount*coins) in 2-d

        */

        int n = coins.size();
        vector<int> dp(amount+1, INT_MAX);
        // given in question, that 0 amount is valid
        dp[0] = 0;

        for(int i=0; i<n; i++)
        {
            int coin = coins[i];
            if(coin <= amount)
            {
                // coing greater than amount is invalid scenerio
                dp[coin] = 1;
            }
        }

        for(int x=1; x<=amount; x++)
        {
            // dp[x] computation
            for(int i=0; i<n; i++)
            {
                int target = x-coins[i];
                if(target >= 0 && dp[target] != INT_MAX)
                {
                    dp[x] = min(dp[x], dp[target] + 1);
                    // including ith coin the ans -> +1
                    // applied dp[target] != INT_MAX for this case
                    // coins=[2]
                    // amount=3
                    // because iNT_MAX +1 would overflow and produce wrong answer
                }
            }
        }

        if(dp[amount] == INT_MAX)
        {
            return -1;
        }

        return dp[amount];
    }
};
