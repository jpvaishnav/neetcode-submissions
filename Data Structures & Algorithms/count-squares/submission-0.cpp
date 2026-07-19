class CountSquares {
public:
    unordered_map<int, vector<int>> horizonPoints;
    unordered_map<int, vector<int>> verticalPoints;

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
        */
    }
    
    void add(vector<int> point) {
        int x = point[0];
        int y = point[1];

        this->horizonPoints[x].push_back(y);
        this->verticalPoints[y].push_back(x);
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
    }
};
