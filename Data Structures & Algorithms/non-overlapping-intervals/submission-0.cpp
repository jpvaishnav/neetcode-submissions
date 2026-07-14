class Solution {
public:
    static bool intervalComp(vector<int> & i1, vector<int> & i2)
    {
        return (i1[1] < i2[1]);
    }

    bool areOverlapping(vector<int> prev, 
                        vector<int> curr)
    {
        if(curr[0]>=prev[1])
        {
            //non-overlapping
            return false;
        }
        return true;
    }

    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        /*
        Approach: Greedy algorithm of trains in a platform
        sort by finish time
        count non-overlapping intervals
        return total - non-overlapping as overlapping intervals
        */

        sort(intervals.begin(), intervals.end(), intervalComp);

        int n = intervals.size();
        if(n==0)
        {
            return 0;
        }
        vector<int> prev = intervals[0];
        int nonOverlapping = 1;

        for(int i=1; i<n; i++)
        {
            vector<int> curr = intervals[i];
            if(areOverlapping(prev, curr))
            {
                continue;
            }
            else
            {
                prev = curr;
                nonOverlapping++;
            }
        }

        return n-nonOverlapping;
    }
};
