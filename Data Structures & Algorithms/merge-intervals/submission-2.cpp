class Solution {
public:
    static bool intervalComp(vector<int> & i1, vector<int> & i2)
    {
        return (i1[0] < i2[0]);
    }

    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        /*
        Approach: similar activity selection algorithm
        - sort by finish time
        - maintain prev and curr
        - iterate over intervals
            - if prev and curr are overlapping
                - then merge prev and curr
                prev.start = min(prev.start, curr.start)
                pre.end = curr.end

        intervals=[[2,3],[4,5],[6,7],[8,9],[1,10]]
        is not working when sorting with end time
        - pattern from this example: sort by start time

        summary between 2 techniques of sorting by start vs finish time:

        Merge Intervals (Interval Partitioning) uses a Greedy Algorithm sorted by start time to group overlapping segments sequentially from left to right, as seen in LeetCode 56 (Merge Intervals).
        This technique aims to minimize resources or find contiguous blocks by blending colliding events into a single, continuous timeline block.
        Erase Overlap (Interval Scheduling Maximization Problem / ISMP) uses an Earliest Finish Time Greedy Algorithm sorted by end time to clear the timeline quickly, as seen in LeetCode 435 (Non-overlapping Intervals).T
        This technique aims to maximize event count by prioritizing the tasks that finish first, leaving maximum room for future choices.
        */
        int n = intervals.size();
        sort(intervals.begin(), intervals.end(), intervalComp);
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
