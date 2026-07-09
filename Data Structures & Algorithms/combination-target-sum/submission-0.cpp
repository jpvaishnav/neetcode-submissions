class Solution {
public:
    void backTrack(vector<int> & nums, int i,
                    int target, int curr_sum,
                    vector<int> & curr_solution,
                    vector<vector<int>> & ans)
    {
        if(curr_sum == target)
        {
            ans.push_back(curr_solution);
            // given that all elements are positive, so we can return from here
            // no further solution possible
            return;
        }

        if(curr_sum > target)
        {
            return;
        }

        if(i >= nums.size())
        {
            return;
        }

        // include ith element in solution
        //curr_sum += nums[i]; added directly to function
        curr_solution.push_back(nums[i]);
        backTrack(nums, i, target, curr_sum + nums[i], curr_solution, ans);
        curr_solution.pop_back();

        backTrack(nums, i+1, target, curr_sum, curr_solution, ans);
    }

    vector<vector<int>> combinationSum(vector<int>& nums, int target) {
        /*
        Approach: pattern seems similar to include-exclude approach
        and we need to maintain solution array as well
        at any given index, we have 2 options-
            include index element in current sum,
                Add element in solution array
                and recursion for same index
                remove element from solution array (backtrack)
            and exclude index element
                // no change in solutio array
                and recursion for next index
        base cases-
            1. when sum is equal to target
            2. when sum is greater than target
            3. when index has reached n
        */
        vector<int> curr_solution;
        vector<vector<int>> ans;
        backTrack(nums, 0, target, 0, curr_solution, ans);

        return ans;
    }
};
