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
    int getIndexFromInOrder(vector<int> & inorder, int val)
    {
        for(int i = 0; i < inorder.size(); i++)
        {
            if(inorder[i] == val)
            {
                return i;
            }
        }
        return -1;
    }

    TreeNode* ConstructTreeFromPreAndInorder(int & preIndex, int in_start, int in_end,
                vector<int> & preorder, vector<int> & inorder)
    {
        if (preIndex >= preorder.size())
        {
            return NULL;
        }

        if(in_start > in_end)
        {
            return NULL;
        }

        // preIndex is the root
        TreeNode* newNode = new TreeNode(preorder[preIndex]);
        int in_index = getIndexFromInOrder(inorder, preorder[preIndex]);
        preIndex++;
        newNode->left = ConstructTreeFromPreAndInorder(preIndex, in_start, in_index-1, preorder, inorder);
        newNode->right = ConstructTreeFromPreAndInorder(preIndex, in_index+1, in_end, preorder, inorder);

        return newNode;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        // Call constructTreeFromPreInOrder()
        int preIndex = 0;
        TreeNode* root = ConstructTreeFromPreAndInorder(preIndex, 0, inorder.size()-1, preorder, inorder);
        return root;
    }
};
