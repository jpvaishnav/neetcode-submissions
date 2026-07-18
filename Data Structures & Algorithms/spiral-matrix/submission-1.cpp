class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        /*
        Approach: traversal as given order
        2 techniques:
            - write all traversed index and derive i, j, and index range of k
            - or maintian row_start, row_end, col_start, col_end
            - update these until valid
            row_start=0;
            row_end=m-1;
            col_start=0;
            col_end=n-1;
            row_start++;
            row_end--;
            col_start++;
            col_end--;

            breaking/base condition
            while(row_start < row_end && col_start<col_end)
        */

        int m = matrix.size();
        vector<int> ans;
        if(m==0)
        {
            return ans;
        }

        int n = matrix[0].size();

        int row_start=0;
        int row_end=m-1;
        int col_start=0;
        int col_end=n-1;

        while(row_start < row_end && col_start < col_end)
        {
            cout<<row_start<<" "<<row_end<<" "<<col_start<<" "<<col_end<<endl;
            // print top row
            for(int j=col_start; j<=col_end; j++)
            {
                ans.push_back(matrix[row_start][j]);
            }

            // print last column
            for(int i=row_start+1; i<=row_end; i++)
            {
                ans.push_back(matrix[i][col_end]);
            }

            // print last row
            for(int j=col_end-1; j>=col_start;j--)
            {
                ans.push_back(matrix[row_end][j]);
            }

            //print first col
            for(int i=row_end-1;i>row_start; i--)
            {
                ans.push_back(matrix[i][col_start]);
            }

            row_start++;
            row_end--;
            col_start++;
            col_end--;
        }

        if(row_start == row_end)
        {
            // include entire row
            for(int j=col_start;j<=col_end;j++)
            {
                ans.push_back(matrix[row_start][j]);
            }
        }
        else if(col_start == col_end)
        {
            // include entire column
            // col_start == col_end
            for(int i=row_start;i<=row_end;i++)
            {
                ans.push_back(matrix[i][col_start]);
            }
        }
        else
        {
            // no-op
        }

        return ans;
    }
};
