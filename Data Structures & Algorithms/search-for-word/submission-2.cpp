class Solution {
public:

    int r_dir[4] = {-1,1,0,0};
    int c_dir[4] = {0,0,-1,1};

    bool isValidIndex(int i, int j, int m, int n)
    {
        return(i>=0 && i<m && j>=0 && j<n);
    }

    bool isSolution(vector<vector<char>> & board,
                    string & word,
                    int p, int wordLength,
                    int i, int j,
                    int m, int n,
                    vector<vector<bool>> & visited)
    {
        if(p == wordLength)
        {
            //cout << "returning valid solution at index "<<i<<" "<<j<<" "<<p<<endl;
            return true;
        }

        visited[i][j] = true;

        for(int k=0; k<4;k++)
        {
            int i1 = i + r_dir[k];
            int j1 = j + c_dir[k];

            if(isValidIndex(i1,j1,m,n) && board[i1][j1]==word[p] && visited[i1][j1] == false)
            {
                if(isSolution(board, word, p+1, wordLength, i1, j1 ,m ,n, visited))
                {
                    //cout << "returning valid solution at index "<<i<<" "<<j<<" pointer: "<<p<<endl;
                    return true;
                }
            }
        }
        visited[i][j] = false;
        return false;
    }

    bool exist(vector<vector<char>>& board, string word) {
        /*
        Approach: classical backtracking: Leaf approach here
        to find if feasible solution exists or not
        maintain current cell index of matrix, and current pointer from string
        if cell value matches string pointer value,
            then do a for loop in 4 directions for p+1 pointer
                - and call isSolution() function
                - if any of them returns true, then return true
            else, backtrack to (i,j)the cell and try solution with next cell
            maintain visited as well, while doing a traversal to avoid traversing duplicates

            brainstorming : https://github.com/jpvaishnav/Profile/blob/main/images/word_search_backtrack.jpg
        */

        int wordLength = word.size();
        int m = board.size();
        if(m==0)
        {
            return false;
        }
        int n = board[0].size();

        vector<vector<bool>> visited(m, vector<bool>(n, false));

        for(int i=0; i<m; i++)
        {
            for(int j=0; j<n; j++)
            {
                if(board[i][j] == word[0])
                {
                    if(isSolution(board, word, 1, wordLength, i, j, m, n, visited))
                    {
                        //cout << "returning valid solution at index "<<i<<" "<<j<<endl;
                        return true;
                    }
                }
            }
        }
        return false;
    }
};
