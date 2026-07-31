class TrieNode
{
    public:
    bool isEnd;
    TrieNode* child[26];

    TrieNode()
    {
        isEnd = false;
        for(int i=0; i<26; i++)
        {
            child[i] = NULL;
        }
    }
};

class PrefixTree {
public:
    /*
    Approach: 
        Create a TrieNode() class with 2 properties
            - isEnd = true or false
            - child array of TrieNode of 26 length
                - given that lowercase alphabet chars
        Search - O(input length)
        Insert - O(input length)
        isPrefix - O(input prefix length)
    
    How to fit TrieNode() class here?
        - create seperate class TrieNode and use that in PrefixTree() constructor
        - or consider PrefixTree() itself a node?
            - every node can't have search/insert/prefix functions

    */
    TrieNode* root;
    PrefixTree() {
        root = new TrieNode();
    }
    
    void insert(string word) {
        TrieNode* curr = root;
        int wordLength = word.length();
        for(int i=0; i<wordLength; i++)
        {
            int childIndex = word[i] - 'a';
            if(curr->child[childIndex] == NULL)
            {
                curr->child[childIndex] = new TrieNode();
            }
            curr = curr->child[childIndex];
        }
        curr->isEnd = true;
    }
    
    bool search(string word) {
        TrieNode* curr = root;
        int wordLength = word.length();
        for(int i=0; i<wordLength; i++)
        {
            int childIndex = word[i] - 'a';
            if(curr->child[childIndex] == NULL)
            {
                return false;
            }
            curr = curr->child[childIndex];
        }
        return (curr->isEnd == true);
    }
    
    bool startsWith(string prefix) {
        TrieNode* curr = root;
        int prefixLength = prefix.length();
        for(int i=0; i<prefixLength; i++)
        {
            int childIndex = prefix[i] - 'a';
            if(curr->child[childIndex] == NULL)
            {
                return false;
            }
            curr = curr->child[childIndex];
        }
        return true;
    }
};
