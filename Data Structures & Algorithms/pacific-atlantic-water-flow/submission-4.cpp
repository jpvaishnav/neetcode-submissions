class Solution {
public:

    const int r_dir[4] = {-1,1,0,0};
    const int c_dir[4] = {0,0,-1,1};

    bool isValidIndex(int i, int j, int m, int n)
    {
        return (i>=0 && i<m && j>=0 && j<n);
    }

    // return 0 if pacific is reached, return 1 if atlantic is reached
    // return -1 otherwise
    // return 2 if both reached
    int DFS(vector<vector<int>>& heights, vector<vector<int>>& reach, 
            int i, int j, int m, int n, int parent_i, int parent_j)
    {
        // valid index is already passed by dfs entry and 
        // in neighbor traversal we will check index, so no need to check index here

        // visited marking will be done after traversing all nodes -> update reach

        // base case
        // Pacific condition: i==0, j==0
        // Atlantic condition: i==m-1, j==n-1
        if(i==0 && j == n-1 || i==m-1 && j == 0)
        {
            reach[i][j] = 2;
            return 2;
        }

        bool pacific_flag = false;
        bool atlantic_flag = false;
        // traverse neighbors
        for(int k = 0; k < 4; k++)
        {
            int neighbor_r = i + r_dir[k];
            int neighbor_c = j + c_dir[k];
            if(isValidIndex(neighbor_r,neighbor_c,m,n)
                && heights[i][j]>=heights[neighbor_r][neighbor_c]
                && !(neighbor_r==parent_i && neighbor_c==parent_j) )
            {
                if(reach[neighbor_r][neighbor_c] == 2)
                {
                    reach[i][j] = 2;
                    return 2;
                }
                int exit_code = DFS(heights, reach, neighbor_r, neighbor_c, m, n, i, j);
                if(exit_code == 2)
                {
                    reach[i][j] = 2;
                    return 2;
                }
                if(exit_code == 1)
                {
                    pacific_flag = true;
                }
                if(exit_code == 0)
                {
                    atlantic_flag = true;
                }
                // exit code -1 means not reachable, so ignore                
            }
        }

        if(pacific_flag && atlantic_flag)
        {
            reach[i][j] = 2;
            return 2;
        }
        if(pacific_flag)
        {
            return 1;
        }
        if(atlantic_flag)
        {
            return 0;
        }

        // process node direct reacahbility
        if((i==0 || j==0))
        {
            return 1;
        }
        if((i==m-1 || j==n-1))
        {
            return 0;
        }
        // reaching here means the node can't reach to both pacific and atlantic
        return -1;
    }

    void dfsFromOceanToNode(vector<vector<int>>& heights, 
                            vector<vector<bool>>& matrix, 
                            int i, int j, int m, int n)
    {
        // mark as visited
        matrix[i][j] = true;

        // pick neighbors and DFS
        for(int k = 0; k < 4; k++)
        {
            int neighbor_r = i + r_dir[k];
            int neighbor_c = j + c_dir[k];
            if(isValidIndex(neighbor_r,neighbor_c,m,n)
                && heights[i][j] <= heights[neighbor_r][neighbor_c]
                && matrix[neighbor_r][neighbor_c] == false)
            {
                dfsFromOceanToNode(heights, matrix, neighbor_r, neighbor_c, m, n);
            }
        }

        return;
    }

    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        /*
        Approach: Pattern is similar to getting number of islands in an area
        4-directional DFS
        choose any node as source node,
        apply 4 direction traversals, and check if given node can reach to both pacific and atlantic
            - if not, then simply mark that node as unreachable, so that it doesn't get pick in next iteration
                of DFS entry or neighbor choosing
        In the end, the nodes which are not marked unreachable are answer set
            - why our answer set is not marking the reachable nodes?
                - because unreachable nodes set improves code perf
                - if any other node reaches to a node n, 
                    - and we know the info that n is unreachable, that DFS chain can be stopped there iself
                - but if don't mark reachable computed nodes,
                    - they will also get re-computed
                so have 3 values:
                    -1: not computed yet
                     0: computed, but not reachable to both oceans
                     1: computed, and reachable to both oceans
        Time complexity: O(number of nodes): O(m*n)

        Pacific condition: i==0, j==0
        Atlantic condition: i==m-1, j==n-1

        problem with this code-
        Infinite Loops: By only passing parent_i and parent_j, a path can easily move (0,0) -> (0,1) -> (1,1) -> (1,0) -> (0,0). Because (0,0) is not the immediate parent of (1,0), your code happily revisits it, creating an endless cycle.
            - this can be solved by maintaining another visited array of ancestors
            However, doing this breaks your time complexity completely, turning your code from a fast \(O(m \times n)\) solution into an exponential \(O(4^{m \times n})\) exhaustive search.
            In standard graph algorithms, memoization (storing an exit code like 0, 1, or 2) only works if the result of a cell is absolute. For example, if you visit cell (r, c) and it determines it can reach the Pacific, that should always be true.

        Simplified approach: Instead of from land to ocean,
        reach from ocean to land: 
            - Similar approach of other questions where we had computed reverse of what is asked
            - because that was easier in graph traversals
        */

        // vector<vector<int>> ans;

        // int m = heights.size();
        // if(m==0)
        // {
        //     return ans;
        // }
        // int n = heights[0].size();
        // vector<vector<int>> reach(m, vector<int>(n,-1));

        // for(int i=0; i<m; i++)
        // {
        //     for(int j=0; j<n; j++)
        //     {
        //         if(reach[i][j] == -1)
        //         {
        //             DFS(heights, reach, i, j, m, n, -1, -1);
        //         }
        //     }
        // }

        // // nodes with reach=2 can reach to both atlantic and pacific
        // for(int i=0; i<m; i++)
        // {
        //     for(int j=0; j<n; j++)
        //     {
        //         if(reach[i][j] == 2)
        //         {
        //             vector<int> temp;
        //             temp.push_back(i);
        //             temp.push_back(j);
        //             ans.push_back(temp);
        //         }
        //     }
        // }

        // return ans;

        /*
        Approach 2: based on visualisation, dry run on given test case,
            and pattern from previous problem(start from target state and check if source is reachable with given conditions)
            in this case, 
                - target state = 1st row, and 1st column for pacific
                    - last row, last column for atlantic
                - condition
                    - would be switched to uphill.
                        - go from lower height to higher or equal height
                - pick neighbor if its already not visited previously
                    - to avoid loop
                - maintaining seperate visited array?
                    - no maintain a pacific matrix where 0 means not reached yet, 1 means pacific ocean connected
                    - can 0 cause infinite loop?
                        - no, because in this case, we are starting from edges, which are already 1
                            - and we only go to neighbor nodes and mark them as 1
                            - so, no traversal on 0

        - time complexity of this approach: O(M*N)
            - because every node is getting visited at max 1 time
        */

        vector<vector<int>> ans;
        int m = heights.size();
        if(m==0)
        {
            return ans;
        }
        int n = heights[0].size();
        // cover pacific ocean
        vector<vector<bool>> pacific_matrix(m, vector<bool>(n, false));
        for(int j = 0; j < n ; j++)
        {
            // i = 0, j = j
            // add a condition here - if matrix[i][j] == false
            if(pacific_matrix[0][j] == false)
            {
                dfsFromOceanToNode(heights, pacific_matrix, 0, j, m, n);
            }
        }

        for(int i = 0; i < m ; i++)
        {
            if(pacific_matrix[i][0] == false)
            {
                dfsFromOceanToNode(heights, pacific_matrix, i, 0, m, n);
            }
            // i = i, j = 0
            
        }

        vector<vector<bool>> atlantic_matrix(m, vector<bool>(n, false));
        for(int j = 0; j < n ; j++)
        {
            if(atlantic_matrix[m-1][j] == false)
            {
                // i = m-1, j = j
                dfsFromOceanToNode(heights, atlantic_matrix, m-1, j, m, n);
            }
        }

        for(int i = 0; i < m ; i++)
        {
            if(atlantic_matrix[i][n-1] == false)
            {
                // i = i, j = n-1
                dfsFromOceanToNode(heights, atlantic_matrix, i, n-1, m, n);
            }
        }

        // get intersection nodes which are 1 on both pacific and atlantic matrix

        for(int i = 0; i<m; i++)
        {
            for(int j =0; j<n; j++)
            {
                if(pacific_matrix[i][j] && atlantic_matrix[i][j])
                {
                    vector<int> temp = {i,j};
                    // temp.push_back(i);
                    // temp.push_back(j);
                    ans.push_back(temp);
                }
            }
        }

        return ans;
    }
};
