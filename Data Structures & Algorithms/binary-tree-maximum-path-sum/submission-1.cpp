/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

class Solution {
public:

    int preOrder(TreeNode* root, int & maxPathSum)
    {
        if(root == NULL)
        {
            return 0;
        }
        int left_subtree_sum = preOrder(root->left, maxPathSum);
        int right_subtree_sum = preOrder(root->right, maxPathSum);
        int root_sum = root->val;
        root_sum = max(root_sum, root_sum + left_subtree_sum);
        root_sum = max(root_sum, root_sum + right_subtree_sum);
        //root_sum = max(0, root_sum); do we need this? without this, it works for -ve also

        maxPathSum = max(maxPathSum, root_sum);

        return max(root->val, root->val + max(left_subtree_sum, right_subtree_sum));
    }
    int maxPathSum(TreeNode* root) {
        /*
        Approach: Standard In-order traversal with maintaining 2 variables
            - maintain variable maxPathSum in function parameters
                - and update it like this-
                maxPathSum = max(maxPathSum, root + left_sum + right_sum)
                // including root in path
                left_sum is returned from recursive call
                right_sum is returned from recursive call

                function returns max sum of chain including root
                    max(root, 0, root+left_sum, root + right_sum)
                    why 0: if sum is negative: exclude it
            Time complexity: O(N), 1 traversal
            Can we improve this?
            Pattern: Maintaining ans in function parameter and returning value in function return in tree traversal
        */

        int max_sum = INT_MIN;
        preOrder(root, max_sum);
        // if all elements are negative, then 
        return max_sum;
    }
};
