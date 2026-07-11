class Solution {
public:

    void traverse(vector<int> & nums, 
                vector<vector<int>> & permutations,
                int n,
                int curr_index,
                bool original_index_flag)
    {
        if(curr_index==n)
        {
            return;
        }
        if(original_index_flag == false)
        {
            permutations.push_back(nums);
        }
        for(int j=curr_index; j<n; j++)
        {
            // swap(nums[curr_index], nums[j])
            int curr_val = nums[curr_index];
            int j_val = nums[j];
            nums[curr_index]=j_val;
            nums[j] = curr_val;
            traverse(nums,permutations, n, curr_index+1, (j==curr_index));
            nums[curr_index]=curr_val;
            nums[j] = j_val;
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        /*
        Approach:
        Natural method of generic permutations
        3 boxes = [_,_,_]
        place 1 or 2 or 3 in first box
        - if 1 is placed, then arrange [2,3] in last 2 boxes
        - if 2 is places, then arrange [1,2] in last 2 boxes
        - if 3 is places, then arrange [1,2] in last 2 boxes

        Backtracking algo to do it:
            - given current index i,
                - swap each of j =i+1 to j<n with ith element // is is fixed here
                - call for traverse with current index = (i+1)
                - backtrack
            - put incoming state in ans at start of traversal function
            did dry run with [1,2,3]
        */

        vector<vector<int>> permutations;
        int n = nums.size();

        traverse(nums,permutations, n, 0, false);

        return permutations;

    }
};
