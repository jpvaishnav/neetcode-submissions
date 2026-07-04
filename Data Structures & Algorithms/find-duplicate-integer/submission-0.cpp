class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        /*
        every element can be used as pointer to next element
        1 -> arr[1] = 2
        2 -> arr[2] = 3
        3 -> arr[3] = 2
        2 is already visited, hence this cycle can be detected using linked-in slow fast algorithm
        and start point of this cycle can be detected by having another iteration where both slow and fast
        pointers move by 1 point

        O(n) time, O(1) aux space
        */

        int slow = 0;
        int fast = 0;
        do
        {
            slow = nums[slow];
            fast = nums[nums[fast]];
        }
        while(slow != fast);

        // given that arr[slow] == arr[fast]
        // now find start point of cycle
        fast = 0;
        while(slow!=fast)
        {
            slow = nums[slow];
            fast = nums[fast];
        }

        // slow is the start of cycle, and repeated node
        // did dry run on 1,2,3,2,2, and on 1,2,3,4,4

        return slow;
    }
};
