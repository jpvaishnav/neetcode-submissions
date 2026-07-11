class Solution {
public:

    void backTrackTillLeaf(vector<int> & nums, 
                vector<vector<int>> & permutations,
                int n,
                int curr_index)
    {
        if(curr_index == n)
        {
            permutations.push_back(nums);
            return;
        }

        for(int j=curr_index; j<n; j++)
        {
            // swap(nums[curr_index], nums[j])
            int curr_val = nums[curr_index];
            int j_val = nums[j];
            nums[curr_index]=j_val;
            nums[j] = curr_val;
            backTrackTillLeaf(nums,permutations, n, curr_index+1);
            nums[curr_index]=curr_val;
            nums[j] = j_val;
        }
    }

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

        Optimizations with Geminin discussion:
            It asked to save leaf node to avoid duplicate calls.
            follow up question: when to choose leaf node vs when to choose internal node
            - if your solution is in journey like subset, then include internal node
            - if your solution is produced in the end, the include leaf node after full processing
            For pointer 1, there are 2 approaches to save a solution. One is we push every state or node in our answer. We did that in subset problem when subset had duplicate entries. Second is, we push only leaf node in answer which we did in subset with unique values, and we did it in N Queen problem, Sudoko problem. So, when should we choose which approach

            The choice between saving every state (internal nodes) or only saving the leaf nodes depends entirely on the definition of a valid solution in your problem's state space tree, not on whether the input has duplicate values.

            1. Save Only Leaf Nodes (Complete State)Choose this approach when a valid solution must include all elements, fill all slots, or reach the maximum depth of the recursion.The Rule: An incomplete or partial state is invalid. You must go all the way to the bottom of the tree to form a complete answer.Why it applies to your examples:Permutations / N-Queens / Sudoku: A partial arrangement (e.g., placing only 2 queens on an \(8\times8\) board, or filling 5 cells of a Sudoku grid) is not a solution. You only have a valid solution when all \(N\) queens are safely placed or all boxes are filled.Subsets of fixed size \(K\): If a problem asks for all subsets of exactly size \(K\), internal nodes of size less than \(K\) are useless. You only collect the node when curr_depth == K.

            2. Save Every State / Internal Nodes (Prefix State)Choose this approach when every intermediate step or partial combination is considered a valid, standalone solution.The Rule: The journey itself is the answer. Every prefix, subset, or path you generate along the way meets the problem's criteria.Why it applies to your examples:Subsets / Power Set: By definition, a power set contains all possible combinations of any length (including the empty set). If your input is [1, 2], the empty set [] is a solution, [1] is a solution, and [1, 2] is a solution. Therefore, every node you step on in the recursion tree is a valid subset, so you save it immediately.

            Updated leaf approach in function backTrackWithLeaf()
            visual image saved at permutations_dryRun.png
        */

        vector<vector<int>> permutations;
        int n = nums.size();

        //traverse(nums,permutations, n, 0, false);
        backTrackTillLeaf(nums, permutations, n, 0);
        return permutations;

    }
};
