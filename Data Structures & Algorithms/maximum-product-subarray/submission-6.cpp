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

        - derived optimal solution by example, dry run of pattern across test cases
        - and concept of min and max range, which gets amplified by incoming new element
        visuals at https://github.com/jpvaishnav/Profile/blob/main/images/dp_max_prod_subarray_1.jpg
        https://github.com/jpvaishnav/Profile/blob/main/images/dp_max_prod_subarray_2.jpg

        https://github.com/jpvaishnav/Profile/blob/main/images/dp_max_prod_subarray_3.jpg

time complexity: O(n), space: O(1)
can we optimize further?

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
            int curr_max_prod = nums[i];
            int curr_min_prod = nums[i];
            if(nums[i]>0)
            {
                //curr_max_prod =  max(nums[i], max_prod * nums[i]);
                //curr_min_prod =  min(nums[i], min_prod * nums[i]);
                if(max_prod * nums[i] > nums[i])
                {
                    curr_max_prod = max_prod * nums[i];
                }
                if(min_prod * nums[i] < nums[i])
                {
                    curr_min_prod = min_prod * nums[i];
                }
                //ans = max(ans, curr_max_prod);
                
            }
            else
            {
                //curr_max_prod = max(nums[i], nums[i] * min_prod);
                //curr_min_prod = min(nums[i], nums[i] * max_prod);
                //cout << i << " "<<curr_min_prod << " "<<curr_max_prod << endl;
                //ans = max(ans, curr_max_prod);

                if(nums[i] * min_prod > nums[i])
                {
                    curr_max_prod = nums[i] * min_prod;
                }
                if(nums[i] * max_prod < nums[i])
                {
                    curr_min_prod = nums[i] * max_prod;
                }
            }
            if(curr_max_prod > ans)
            {
                ans= curr_max_prod;
            }
            min_prod = curr_min_prod;
            max_prod = curr_max_prod;
        }

        return ans;
    }
};
