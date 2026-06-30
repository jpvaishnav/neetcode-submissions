class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        
        /*
        Approach: Naive solution would be O(N3)
        fixing one pointer a at arr[i],
        then b is fixed between j = i+1 to j = n-2;
        then c is fixed between k = j+1 to k = n-1;
        and we check each time if a + b + c = 0;
        if yes, then add in answer, and in the end remove duplicate ones 
        */

        /*
        Optimized solution: Given that modifying the array is allowed
        so we can sort the array in O(NlogN)
        Then fix a pointer at arr[i].
        Now between range of i + 1 to n-1 (which is sorted segment)
        apply 2 pointer techniques, and find if any p1 + p2 == -arr[i]
        if found, then move in both directions p1++, p2-- to find more combinations
        Derived from example: [-1,0,1,2,-1,-4] + From Naive + 2 pointer
        O(N2) time complexity
        */

        vector<vector<int>> ans;
        if(nums.size() < 3)
        {
            return ans;
        }

        sort(nums.begin(), nums.end());

        int n = nums.size();
        for(int i = 0; i <= n-3; i++)
        {
            int a = nums[i];
            int target = (-1)*(a); // a - 2*a// which is -a
            int j = i+1;
            int k = n-1;
            while(j < k) // not equal sign, because we want distinct numbers
            {
                int sum = nums[j] + nums[k];
                if(sum == target)
                {
                    vector<int> temp;
                    temp.push_back(nums[i]);
                    temp.push_back(nums[j]);
                    temp.push_back(nums[k]);
                    ans.push_back(temp);
                    j++;
                    k--;
                }
                else if(sum < target)
                {
                    j++;
                }
                else
                {
                    k--;
                }
            }
        }

        // filter out unique arrays from ans
        // create hashMap<string, bool>
        // represent each a,b,c as abc [since our selected pairs are already sorted]
        // so, sorted means there wont be duplicate pairs like -1,0,1 and 1,0,-1. because they will be covered by -1,0,1
        // still if array has multiple 0s and 1s, they would be fetched twice
        // eg: -1, 0, 0, 1, 1 => -1,0,1 and -1,0,1 based on above algorithm
        // so, detect them using map of string

        unordered_set<string> uniqueTriplets;
        vector<vector<int>> uniqueAns;
        for(auto triplet: ans)
        {
            string s = to_string(triplet[0]) + to_string(triplet[1]) + to_string(triplet[2]);
            if (uniqueTriplets.find(s) == uniqueTriplets.end())
            {
                uniqueAns.push_back(triplet);
                uniqueTriplets.insert(s);
            }
            // otherwise, it is duplicate, ignore
        }

        return uniqueAns;
    }
};
