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

    void countGoodNodes(TreeNode* root, int max_ancestors, int & goodNodes)
    {
        if(root == NULL)
        {
            return;
        }

        if(root->val >= max_ancestors)
        {
            goodNodes++;
            max_ancestors = root->val;
        }
        countGoodNodes(root->left, max_ancestors, goodNodes);
        countGoodNodes(root->right, max_ancestors, goodNodes);
    }

    int goodNodes(TreeNode* root) {
        /*
        Approach: tree traversal:
        Root -> left -> right : PreOrder/DFS
        How to check if root->val is greater than all ancestors
        option1: Pass a vector of ancestors, and check with O(N) time
        option2: Pass a max heap of ancestors and check with O(logN) time
        option3: Pass max value of ancestors and check with O(1) time
        at root, 
            - first check goodness criteria and increment count if
                - root->val > max_ancestors
            - pass max value of ancestors for both left and right subtree
                - in recursive calls of preorder
        */

        int max_ancestors = INT_MIN;
        int goodNodes = 0;
        countGoodNodes(root, max_ancestors, goodNodes);
        return goodNodes;
    }
};
