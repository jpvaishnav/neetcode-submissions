class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        /*
        Approach:
            Traverse the matrix 
            if a cell (i,j) has value = 0
            then move all row values from i=0 to m-1 bottom most side to 0
            each cell is visited exactly once through outer loop and exactly once through inner loop
                - time complexut: O(m*n*(m+n))
            caveat: if we mark a cell as 0, then it would create cascade effect
            Input:


matrix=[[1,2,3],[4,0,5],[6,7,8]]
Your Output:


[[1,0,0],[0,0,0],[0,0,0]]
Expected output:


[[1,0,3],[0,0,0],[6,0,8]]

        - can we mark 0 intended values as -val?
            - matrix value itself can be negative
        
        // O(m*n) space solution is to use boolean array to track 0 value cells
        and then update only 0 value cells through loops

        O(1) space solution?
        // use arithmetic ops to store both current and 0 state for that cell
            // lets consider that row, and column value as target values
            // if target is already 0, then dont update
            // otherwise set them to INT_MAX
        // use INT_MAX? divide by 0 if a value is supposed to be 0
            // this test case is failing with int_max
            Input

matrix=[[-4,-2147483648,6,-7,0],[-8,6,-8,-6,0],[2147483647,2,-9,-6,-10]]
Your Output

[[0,0,0,0,0],[0,0,0,0,0],[0,2,-9,-6,0]]
Expected Output

[[0,0,0,0,0],[0,0,0,0,0],[2147483647,2,-9,-6,0]]

        efficient approach:
        - use first element of row and column as indicator that wheter this row or column should be marked as 0 or not
        - track first row and first column seperately, as indicator for both of them would be arr[0][0]
        for others, it would be unique,
            if arr[i][j] = 0, then arr[i][0] =0, arr[0][j] =0;
            visualise this

            ## Diagram (Mermaid)

Renders in GitHub, VS Code, Obsidian, and most Markdown viewers that support Mermaid.

```mermaid
flowchart TD
    subgraph Row0["row 0 — indicator row"]
        direction LR
        A00["1"]
        A01["2"]
        A02["3"]
        A03["4"]
    end
    subgraph Row1["row 1"]
        direction LR
        A10["5"]
        A11["0"]
        A12["7"]
        A13["8"]
    end
    subgraph Row2["row 2"]
        direction LR
        A20["9"]
        A21["10"]
        A22["11"]
        A23["0"]
    end
    subgraph Row3["row 3"]
        direction LR
        A30["13"]
        A31["14"]
        A32["0"]
        A33["16"]
    end

    A11 -->|marks| A10
    A11 -->|marks| A01
    A23 -->|marks| A20
    A23 -->|marks| A03
    A32 -->|marks| A30
    A32 -->|marks| A02
```


        */
        int m = matrix.size();
        if(m==0)
        {
            return;
        }
        int n = matrix[0].size();
        bool first_row = false;
        bool first_column = false;
        // track first row, first column seperately for clean code
        for(int i=0; i<m; i++)
        {
            if(matrix[i][0] == 0)
            {
                //cout<<"Marking first_column true at "<<i<<endl;
                first_column = true;
                break;
            }
        }

        for(int j=0; j<n; j++)
        {
            if(matrix[0][j] == 0)
            {
                
                //cout<<"Marking first_row true at "<<j<<endl;
                first_row = true;
                break;
            }
        }

        for(int i=1; i<m; i++)
        {
            for(int j=1; j<n; j++)
            {
                if(matrix[i][j] == 0)
                {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }

        // cout<<"matrix after updates: "<<endl;
        // for(int i=0; i<m; i++)
        // {
        //     for(int j=0; j<n; j++)
        //     {
        //         cout<<matrix[i][j]<<" ";
        //     }
        //     cout<<endl;
        // }

        // process first row, first column and fill

        for(int i=1; i<m; i++)
        {
            if(matrix[i][0] == 0)
            {
                //cout<< "Marking row zero "<<i<<endl;
                // mark that row zero
                for(int col=1;col<n;col++)
                {
                    matrix[i][col] = 0;
                }
            }
        }

        for(int j=1; j<n; j++)
        {
            if(matrix[0][j] == 0)
            {
                //cout<< "Marking col zero "<<j<<endl;
                // mark the columns as zero
                for(int row=1; row<m;row++)
                {
                    matrix[row][j]=0;
                }
            }
        }

        // update first row and first column itself
        if(first_row)
        {
            //cout<<"Processing first_row"<<endl;
            for(int j=0; j<n ;j++)
            {
                //cout<<"matrix 0 "<<j<<endl;
                matrix[0][j] = 0;
            }
        }
        if(first_column)
        {
            //cout<<"Processing first_column"<<endl;
            for(int i=0; i<m; i++)
            {
                //cout<<"matrix "<<i<<" "<<0<<endl;
                matrix[i][0] = 0;
            }
        }
        return;
    }
};
