class Solution {
public:

    bool isValidIndex(int i, int j, int & m, int & n)
    {
        return (i>=0 && j>=0 && i<m && j<n);
    }

    bool isValidNode(vector<vector<char>> & grid, 
            int i, 
            int j, 
            vector<vector<bool>> & visited,
            int & m,
            int & n)
    {
        if(isValidIndex(i,j,m,n) && grid[i][j]=='1' && visited[i][j] == false)
        {
            return true;
        }
        return false;
    }
    void DFS(vector<vector<char>> & grid, 
            int i, 
            int j, 
            vector<vector<bool>> & visited,
            int & m,
            int & n)
    {
        // if(isValidIndex(i,j,m,n) == false)
        // {
        //     return;
        // } this is not needed, as function is already validating valid index
        // it means node is valid in grid, so mark it as visited
        cout<< "Marking visited: "<< i << " "<< j << endl;
        visited[i][j] = true;
        // pick neighbors
        // i,j -> i+1,j; i-1,j; i, j+1; i, j-1;
        if(isValidNode(grid, i+1, j, visited ,m, n))
        {
            cout<< "Entering DFS in "<< i+1 << " "<< j<< endl;
            DFS(grid, i+1, j, visited, m, n);
            /*
            A typo in function argument DFS(grid, i+1, j, visited, m, m) passing both as m
            lead to this error
            ==3==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x502000000051 at pc 0x588a19c0d882 bp 0x7ffd8690b960 sp 0x7ffd8690b958
READ of size 1 at 0x502000000051 thread T0
    #0 0x588a19c0d881 in Solution::isValidNode(std::vector<std::vector<char, std::allocator<char>>, std::allocator<std::vector<char, std::allocator<char>>>>&, int, int, std::vector<std::vector<bool, std::allocator<bool>>, std::allocator<std::vector<bool, std::allocator<bool>>>>&, int&, int&) /box/main.cpp:44:37
    #1 0x588a19c0d881 in Solution::DFS(std::vector<std::vector<char, std::allocator<char>>, 
            */
        }
        if(isValidNode(grid, i-1, j, visited ,m, n))
        {
            cout<< "Entering DFS in "<< i-1 << " "<< j<< endl;
            DFS(grid, i-1, j, visited, m, n);
        }
        if(isValidNode(grid, i, j+1, visited ,m, n))
        {
            cout<< "Entering DFS in "<< i << " "<< j+1<< endl;
            DFS(grid, i, j+1, visited, m, n);
        }
        if(isValidNode(grid, i, j-1, visited ,m, n))
        {
            cout<< "Entering DFS in "<< i << " "<< j-1<< endl;
            DFS(grid, i, j-1, visited, m, n);
        }

        // if(isValidIndex(i+1,j,m,n) && grid[i+1][j] == '1' && visited[i+1][j] == false)
        // {
        //     cout<< "Entering DFS in "<< i+1 << " "<< j<< endl;
        //     DFS(grid, i+1, j, visited, m, m);

        // }
        // if(isValidIndex(i-1,j,m,n) && grid[i-1][j] == '1' && visited[i-1][j] == false)
        // {
        //     cout<< "Entering DFS in "<< i-1 << " "<< j<< endl;
        //     DFS(grid, i-1, j, visited, m, m);
        // }
        // if(isValidIndex(i,j+1,m,n) && grid[i][j+1] == '1' && visited[i][j+1] == false)
        // {
        //     cout<< "Entering DFS in "<< i << " "<< j+1<< endl;
        //     DFS(grid, i, j+1, visited, m, m);
        // }
        // if(isValidIndex(i,j-1,m,n) && grid[i][j-1] == '1' && visited[i][j-1] == false)
        // {
        //     cout<< "Entering DFS in "<< i << " "<< j-1<< endl;
        //     DFS(grid, i, j-1, visited, m, m);
        // }

        return;
    }
    int numIslands(vector<vector<char>>& grid) {
        /*
        Similar to finding count of dfs tree in a forest (good question for visualisation as well)
        Only difference is neighbors here would be from (i,j) to 4 directions.
        (if question was allowing diagonal traversals), then there would have been 8 directions

        Initialize visited metrix
        traverse each node, if given node is land and unvisited, then apply DFS
            - DFS marks that node as visited,
                - and calls DFS() for its unvisited neighbors
        Time complexity: O(m*n)
        Aux space complexity: O(m*n)
        */

        vector<vector<bool>> visited; // C++ by default initiates to false
        // no size of m, n is given here; so we need to initialize initial values here
        for(int i = 0; i < grid.size() ; i++)
        {
            vector<bool> temp;
            for(int j = 0; j < grid[i].size(); j++)
            {
                temp.push_back(false);
            }
            visited.push_back(temp);
        }

        int islands = 0;
        int m = grid.size(); // numer of rows
        for(int i = 0; i < m; i++)
        {
            int n = grid[i].size(); // number of columns
            for(int j = 0; j < n; j++)
            {
                char node = grid[i][j];
                if(node == '1' && visited[i][j] == false)
                {
                    islands++;
                    DFS(grid, i, j, visited, m, n);
                }
            }
        }

        return islands;
        
    }
};
