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
    vector<int> rightSideView(TreeNode* root) {
        vector<int> rightViewNodes;
        queue<TreeNode*> q;
        if(root!=NULL)
        {
            q.push(root);
        }
        while(!q.empty())
        {
            // size of current level
            int n = q.size();
            for(int i = 0; i<n; i++)
            {
                TreeNode* t = q.front();
                q.pop();
                if (i == n-1)
                {
                    rightViewNodes.push_back(t->val);
                }
                if(t->left !=NULL)
                {
                    q.push(t->left);
                }
                if(t->right!=NULL)
                {
                    q.push(t->right);
                }
            }
        }
        return rightViewNodes;
    }
};
