class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        /*
        Approach: maintain element presence through a hash table
            - use unordered_set as we only need availibility, not index
        First traversal fills above Hash Table
        Second traversal checks for consecutive.
            - visualise consecutive sequence of i, i+1, i+2, i+3, .....i+m
                - if this is a valid solution, then for every element
                    - its previous element(-1) exists in the array
                    - except for first element for which i-1 does not exist
                - so we only check consecutive chain availibility of given element could be starting point of sequence
                - this way we do atmost O(n) traversals, and keep time complexity within O(n)
                    - otherwise if we assume each element as starting point and check consecutive chain
                        (+1, +2, +3,.....), then the method is repeating, and leading to O(N^2) time complexity
        */

        if(nums.size() < 1)
        {
            return 0;
        }

        unordered_set<int> hashTable;
        for(auto num: nums)
        {
            hashTable.insert(num);
        }

        int ans = 1;

        for(auto num: nums)
        {
            if(hashTable.find(num-1) == hashTable.end())
            {
                // initialize num as first point of sequence, and add till num+1, num+2, .. exists
                int curr = 1;
                int element = num;
                while(hashTable.find(element+1)!=hashTable.end())
                {
                    curr++;
                    element++;
                }
                ans = max(ans, curr);
            }
        }

        return ans;
    }
};
