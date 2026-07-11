class Solution {
public:

    bool isValidParanthesis(string & s)
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

    void generate(string p, int i, int & max_chars, vector<string> &ans, int & opening_brackets, int & closing_brackets)
    {
        if(closing_brackets > opening_brackets)
        {
            return;
        }
        if(i==max_chars)
        {
            if(isValidParanthesis(p))
            {
                ans.push_back(p);
            }
            return;
        }

        // at i, choose both ( and )
        opening_brackets++;
        generate(p+'(', i+1, max_chars, ans, opening_brackets, closing_brackets);
        opening_brackets--;
        closing_brackets++;
        generate(p+')', i+1, max_chars, ans, opening_brackets, closing_brackets);
        closing_brackets--;
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
        
        optimize by cutting invalid branches
        maintain count of opening and closing bracket
        - if at any point, if closing brackets are greater than opening bracket
        then entire tree branch is invalid solution
        example: ((()))) -> further child would also be invalid
        ()) -> childs would be invalid
        */
        vector<string> ans;
        int max_chars = 2*n;
        int opening_brackets = 0;
        int closing_brackets = 0;
        generate("", 0, max_chars, ans, opening_brackets, closing_brackets);

        return ans;
    }
};
