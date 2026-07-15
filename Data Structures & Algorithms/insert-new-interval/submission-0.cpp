class Solution {
public:
    static bool intervalComp(vector<int> & i1, vector<int> & i2)
    {
        return (i1[0] < i2[0]);
    }
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        /*
        Approach:
        add new interval inside intervals array if
            newInterval.start  is between prev.start and curr.start
            this one is O(N), because vector will have to be right shifted
            another is O(NlogN), where insert new interval in vector and do sort
        Then call MergeOverlappingIntervals
        intervals are already sorted, so O(n)
        */

        intervals.push_back(newInterval);
        sort(intervals.begin(), intervals.end(), intervalComp);

        int n = intervals.size();

        vector<vector<int>> ans;
        if(n==0)
        {
            return ans;
        }
        vector<int> prev = intervals[0];

        for(int i=1; i<n; i++)
        {
            vector<int> curr = intervals[i];
            // if overlapping
            if(curr[0] <= prev[1])
            {
                // merge
                //prev[0] = min(prev[0], curr[0]); which is prev[0] is sorted by start time
                prev[1] = max(prev[1], curr[1]);
                // why no min here, because sorted by finish time
                // so curr[1] will always be greater than prev[1]
            }
            else
            {
                ans.push_back(prev);
                prev = curr;
            }
        }

        ans.push_back(prev);
        return ans;
    }
};
