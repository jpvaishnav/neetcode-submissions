class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        /*
        Approach: Standard heap use
        Naive algo: sort array and return arr[k]
            time: O(NlogN)
        Heap algo:
            - maintain min heap of k size
            - insert first k element in min heap
            - Now traverse all elements
                - if new element is less than min of heap
                    - that element is not useful in context of k largest elements,
                        so no action
                - if element is greater than min of heap
                    - then pop heap top
                    - and insert new element
            - And of heap, we have K largest element in heap
                - and heap top is kth largest
            - time complexity: O(NlogK)
            
        */

        priority_queue<int, vector<int>, greater<int> > minHeap;

        for(int i=0; i<k; i++)
        {
            minHeap.push(nums[i]);
        }

        for(int i=k; i<nums.size(); i++)
        {
            if(nums[i] <= minHeap.top())
            {
                // no action
                // even in case of equal, no action needed
                // example: 1,1,1,2,2,2 k=4
                // 1,1,1,2 is pushed in minHeap, so next 2 won't be
            }
            else // if equal or greater, then push.
            {
                minHeap.pop();
                minHeap.push(nums[i]);
            }
        }

        return minHeap.top();
    }
};
