class Solution {
public:
    const vector<string> mapperCharsArray = {"", "", "abc",
                                            "def", "ghi", "jkl", "mno", "pqrs",
                                            "tuv", "wxyz"};

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
                string & solution,
                string & digits,
                int p, int n)
    {
        if(p==n)
        {
            ans.push_back(solution);
            return;
        }

        //string letters = getMappedCharacters(digits[p]);
        int index = digits[p]-'0';
        string letters = mapperCharsArray[index];
        for(auto c: letters)
        {
            solution[p] = c;
            traverse(ans, solution, digits, p+1, n);
            //traverse(ans, solution + c, digits, p+1, n);
            solution[p] = ' '; //backtrack
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

        Time complexity: O(3^n)
        optimization: by passing string as reference,
        although string as reference is a cleaner code here
        - 
        */

        vector<string> ans;
        int n = digits.size();
        if(n==0)
        {
            return ans;
        }
        
        string solution = "";
        for(int i=0; i<n; i++)
        {
            solution = solution + ' ';
        }
        //initiateMap();
        traverse(ans, solution, digits, 0, n);

        return ans;
    }
};
