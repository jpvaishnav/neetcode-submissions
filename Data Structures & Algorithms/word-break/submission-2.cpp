class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        /*
        Approach:
            Recursion from last, bottom up
                - f(length n)
                - apply cuts/partitions of valid words from dictionary
                - if any of recursive call return true, then return true
                    - f(n - cut.length) -> return true
                - base case:
                    - recursion terminates when string length becomes 0, return true
                - optimization from cuts/partition,
                    instead of making n-1 cut for n length string
                    - create a hash map of <cutLength, cutString>
                    and apply cut of those lengths only if 
                        cutString == word from dictionary
            overlapping subproblems -> DP
            dp[n]
            dp[i] = true if word break is possible for string of length i, else false
            dp[0] = true, because 0 length string means entire string has been cut by matching partitions
            dp[n] = d[n-x1] || dp[n-x2] || dp[n-x3] || ... 
                where x1, x2, x3 are length of matching cuts 

            Time complexity:
            if m is s.length
            if n is wordDict.length or max number of words
            if p is word.length
            then O(m*n*p)
            Aux space: O(m)

            visuals: https://github.com/jpvaishnav/Profile/blob/main/images/dp_word_break.jpg
        */

        unordered_map<int, vector<string>> lengthWordMap;
        for(auto word: wordDict)
        {
            lengthWordMap[word.length()].push_back(word);
        }

        int n = s.size();
        vector<bool> dp(n+1, false); // length based indexing
        dp[0] = true;
        for(int i=1; i<=n; i++)
        {
            for(auto lengthWordPair: lengthWordMap)
            {
                int length = lengthWordPair.first;
                if(length > i)
                {
                    continue;
                }
                vector<string> words = lengthWordPair.second;
                string string_partition = s.substr(i-length, length);
                // calculate the index by applying length =1, length = 2, ...
                for(auto word: words)
                {
                    if(word == string_partition)
                    {
                        if(dp[i-length] == true)
                        {
                            dp[i] = true;
                            break;
                            // break is an optional optimization here
                            // no more words with this length will be checked
                        }
                    }
                }
            }
        }
        return dp[n];
    }
};
