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

    int inOrderTillK(TreeNode* root, int & counter, int & k)
    {
        if(root == NULL)
        {
            return -1;
        }
        if(root->left!=NULL)
        {
            int x = inOrderTillK(root->left, counter, k);
            if(x!=-1)
            {
                return x;
            }
        }
        // process root->val;
        counter++;
        if(counter == k)
        {
            return root->val;
        }
        if(root->right!=NULL)
        {
            int x = inOrderTillK(root->right, counter, k);
            if(x!=-1)
            {
                return x;
            }
        }

        return -1;
    }
    int kthSmallest(TreeNode* root, int k) {
        // get inorder sorted array and return arr[k] - O(n)
        // Traverse inorder till reaching K - O(k)
        int counter = 0;
        return inOrderTillK(root, counter, k);
    }
};
