class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        /*
        Approach; variation of subset problem
        1. this is not a subset problem, so need to traverse till complete depth in tree, traverse till n = 0, that will be base case
        2. instead of include-exclude the pattern becomes + or - at given element

        recursion:
        f(n, sum):
            f(n-1, sum + arr[n-1]) + f(n-1, sum - arr[n-1])
        base case:
            only when n is zero and Target_Minus_Sum also becomes 0:
                then it is 1,
            else,
                0 if n is zero and target_Minus_Sum becomes 0
            2nd variable represents Target_Minus_Sum
            - if we are picking arr[n-1] as positive val:
                we substract from Target_Minus_Sum
            - if we are picking arr[n-1] as negative val:
                - we add in Target_Minus_Sum
        
        Overlapping subproblems -> DP ->
            dp[n+1][sum+1]
            dp[i][j] = dp[i-1][j-arr[i-1]] + dp[i-1][j+arr[j-1]]
        is sum+1 write choice here?
            no, we need to calculate max possible value of sum in advance to instantiate matrix dimensions
                - is that within int range
                - input constraint:
                    n = 20, nums[i] = 1000
                    so max sum is 20,000
            How to handle negative index of sum?
                if target is -1000?
                can we maintain all negatives beyond max_sum?
                max_sum can be 20,000, 
                    so 20,001 is -1
                    20,002 is -2
                    40,000 is -20,000
                    and when perfoming sum operations,
                    consider numbers greater than 20,000 as negative
                running into index out of range error
                asking AI agent about hint:
                    - Gemini provided about offset based shifting & suggested standard method
                    - but our code argued & applied index check in given code itself
                    - but it timed out
                        - because 20*40,000 = 800000 operations

        */

        int n = nums.size();
        // optimizing max_sum
        int max_sum = 0;
        for(int i=0; i<n; i++)
        {
            max_sum = max_sum + nums[i];
        }
        max_sum = abs(max_sum);
        int max_neg_sum = max_sum * -1;

        if(target > max_sum || target < max_neg_sum)
        {
            return 0;
        }
        //int max_sum = 20000;
        //int max_neg_sum = -20000;
        int max_range = 2*max_sum;
        vector<vector<int>> dp(n+1, vector<int>(max_range+1));
        //int dp[n+1][max_range+1];
        dp[0][0] = 1;
        for(int j=1;j<=max_range; j++)
        {
            dp[0][j] = 0;
        }

        // based on pattern in 2d, traverse in row first order

        for(int i=1; i<=n; i++)
        {
            for(int j=0; j<=max_range; j++)
            {
                //cout << "updating dp "<<i<<" "<<j<<endl;
                int ele = nums[i-1];
                int j_actual = j;
                if(j>max_sum)
                {
                    j_actual = (j-max_sum)*(-1);
                }
                int j_minus_pos_ele = j_actual - ele;
                int j_plus_neg_ele = j_actual + ele;

                dp[i][j] = 0;

                // now decode the new expressions
                if(j_minus_pos_ele <=max_sum && j_minus_pos_ele >=max_neg_sum)
                {
                    if(j_minus_pos_ele < 0)
                    {
                        j_minus_pos_ele = max_sum +(j_minus_pos_ele*-1);
                    }
                    dp[i][j] += dp[i-1][j_minus_pos_ele];
                }
                if(j_plus_neg_ele <=max_sum && j_plus_neg_ele >=max_neg_sum)
                {
                    if(j_plus_neg_ele < 0)
                    {                        
                        // this is also needed, because j_actual can be negative
                        j_plus_neg_ele = max_sum + (j_plus_neg_ele*-1);
                    }
                    dp[i][j] += dp[i-1][j_plus_neg_ele];
                }
                //cout<<"Indexes are "<<j_minus_pos_ele<<" "<<j_plus_neg_ele<<endl;
                // all indexes are positive at this point
                // if(j_minus_pos_ele>=0 && j_minus_pos_ele <=max_range)
                // {
                //     dp[i][j] += dp[i-1][j_minus_pos_ele];
                // }

                // if(j_plus_neg_ele>=0 && j_plus_neg_ele <=max_range)
                // {
                //     dp[i][j] += dp[i-1][j_plus_neg_ele];
                // }

                //dp[i][j] = dp[i-1][j_minus_pos_ele] + dp[i-1][j_plus_neg_ele];
            }
        }
        if(target < 0)
        {
            target = max_sum + (target*-1);
        }
        return dp[n][target];
    }
};
