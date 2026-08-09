class Solution {
public:
    int maxProduct(vector<int>& nums) {
        /*
        Approach:
            negative element stops the max prod subarray,
            but consecutive negative elements are fine, as they gets multiplied
            include-exclude pattern
                - include ith element in product
                    - arr[i] * f(i-1)
                    - since its sub-array so f(i-1) has to end at i-1
                    that means
                    dp[i] = max prod of subarray ending at index i
                        - ending at (ending till)
                    and ans would be max of all dps(similar to LIS)
                - exclude ith element from product
                    - ith element arr[i] is only element in the substring
                - isn't it kadane algorithm?

                Kadane not working for given example:
                    nums=[-2,3,-4]
                Since, negative is contributing factor, 
                    should we solve using min and max
                But, dp[][] seems most standard solution
                write recursion first
                find overlapping sub-problem
                then write tabulation,
                    - if difficulty in tabulation, go for memoization


        */
        int n = nums.size();
        if(n==1)
        {
            return nums[0];
        }

        int max_prod = max(nums[1], nums[1] * nums[0]);
        int min_prod = min(nums[1], nums[1] * nums[0]);
        int ans = max_prod;

        cout << 1 << " "<<min_prod << " "<<max_prod << endl;

        for(int i=2; i<n; i++)
        {
            if(nums[i]>0)
            {
                int curr_max_prod =  max(nums[i], max_prod * nums[i]);
                int curr_min_prod =  min(nums[i], min_prod * nums[i]);
                ans = max(ans, curr_max_prod);
                min_prod = curr_min_prod;
                max_prod = curr_max_prod;
            }
            else
            {
                int curr_max_prod = max(nums[i], nums[i] * min_prod);
                int curr_min_prod = min(nums[i], nums[i] * max_prod);
                //cout << i << " "<<curr_min_prod << " "<<curr_max_prod << endl;
                ans = max(ans, curr_max_prod);
                min_prod = curr_min_prod;
                max_prod = curr_max_prod;
            }

        }

        return ans;
    }
};
