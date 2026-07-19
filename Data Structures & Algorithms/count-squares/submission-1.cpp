class CountSquares {
public:
    unordered_map<int, vector<int>> horizonPoints;
    unordered_map<int, vector<int>> verticalPoints;

    //vector<vector<int>> points;

    CountSquares() {
        /*
        Naive approach: Choose 3 points from given N points
        nC3
        which is N*(N-1)*(N-2)/3*2*1
        which is N^3

        Optimized approach: derived from example:
        get all points on same horizon of given(x1,y1)
            - where x value is same = x1
        get all points on same vertical line of given (x1,y1)
            - where y value is same = y1
        Now, choose 2 points, one from each set
            and find 3rd point which is not same as (x1,y1)
        use hashtable for fetching points in O(1) time?

        Optimization suggested by AI in O(1)
        - uses math pattern of geometry
        - diagonal point pattern in square
        The Optimized \(O(N)\) Approach: 
        Use a Frequency MapTo fix the performance issues while 
        still tracking every single duplicate point, 
        you should use a frequency map.Instead of searching through 
        lists of coordinates to find matching horizontal and vertical points, 
        you can treat the queried point (x, y) as one corner of the square, 
        look up any other point (x1, y1) in your database to act as the diagonally opposite corner, 
        and then verify if the remaining two corners exist.Since a square requires its sides to be equal, the distance \(\vert{}x - x1\vert{}\) must equal \(\vert{}y - y1\vert{}\). This mathematical constraint lets you skip searching entire rows and columns.
        this idea can give O(N) solution,
            
        */
    }
    
    void add(vector<int> point) {
        int x = point[0];
        int y = point[1];

        this->horizonPoints[x].push_back(y);
        this->verticalPoints[y].push_back(x);

        // points.push_back(point);

    }
    
    int count(vector<int> point) {
        int x = point[0];
        int y = point[1];

        int ans = 0;

        vector<int> hPoints = this->horizonPoints[x];
        vector<int> vPoints = this->verticalPoints[y];

        for(auto y1: hPoints)
        {
            for(auto x1: vPoints)
            {
                // target is (x1,y1)
                // and it should not be same as given points
                // (x,y1) (x1,y) (x,y)
                if(x1==x || y1==y)
                {
                    continue;
                }
                // check if (x1,y1) is present
                vector<int> x1Points = this->horizonPoints[x1];
                for(auto ele: x1Points)
                {
                    if(ele==y1)
                    {
                        ans++;
                    }
                }
            }
        }
        return ans;

        // int x = point[0];
        // int y = point[1];

        // int ans = 0;
        // // find all diagonal points
        // vector<vector<int>> diagonals;
        // for(auto p: points)
        // {
        //     int x1 = p[0];
        //     int y1 = p[1];
        //     if(abs(x-x1) == abs(y-y1) && !(x==x1 && y==y1))
        //     {
        //         vector<int> temp;
        //         temp.push_back(x1);
        //         temp.push_back(y1);
        //         diagonals.push_back(temp);
        //     }
        // }

        // for(auto dPoint: diagonals)
        // {
        //     int x1 = dPoint[0];
        //     int y1 = dPoint[1];

        //     // (x,y) (x1,y1)
        //     // lookup
        //     // (x1,y) and (x,y1)

        // //     int target_x = x1;
        // //     int target_y = y;
        // //     for(auto p: points)
        // //     {
        // //         if(p[0] == target_x && p[1] == target_y)
        // //         {
        // //             ans++;
        // //         }
        // //     }

        // //     target_x = x;
        // //     target_y = y1;
        // //     for(auto p: points)
        // //     {
        // //         if(p[0] == target_x && p[1] == target_y)
        // //         {
        // //             ans++;
        // //         }
        // //     }
        // // }

        // // return ans;
    }
};
