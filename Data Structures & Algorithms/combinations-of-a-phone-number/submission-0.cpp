class Solution {
public:
    unordered_map<char, string> mappedChars;

    void initiateMap()
    {
        mappedChars['2'] = "abc";
        mappedChars['3'] = "def";
        mappedChars['4'] = "ghi";
        mappedChars['5'] = "jkl";
        mappedChars['6'] = "mno";
        mappedChars['7'] = "pqrs";
        mappedChars['8'] = "tuv";
        mappedChars['9'] = "wxyz";
    }

    string getMappedCharacters(char c)
    {
        return mappedChars[c];
    }

    void traverse(vector<string> & ans, 
                string solution,
                string & digits,
                int p, int n)
    {
        if(p==n)
        {
            ans.push_back(solution);
            return;
        }

        string letters = getMappedCharacters(digits[p]);
        for(auto c: letters)
        {
            traverse(ans, solution + c, digits, p+1, n);
        }
        return;
    }

    vector<string> letterCombinations(string digits) {
        /*
        Approach: Backtracking traversal
        leaf of node will be answer
        keep a pointer p on digits string
        when p == n, then leaf node, and include in answer
        otherwise get all 3 mapped characters for given digit at digits[p]
            and put each character at end of string
            and remove // backtrack
        */

        vector<string> ans;
        string solution = "";
        int n = digits.size();
        if(n==0)
        {
            return ans;
        }
        initiateMap();
        traverse(ans, solution, digits, 0, n);

        return ans;
    }
};
