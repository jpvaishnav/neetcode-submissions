class Solution {
public:
    int maxProduct(vector<int>& nums) {
        /*
        Approach:
            negative element stops the max prod subarray,
            but consecutive negative elements are fine, as they gets multiplied
            include-exclude pattern
                - include ith element in product
                    - arr[i] * f(i-1)
                    - since its sub-array so f(i-1) has to end at i-1
                    that means
                    dp[i] = max prod of subarray ending at index i
                        - ending at (ending till)
                    and ans would be max of all dps(similar to LIS)
                - exclude ith element from product
                    - ith element arr[i] is only element in the substring
                - isn't it kadane algorithm?

                Kadane not working for given example:
                    nums=[-2,3,-4]
                Since, negative is contributing factor, 
                    should we solve using min and max
                But, dp[][] seems most standard solution
                write recursion first
                find overlapping sub-problem
                then write tabulation,
                    - if difficulty in tabulation, go for memoization

        - derived optimal solution by example, dry run of pattern across test cases
        - and concept of min and max range, which gets amplified by incoming new element
        visuals at https://github.com/jpvaishnav/Profile/blob/main/images/dp_max_prod_subarray_1.jpg
        https://github.com/jpvaishnav/Profile/blob/main/images/dp_max_prod_subarray_2.jpg

        https://github.com/jpvaishnav/Profile/blob/main/images/dp_max_prod_subarray_3.jpg

        https://github.com/jpvaishnav/Profile/blob/main/images/max_product_subarray_two_track_kadane.gif

time complexity: O(n), space: O(1)
can we optimize further?

TODOs with Gemini:
- link this pattern with existing patterns
- check how DP was supposed to be used in this quesiton

Your $O(n)$ time and $O(1)$ space approach is the absolute global optimum for this problem; you cannot optimize the asymptotic complexity further.
Here is the breakdown of what your pattern is called, how it maps to standard Dynamic Programming, and why your solution is DP.
------------------------------
## What is This Pattern Called?
Your approach goes by two primary names in algorithmic design:

   1. The Variations of Kadane's Algorithm (or "Two-Track Kadane's"): Standard Kadane's algorithm only tracks the maximum subarray sum ending at the current position. Because a negative multiplied by a negative creates a positive, you modified it to track two tracks concurrently: the maximum possible product and the minimum possible product ending at index i.
   2. State-Machine Dynamic Programming: You are maintaining a running state (min_prod and max_prod) that transitions sequentially based on the sign of the incoming element (nums[i]).

------------------------------
## How DP Was Supposed to Be Used Here
Your code already is a Dynamic Programming solution. It is the space-optimized version of a Tabulation DP.
To see how DP was "supposed" to look from first principles, let us trace it from the standard 2D table down to your exact code.
## 1. The Full 2D DP Definition
If you look at the problem as a state transition, at each index $i$, the maximum or minimum product ending at that index depends strictly on the maximum or minimum product ending at index $i-1$.
We define two 1D arrays (or a 2D array dp[N][2]):

* dp_max[i]: The maximum product of a subarray ending at index i.
* dp_min[i]: The minimum product of a subarray ending at index i.

## 2. The Recurrence Relations
For any index $i$, you have three choices to form the new subarray ending at $i$:

   1. Start a brand new subarray containing only the current element: nums[i]
   2. Multiply the current element with the maximum product ending at the previous element: nums[i] * dp_max[i-1]
   3. Multiply the current element with the minimum product ending at the previous element: nums[i] * dp_min[i-1]

The transitions are mathematically stated as:
$$\text{dp\_max}[i] = \max(\text{nums}[i], \text{nums}[i] \times \text{dp\_max}[i-1], \text{nums}[i] \times \text{dp\_min}[i-1])$$ 
$$\text{dp\_min}[i] = \min(\text{nums}[i], \text{nums}[i] \times \text{dp\_max}[i-1], \text{nums}[i] \times \text{dp\_min}[i-1])$$ 
## 3. Full Tabulation DP Code Template
Here is how the unoptimized, full-space DP version looks. It explicitly shows how your conditional if(nums[i] > 0) logic is elegantly bypassed by taking the min/max of all three options simultaneously:

int maxProduct(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;

    // Allocate full DP tables
    vector<int> dp_max(n), dp_min(n);

    // Base cases
    dp_max[0] = nums[0];
    dp_min[0] = nums[0];
    int global_max = nums[0];

    for (int i = 1; i < n; i++) {
        // Option 1: Just current element
        // Option 2: Current element * previous max
        // Option 3: Current element * previous min
        dp_max[i] = max({nums[i], nums[i] * dp_max[i-1], nums[i] * dp_min[i-1]});
        dp_min[i] = min({nums[i], nums[i] * dp_max[i-1], nums[i] * dp_min[i-1]});

        global_max = max(global_max, dp_max[i]);
    }
    return global_max;
}

## 4. How Your Solution Space-Optimized This Table
Notice that dp_max[i] only ever looks back at dp_max[i-1]. It never looks at i-2, i-3, etc.
Because of this strict linear rolling dependency, you do not need the full vector<int> array sizes of $N$. You can replace the entire array with just two scalar variables: max_prod and min_prod. By updating these two variables in place at every step, you naturally optimized the space complexity from $O(n)$ down to $O(1)$.
------------------------------
## Clean Code Refactoring Tip
Your explicit conditional branching (if (nums[i] > 0) ... else ...) works perfectly, but you can dramatically shorten and clean your code by using a standard trick: swapping min and max when a negative number is encountered.
If nums[i] is negative, multiplying by it flips magnitudes: the largest becomes the smallest, and the smallest becomes the largest.

int maxProduct(vector<int>& nums) {
    int n = nums.size();
    int max_prod = nums[0], min_prod = nums[0], ans = nums[0];

    for(int i = 1; i < n; i++) {
        // If negative, the potential next max and min swap roles
        if (nums[i] < 0) {
            swap(max_prod, min_prod);
        }

        // DP State transitions
        max_prod = max(nums[i], max_prod * nums[i]);
        min_prod = min(nums[i], min_prod * nums[i]);

        ans = max(ans, max_prod);
    }
    return ans;
}

        */
        int n = nums.size();
        if(n==1)
        {
            return nums[0];
        }

        int max_prod = max(nums[1], nums[1] * nums[0]);
        int min_prod = min(nums[1], nums[1] * nums[0]);
        int ans = max_prod;

        //cout << 1 << " "<<min_prod << " "<<max_prod << endl;

        for(int i=2; i<n; i++)
        {
            int curr_max_prod = nums[i];
            int curr_min_prod = nums[i];
            if(nums[i]>0)
            {
                //curr_max_prod =  max(nums[i], max_prod * nums[i]);
                //curr_min_prod =  min(nums[i], min_prod * nums[i]);
                if(max_prod * nums[i] > nums[i])
                {
                    curr_max_prod = max_prod * nums[i];
                }
                if(min_prod * nums[i] < nums[i])
                {
                    curr_min_prod = min_prod * nums[i];
                }
                //ans = max(ans, curr_max_prod);
                
            }
            else
            {
                //curr_max_prod = max(nums[i], nums[i] * min_prod);
                //curr_min_prod = min(nums[i], nums[i] * max_prod);
                //cout << i << " "<<curr_min_prod << " "<<curr_max_prod << endl;
                //ans = max(ans, curr_max_prod);

                if(nums[i] * min_prod > nums[i])
                {
                    curr_max_prod = nums[i] * min_prod;
                }
                if(nums[i] * max_prod < nums[i])
                {
                    curr_min_prod = nums[i] * max_prod;
                }
            }
            if(curr_max_prod > ans)
            {
                ans= curr_max_prod;
            }
            min_prod = curr_min_prod;
            max_prod = curr_max_prod;
        }

        return ans;
    }
};
