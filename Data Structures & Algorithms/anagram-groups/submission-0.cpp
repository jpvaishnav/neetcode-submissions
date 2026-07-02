class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        /*
        Create an unordered_map(hash table) of <string, vector<string>>
        string would be sorted version of string,
        and vector<string> would contain remaining anagrams
        - go through all strings, sort each and find if it exists in Map
        - if yes, then append in existing list, else create a new list
        O(N*m*logm) N = total strings, m = length of each string
        using hash table, which provides find, insert in O(1)

        Can we find better solution using character map?
        Compute character map of each string, compare with remaining with N-1 strings
        O(N* 255) for 1 string comparison
        and do it N times = O(N*N*255)
        */

        unordered_map<string, vector<string>> hashTable;
        for(auto str: strs)
        {
            string originl_string = str;
            sort(str.begin(), str.end());
            if(hashTable.find(str) == hashTable.end())
            {
                // sorted string is not present in hash table
                vector<string> temp;
                temp.push_back(originl_string);
                hashTable[str] = temp;
            }
            else
            {
                hashTable[str].push_back(originl_string);
            }
        }

        // traverse all, and put them in final ans
        vector<vector<string>> anagrams;
        for(auto itr=hashTable.begin(); itr!=hashTable.end(); itr++)
        {
            anagrams.push_back(itr->second);
        }
        return anagrams;
    }
};
