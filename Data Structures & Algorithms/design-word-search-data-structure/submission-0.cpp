class TrieNode{
    public:
        bool isEnd;
        TrieNode* child[26];
    
    TrieNode()
    {
        isEnd = false;
        for(int i=0; i<26;i++)
        {
            child[i] = NULL;
        }
    }
};

class WordDictionary {
public:

    /*
    Maintain a TrieNode() data structure
        with isEnd & child[26] properties
        Insert()
            Add word in trie
        Search
            - if dot, then perform DFS search for all non-NULL child nodes
                - use recursive function DFS(TrieNode* root, string word, int index) for this
            - Otherwise check exact childIndex
    */
    TrieNode* root;
    WordDictionary() {
        root = new TrieNode();
    }
    
    void addWord(string word) {
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
    
    bool DFS(TrieNode* curr, string & word, int i, int n)
    {
        if(curr == NULL)
        {
            return false;
        }

        if(i==n)
        {
            return curr->isEnd == true;
            // can return true here directly if prefix search
            // dry run with given example, day satisfied this condition
        }

        if(word[i] == '.')
        {
            for(int j=0; j<26; j++)
            {
                if(curr->child[j]!=NULL)
                {
                    bool exit_code = DFS(curr->child[j], word, i+1, n);
                    if(exit_code)
                    {
                        return true;
                    }
                }
            }
        }
        else
        {
            int childIndex = word[i] - 'a';
            if(curr->child[childIndex] == NULL)
            {
                return false;
            }
            bool exit_code = DFS(curr->child[childIndex], word, i+1, n);
            if(exit_code)
            {
                return true;
            }
        }

        return false;
    }
    bool search(string word) {
        int n = word.length();
        return DFS(root, word, 0, n);
    }
};
