class Solution {
public:

    bool isValidParanthesis(string s)
    {
        stack<char> st;

        for(auto c: s)
        {
            if(c=='(')
            {
                st.push(c);
            }
            else // closing bracket
            {
                if(st.empty())
                {
                    return false;
                }
                if(st.top()!='(')
                {
                    return false;
                }
                st.pop();
            }
        }
        return st.empty();
    }

    void generate(string p, int i, int max_chars, vector<string> &ans)
    {
        if(i==max_chars)
        {
            if(isValidParanthesis(p))
            {
                ans.push_back(p);
            }
            return;
        }

        // at i, choose both ( and )
        generate(p+'(', i+1, max_chars, ans);
        generate(p+')', i+1, max_chars, ans);
    }

    vector<string> generateParenthesis(int n) {
        /*
        Approach:
        Generate all parantheses possibility with total 2*n characters
        at each position, insert opening bracket ( or closing bracker )
        and move on to next position
        leaf node is answer
            - before inserting leaf node to final ans
            - check isValidParantheses() using stack in O(7)
        */
        vector<string> ans;
        generate("", 0, 2*n, ans);

        return ans;
    }
};
