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

        Time complexity: O(nLogn)

        Question: What is difference between approaches for
            > Non-overlapping intervals: sort by finish time
            > Meeting rooms: Sort both start and finish time
            > Merge overlapping intervals: sort by start time

        ## 1. Non-Overlapping Intervals (Interval Scheduling)

* 
* The Logic: Always pick the item that frees up the timeline fastest. This leaves the absolute maximum room available for all subsequent choices. [1] 
* The Technique: Earliest Finish Time (EFT) / Greedy Algorithm. [2, 3, 4] 
* How it Works: Sort by finish time only. Iterate and pick the next interval whose start time is greater than or equal to the current interval's finish time. [5, 6, 7] 
* Similar Problems: [LeetCode 435 (Non-overlapping Intervals)](https://leetcode.com/problems/non-overlapping-intervals/), [LeetCode 452 (Minimum Number of Arrows to Burst Balloons)](https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/), LeetCode 646 (Maximum Length of Pair Chain). [8] 
* 

## 2. Meeting Rooms II (Interval Partitioning)

* 
* The Logic: Track the exact "peaks" of overlap on a timeline. When a meeting starts, you need a room; when it ends, you free up a room.
* The Technique: Chronological Event Processing / Two-Pointer Chronological Sweep.
* How it Works: Separate all starts and ends into two separate lists. Sort both start and finish times independently. Use two pointers to move forward in time, incrementing a room counter for starts and decrementing for ends.
* Similar Problems: [LeetCode 253 (Meeting Rooms II)](https://leetcode.com/problems/meeting-rooms-ii/), LeetCode 1094 (Car Pooling), LeetCode 732 (My Calendar III / Peak Load Finding). [9, 10, 11, 12, 13] 
* 

## 3. Merge Overlapping Intervals (Interval Blending)

* 
* The Logic: Find contiguous, unbroken chains of time. Sorting by start time ensures that any segments capable of merging sit directly next to each other.
* The Technique: Sequential Continuity / Linear Scan Greedy Algorithm.
* How it Works: Sort by start time only. Iterate through the array. If the next interval's start time falls inside the current interval's boundaries, merge them by extending the current interval's end point.
* Similar Problems: [LeetCode 56 (Merge Intervals)](https://leetcode.com/problems/merge-intervals/), LeetCode 57 (Insert Interval), LeetCode 986 (Interval List Intersections). [14, 15, 16, 17, 18] 
* 

------------------------------
Would you like me to show you the C++ code implementation for the Meeting Rooms II two-pointer approach or how to use a Min-Heap (Priority Queue) variation for that same problem?

[1] [https://medium.com](https://medium.com/@aswathipp17/mastering-non-overlapping-intervals-a-greedy-algorithm-deep-dive-gfg-day26-4e7b45eb30c7)
[2] [https://www.youtube.com](https://www.youtube.com/watch?v=5a5jlvarYGM)
[3] [https://testbook.com](https://testbook.com/question-answer/latest-start-of-an-activity-is-always--6040c6cffbf724458d743d39)
[4] [https://www.tryexponent.com](https://www.tryexponent.com/courses/swe-practice/binary-search-heaps-and-intervals)
[5] [https://algomaster.io](https://algomaster.io/learn/dsa/non-overlapping-intervals)
[6] [https://algomaster.io](https://algomaster.io/learn/dsa/intervals-introduction)
[7] [https://baotramduong.medium.com](https://baotramduong.medium.com/leetcode-pattern-19-tips-strategies-for-solving-greedy-algorithms-problems-including-10-classic-5d36314f3799)
[8] [https://www.interviewcoder.co](https://www.interviewcoder.co/blog/google-coding-interview-patterns-12-patterns-cover-most-questions)
[9] [https://algo.monster](https://algo.monster/liteproblems/253)
[10] [https://medium.com](https://medium.com/@conniezhou678/mastering-data-algorithm-part-7-merging-intervals-in-python-a198ab5606a6)
[11] [https://mecha-mind.medium.com](https://mecha-mind.medium.com/algo-pattern-recognition-interval-and-scheduling-problems-184df33f7cf1)
[12] [https://levelup.gitconnected.com](https://levelup.gitconnected.com/dsa-intervals-insert-merge-non-overlapping-meeting-rooms-8f5e91ea5f37)
[13] [https://dilipkumar.medium.com](https://dilipkumar.medium.com/sweep-line-algorithm-e1db4796d638)
[14] [https://algo.monster](https://algo.monster/liteproblems/252)
[15] [https://www.hellointerview.com](https://www.hellointerview.com/learn/code/intervals/overview)
[16] [https://www.simplilearn.com](https://www.simplilearn.com/kadanes-algorithm-article)
[17] [https://takeuforward.org](https://takeuforward.org/data-structure/merge-overlapping-sub-intervals)
[18] [https://algomaster.io](https://algomaster.io/learn/dsa/intervals-introduction)


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
