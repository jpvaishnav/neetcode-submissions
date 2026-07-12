class Solution {
public:
    bool canJump(vector<int>& nums) {
        /*
        Approach: visualisation and dry run on given example
        - traverse each position,
            - jump maximum possible, and mark the max jumped node as reached
            - maintain reached[i] to indicate if ith position is reached
            - to start with, only first position is reached
            - and when jumping next as well,
                - jump from only reached node
        And in the end, check if last position is reached
        what is greedy in this algo:
            tendency to jump max at given position p
        */

        int n = nums.size();
        if(n==0)
        {
            return false;
        }

        vector<bool> reach(n, false);
        reach[0] = true;

        for(int i=0; i<n; i++)
        {
            if(reach[i] == true)
            {
                int max_reach = min(n-1, i+nums[i]);
                // mark every node between i to max_reach as reached
                for(int j=i+1; j<=max_reach; j++)
                {
                    reach[j] = true;
                }
            }
        }

        return reach[n-1];
    }
};
