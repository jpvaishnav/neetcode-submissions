class Solution {
public:

    string compute_hash(string str)
    {
        int count[26] = {0};
        for(char c: str)
        {
            count[c-'a']++;
        }
        string hash_key;
        for(int i=0; i<26; i++)
        {
            hash_key = hash_key + to_string(count[i]) + "#";
            // # is seperator, can be done by a, b, c, but ('a'++) is complex syntax
        }
        return hash_key;
    }

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

        // unordered_map<string, vector<string>> hashTable;
        // for(auto str: strs)
        // {
        //     string originl_string = str;
        //     sort(str.begin(), str.end());
        //     if(hashTable.find(str) == hashTable.end())
        //     {
        //         // sorted string is not present in hash table
        //         vector<string> temp;
        //         temp.push_back(originl_string);
        //         hashTable[str] = temp;
        //     }
        //     else
        //     {
        //         hashTable[str].push_back(originl_string);
        //     }
        // }

        // // traverse all, and put them in final ans
        // vector<vector<string>> anagrams;
        // for(auto itr=hashTable.begin(); itr!=hashTable.end(); itr++)
        // {
        //     anagrams.push_back(itr->second);
        // }
        // return anagrams;

        /*
        Optimization as per hint by copilot.
        Use frequency character map.
        Compute frequency map of 26 characters and convert each string into a hash value.
        for example abc, and acb both will have values in this order-
        11100000000000.....0 (first 1 is count of a, second is count of b)
        -> problem in this approach is if a comes 12 times than string becomes 121... -> now a is 1 or 12?
        Huffman encoding?
        We can simply use a1b1c1d4.....z0 as unique hash key?
        Time complexity: Compute unique key for each string: O(m)
        Hash table calculates hash of this key: O(m) => O(m + m)
        and this is done N times:
        O(N*m) which is better than O(N*m*logm)
        */

        unordered_map<string, vector<string>> hashTable;
        for(auto str: strs)
        {
            string hash_key = compute_hash(str);
            if(hashTable.find(hash_key) == hashTable.end())
            {
                vector<string> temp;
                temp.push_back(str);
                hashTable[hash_key] = temp;
            }
            else
            {
                hashTable[hash_key].push_back(str);
            }
        }

        vector<vector<string>> anagrams;
        for(auto itr=hashTable.begin(); itr!=hashTable.end(); itr++)
        {
            anagrams.push_back(itr->second);
        }
        return anagrams;
    }
};
