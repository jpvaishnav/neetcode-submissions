class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        /*
        Approach:
        for n length & n-1 th index:
            call recursive functions for all elements index between
                0 to n-2: j
                and if they are smaller than current n-1 th element
                then 
                    get longest increasing subsequence ending at jth index
                    LIS[n-1] = max(LIS[n-1], LIS[j])
        - overlapping subproblems
            LIS[j] has multiple calls in recursion tree
        - use DP
        - tabulation
        LIS[i] = length of longest increasing subsequence ending at index i
        LIS[0] = 1
        answer(longest length) would be max of all
        Time: O(n^2)
        can be optimized to O(nlogN) using tail algorithm
        */

        int n = nums.size();
        if(n<=1)
        {
            return n;
        }
        vector<int> lis(n, 1);
        int ans = 1;
        for(int i=1; i<n; i++)
        {
            for(int j=0; j<i; j++)
            {
                if(nums[i] > nums[j])
                {
                    lis[i]= max(lis[i], 1+lis[j]);
                }
            }
            //cout<< "DEBUG: LIS at index "<<i<<" "<<lis[i]<<endl;
            ans = max(ans, lis[i]);
        }

        return ans;
    }
};
