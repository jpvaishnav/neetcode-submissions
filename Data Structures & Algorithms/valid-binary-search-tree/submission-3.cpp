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

    void inOrder(TreeNode* root, vector<int> & v)
    {
        if(root == NULL)
        {
            return;
        }

        if(root-> left != NULL)
        {
            inOrder(root->left, v);
        }
        v.push_back(root->val);
        if(root->right != NULL)
        {
            inOrder(root->right, v);
        }
        return;
    }
    bool isValidBST(TreeNode* root) {
        // if(root == NULL)
        // {
        //     return true;
        // }
        // // BST property on root
        // if(root->left!=NULL && root->val <= root->left->val)
        // {
        //     return false; // early exit
        // }

        // if(root->right!=NULL && root-> val >= root->right->val)
        // {
        //     return false; // early exit
        // }

        // // BST propery on left subtree
        // if(isValidBST(root->left) == false)
        // {
        //     return false;
        // }

        // if(isValidBST(root->right) == false)
        // {
        //     return false;
        // }

        // return true;
        // This solution lacks comparing root with all children nodes
        // But doing that would take extra time for each subtree

        // In order traversal should be sorted
        vector<int> v;
        inOrder(root, v);
        for(int i = 1; i < v.size(); i++)
        {
            if( v[i] <= v[i-1])
            {
                return false;
            }
        }
        return true;
    }
};
