class Solution {
public:
    int search(vector<int>& nums, int target) {
        // logic:
        // low, high, mid pointers
        // if low.... mid segment is sorted -> 
        // Then check if target is present between lower and upper bound -> if yes, then perform binary search lookup, else the element is present in 2nd segment
        // else if low..mid is not sorted> Then mid+1 to high should be sorted.
        // and perform similar exercise here.
        // mid is the pivot around which segments/partitions are compared

        int low = 0;
        int high = nums.size()-1;
        while(low <= high)
        {
            int mid = low+(high-low)/2;
            if(nums[mid] == target)
            {
                return mid;
            }
            else if(mid!=0 && nums[mid-1] > nums[low])
            {
                // low .. mid-1 is sorted
                if(target >= nums[low] && target <= nums[mid-1])
                {
                    high=mid-1;
                }
                else
                {
                    low = mid+1;
                }
            }
            else
            {
                // mid+1 to high is sorted
                if(mid!=nums.size()-1 && target >= nums[mid+1] && target <= nums[high])
                {
                    // > element is present in this range, so reduce lookup in this range
                    low = mid+1;
                }
                else
                {
                    high = mid-1;
                }
            }
        }

        return -1;
    }
};
