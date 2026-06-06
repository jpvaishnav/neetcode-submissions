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
    vector<vector<int>> levelOrder(TreeNode* root) {
        // line by line level order traversal

        queue<TreeNode*> q;
        vector<vector<int>> ans;
        // can this condition improve run time?
        if(root == NULL)
        {
            return ans;
        }
        if(root != NULL)
        {
            q.push(root);
        }

        while(q.empty() == false)
        {
            int n = q.size();
            // size of current level

            // current level container
            vector<int> curr;

            for(int i = 0; i < n ; i++)
            {
                TreeNode* t = q.front();
                q.pop();
                if(t->left !=NULL)
                {
                    q.push(t->left);
                }
                if(t->right !=NULL)
                {
                    q.push(t->right);
                }
                // add current node in current level
                curr.push_back(t->val);
            }
            ans.push_back(curr);
        }

        return ans;
    }
};
