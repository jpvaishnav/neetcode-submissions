/**
 * Definition of Interval:
 * class Interval {
 * public:
 *     int start, end;
 *     Interval(int start, int end) {
 *         this->start = start;
 *         this->end = end;
 *     }
 * }
 */

class Solution {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        /*
        Approach: Similar to train platform problem
        sort both start and end arrays
        Pick the smaller of start or end
            - increment total counter if picking from start array
            - decrement total counter if picking from finish array
            do ans = max(ans, total counter value)

        */

        vector<int> start_times;
        vector<int> finish_times;

        for(auto interval: intervals)
        {
            start_times.push_back(interval.start);
            finish_times.push_back(interval.end);
        }

        sort(start_times.begin(), start_times.end());
        sort(finish_times.begin(), finish_times.end());

        int i=0;
        int j=0;

        int n = start_times.size();

        int counter = 0;
        int ans = 0;

        while(i<n && j<n)
        {
            if(start_times[i]<finish_times[j])
            {
                i++;
                counter++;
            }
            else
            {
                j++;
                counter--;
            }
            ans = max(ans, counter);
        }
        return ans;
    }
};
