class Solution {
public:

    bool allElementsNegative(vector<int> & nums, int n, int & neg_max)
    {
        for(int i=0; i<n; i++)
        {
            if(nums[i]>=0)
            {
                return false;
            }
            if(nums[i]>neg_max)
            {
                neg_max=nums[i];
            }
        }
        return true;
    }
    int maxSubArray(vector<int>& nums) {
        /*
        Approach: Standard Kadane algorithm
        Have to include element at index i,
            - with 2 options
                - include only ith element
                - include ith element with previous window
        at index i,
            - if curr_sum + arr[i] < 0
                - it means arr[i] inclusion is making ans negative
                so with this combination, future subarrays will also be non optimal
                so, drop curr_sum
                and arr[i] is also negative
                so, drop arr[i] as well, and start fresh with curr_sum=0
                set ans
        What is greedy in this algo?
            - at point i, there are 2 paths,
                - and being greedy, the optimized path is picked
                that is when curr_sum holds positive value with arr[i]
        */

        int n = nums.size();
        if(n==0)
        {
            return 0;
        }
        int neg_max=INT_MIN;
        // kadane does not work, if all elements are negative, so in that case, return max
        if(allElementsNegative(nums, n, neg_max))
        {
            return neg_max;
        }

        int curr_sum=0;
        int ans = 0;
        for(int i=0; i<n; i++)
        {
            if(curr_sum + nums[i] < 0)
            {
                curr_sum = 0;
            }
            else
            {
                curr_sum = curr_sum + nums[i];
            }
            ans = max(ans, curr_sum);
        }

        return ans;
    }
};
