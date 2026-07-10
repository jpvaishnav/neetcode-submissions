class Solution {
public:

    void backTrack(vector<int>& nums,
                vector<vector<int>> & ans,
                vector<int> & solution,
                int i,
                int n)
    {
        if(i==n)
        {
            return;
        }

        // include ith
        // given array has unique integars,
        // it had duplicate integars, then we might have to check element existence using hash table in O(1)
        solution.push_back(nums[i]);
        // mark as visited, putting at start creates duplicate subsets
        ans.push_back(solution);
        backTrack(nums, ans, solution, i+1, n);
        solution.pop_back();

        // exclude ith
        backTrack(nums, ans, solution, i+1, n);

        return;
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        /*
        Approach: Include-exclude pattern with backtracking to maintain solution
        similar to combination sum problem we solved earlier
        algo:
        at pointer i,
            - include ith element in solution subset
                - recursion for (i+1)th element
            - exclude ith element from solution subset
                - recusion for (i+1)th element
            - at start of traversal function, put solution subset in in final ans
        base case/breaking condition:
            - when pointer == n

        */

        vector<vector<int>> ans;
        vector<int> solution;
        ans.push_back(solution); //insert empty element
        int n = nums.size();
        backTrack(nums, ans, solution, 0, n);

        return ans;
    }
};
