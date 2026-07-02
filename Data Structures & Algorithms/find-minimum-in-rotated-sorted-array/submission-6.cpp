class Solution {
public:
    int findMin(vector<int> &nums) {
        /*
        Algo: Similar to finding an element sorted numsay
        low, mid, high.
        slices = nums[low]...ar[mid-1], nums[mid] is already searched/compared with min,
        nums[mid+1]...nums[high]
        condition dervied from example:
        of(low == mid-1) // then comparison does not makes sense,
            so update min, and move to the other window
        while(low < high) // because equal is already compared by nums[mid]
        */

        int ans = INT_MAX;
        int n = nums.size();
        int low = 0;
        int high = n-1;
        
        while(low <= high)
        {
            int mid = low+(high-low)/2;
            if(nums[mid] < ans)
            {
                ans = nums[mid]; // nums[mid] is compared
            }
            if( mid!=0 && (mid-1 == low || nums[mid-1] > nums[low]))
            {
                // sequence is an increasing sequence from low to mid-1
                // so, lowest could be nums[low] -> compare with nums[low]
                // and eliminate comparison with remaining elements in this window
                // derived mid-1 = low after hitting failures on a test case
                // nums=[4,5,6,7] comparison with 4 would be skipped if we dont add mid-1 == low
                ans = min(ans, nums[low]);
                low = mid+1;
            }
            else
            {
                // mid+1 to high
                if(mid!=n-1) // required for index out of range exception
                {
                    ans = min(ans, nums[mid+1]);
                }
                high = mid-1;
            }
        }
        return ans;
    }
};
