class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        /*
        Approach; variation of subset problem
        1. this is not a subset problem, so need to traverse till complete depth in tree, traverse till n = 0, that will be base case
        2. instead of include-exclude the pattern becomes + or - at given element

        recursion:
        f(n, sum):
            f(n-1, sum + arr[n-1]) + f(n-1, sum - arr[n-1])
        base case:
            only when n is zero and Target_Minus_Sum also becomes 0:
                then it is 1,
            else,
                0 if n is zero and target_Minus_Sum becomes 0
            2nd variable represents Target_Minus_Sum
            - if we are picking arr[n-1] as positive val:
                we substract from Target_Minus_Sum
            - if we are picking arr[n-1] as negative val:
                - we add in Target_Minus_Sum
        
        Overlapping subproblems -> DP ->
            dp[n+1][sum+1]
            dp[i][j] = dp[i-1][j-arr[i-1]] + dp[i-1][j+arr[j-1]]
        is sum+1 write choice here?
            no, we need to calculate max possible value of sum in advance to instantiate matrix dimensions
                - is that within int range
                - input constraint:
                    n = 20, nums[i] = 1000
                    so max sum is 20,000
            How to handle negative index of sum?
                if target is -1000?
                can we maintain all negatives beyond max_sum?
                max_sum can be 20,000, 
                    so 20,001 is -1
                    20,002 is -2
                    40,000 is -20,000
                    and when perfoming sum operations,
                    consider numbers greater than 20,000 as negative
                running into index out of range error
                asking AI agent about hint:
                    - Gemini provided about offset based shifting & suggested standard method
                    - but our code argued & applied index check in given code itself
                    - but it timed out
                        - because 20*40,000 = 800000 operations?
                        - no, it timed out due to invalid index -> garbage value
                    - Gemini, and claude both pointed to handling index range properly
                    - ugly solution passed
                    - but need to improve this using standard negative range shift as Gemini suggested first.

    Artifacts:
        Solving:
        With AI Agents:
            Yes, there is a major "index out of range" scenario in your code that will cause a segmentation fault or undefined behavior.The bug lies inside your transition logic when a value exceeds the maximum bounds you set for your manual offset mapping.

            Index out of bounds! Your array size is only 40001 (max index 40000). Accessing dp[i-1][41000] will crash your program.Similarly, if j_actual = 20000 and ele = 1000, j_plus_neg_ele becomes 21000. Your code doesn't convert it because it isn't negative, but your manual indexing rule says numbers above 20000 represent negative values. This corrupts your DP states.

            Instead of trying to split the positive and negative spaces at max_sum manually, the industry-standard way to handle negative array indices in DP is to use a uniform flat shift (offset).Since the sum ranges from -20000 to +20000, you simply add 20000 to every sum to make it safely positive (mapping -20000 to 0, 0 to 20000, and 20000 to 40000).

            The absolute best, standard way to solve this and almost any other bounded array/subset DP problem with negative values is to use the Uniform Offset Method.
Instead of writing complex logic to split or flip negative indices, you translate the entire problem's number line to the right so it fits perfectly into a standard array (where indices can only be $0, 1, 2...$).
Here is the 3-step mindset you can reuse for any similar problem:
## 1. Calculate the Theoretical Minimum and Maximum Sum
Look at the problem constraints. Find the worst-case smallest sum and the worst-case largest sum your code could ever encounter.

* Example: If the maximum possible sum of all elements is $10000$, then your range of sums goes from $-10000$ to $+10000$.

## 2. Establish a Constant OFFSET
An array index cannot be negative. To fix this, look at your minimum possible sum and create an OFFSET equal to its absolute value.

* $\text{OFFSET} = \vert{} \text{Minimum Sum} \vert{}$ (e.g., $10000$).
* This transforms your range from $[-10000, +10000]$ into a safely positive index range of $[0, 20000]$.

## 3. Apply the Offset to EVERY Array Access
Whenever you want to read from or write to your DP table using a logical sum value, always append + OFFSET to the index.

Logical Value (Math)  --->  Actual Array Index
     -10000           --->   -10000 + 10000 = 0
          0           --->        0 + 10000 = 10000
     +10000           --->    10000 + 10000 = 20000

## The Universal Template Structure
Whenever you write your DP loops, just use boundary guards to ensure you don't step out of your newly defined positive range:

// If transitioning from state 'j' to a new sumint next_sum = j + element; // or j - element
// Universal Boundary Guardif (next_sum + OFFSET >= 0 && next_sum + OFFSET <= MAX_RANGE) {
    dp[i][next_sum + OFFSET] += dp[i-1][j + OFFSET];
}


**** optimization suggested by claude for early exit:
That runtime error is almost certainly in the final target-encoding step, not inside the DP loop itself — the loop always stays within `[0, max_range]`, but the target encoding at the end has no bounds check at all. Let me confirm with ASan.Confirmed — that's exactly it. `nums=[1], target=-2`: `max_sum` is only `1` (the actual sum of this array), but `target` encodes to `1 + 2 = 3`, and `dp[n]` only has valid indices `0..2`. The DP loop itself is safe because every `j` it ever touches is generated by the `for(j=0; j<=max_range...)` loop — but the **final target lookup is unguarded**, and since you switched `max_sum` from a fixed worst-case constant to the actual sum of `nums`, it's now entirely possible for a legitimate `target` (within the problem's `-1000..1000` bounds) to fall outside what *this specific array* can represent.

**Fix:** if `|target| > max_sum`, it's unreachable by definition — return `0` immediately, before touching the array:

```cpp
if (target > max_sum || target < max_neg_sum) {
    return 0;   // target unreachable — no need to touch dp at all
}
if (target < 0) target = max_sum + (target * -1);
return dp[n][target];
```Clean run under ASan — no more overflow, and the full regression suite (plus two edge cases I added: `nums=[0]` and empty `nums`) all check out. One correction on my own test comment: `nums=[0], target=0` correctly returns `2`, not `1` — since `+0` and `-0` are counted as two distinct sign assignments in this problem even though they evaluate to the same number, so your code got that right and my expected-value comment was wrong.

So, to summarize this round: the fix is a guard clause right before you touch `dp[n][...]`, rejecting any target outside what the array can represent, before doing any indexing:

```cpp
if (target > max_sum || target < max_neg_sum) return 0;
if (target < 0) target = max_sum + (target * -1);
return dp[n][target];
```

This is the same category of bug as the last one, just at a different site — you correctly bounds-checked the DP transition step to switching to actual-sum bounds instead of index bounds, but the final lookup was still trusting `target` blindly. Since you sized `max_sum` off the *actual* array sum (a good optimization) rather than the fixed constraint of 1000/20000, any target the problem legally allows but this particular array can't reach will fall outside your table — so that boundary needs its own explicit check rather than assuming the caller already validated it.

optimization suggested for calculating max_range:

Let me actually run your exact array through the compiled binary and profile it — if the algorithm itself isn't inherently slower for this input (bounds are fixed regardless of data), something else must be going on.I ran your exact array through the compiled binary across several target values — no timeout, ~5ms per call, consistent with the earlier benchmark. So the algorithm itself isn't blowing up on this input; the loop bounds are fixed at `max_range=40001` regardless of what's in `nums`, so runtime is always ~the same regardless of data.

That points to where the real issue is: **your `max_sum` is way bigger than the problem actually needs.** LeetCode's Target Sum constraints are `0 <= sum(nums[i]) <= 1000`, not 20000. You're doing 20x more work than necessary per call (`max_range = 40000` instead of `2000`).

That matters because LeetCode doesn't call your function once — it runs your class against a whole suite of test cases (often 15–100+ for this problem), and if the harness re-instantiates and re-runs your DP for each one, ~5ms per call adds up. At 20x the necessary array size, you're much closer to the time limit than you need to be, and it's plausible that's what's tipping you over on the judge even though a single call in isolation looks fine.

**Fix:** tie `max_sum` to the actual constraint instead of an arbitrary large number:

```cpp
int max_sum = 0;
for (int x : nums) max_sum += x;   // actual max possible |sum|, not a guess
```

This shrinks `max_range` to whatever this specific input actually needs — for your 9-element-sum array, that's `max_sum=9` instead of `20000`, so the DP table goes from `21 × 40001` down to `21 × 19`. That's the same correctness logic you already have, just sized to the real bound instead of the problem's absolute worst case.

A couple of things to double check on your end since I can't see your LeetCode submission directly:
- What target value are you passing when you see the timeout, and is this a LeetCode submission or your own test harness?
- Are you sure the version you submitted matches this exact code (sign-based reflection, not the earlier range-based one)?

If you make the `max_sum` change and it still times out, paste the exact submission and I'll dig further — but this fix alone should remove the 20x overhead regardless of what's ultimately causing it.

        */

        int n = nums.size();
        // optimizing max_sum
        int max_sum = 0;
        for(int i=0; i<n; i++)
        {
            max_sum = max_sum + nums[i];
        }
        max_sum = abs(max_sum);
        int max_neg_sum = max_sum * -1;

        if(target > max_sum || target < max_neg_sum)
        {
            return 0;
        }
        //int max_sum = 20000;
        //int max_neg_sum = -20000;
        int max_range = 2*max_sum;
        vector<vector<int>> dp(n+1, vector<int>(max_range+1));
        //int dp[n+1][max_range+1];
        dp[0][0] = 1;
        for(int j=1;j<=max_range; j++)
        {
            dp[0][j] = 0;
        }

        // based on pattern in 2d, traverse in row first order

        for(int i=1; i<=n; i++)
        {
            for(int j=0; j<=max_range; j++)
            {
                //cout << "updating dp "<<i<<" "<<j<<endl;
                int ele = nums[i-1];
                int j_actual = j;
                if(j>max_sum)
                {
                    j_actual = (j-max_sum)*(-1);
                }
                int j_minus_pos_ele = j_actual - ele;
                int j_plus_neg_ele = j_actual + ele;

                dp[i][j] = 0;

                // now decode the new expressions
                if(j_minus_pos_ele <=max_sum && j_minus_pos_ele >=max_neg_sum)
                {
                    if(j_minus_pos_ele < 0)
                    {
                        j_minus_pos_ele = max_sum +(j_minus_pos_ele*-1);
                    }
                    dp[i][j] += dp[i-1][j_minus_pos_ele];
                }
                if(j_plus_neg_ele <=max_sum && j_plus_neg_ele >=max_neg_sum)
                {
                    if(j_plus_neg_ele < 0)
                    {                        
                        // this is also needed, because j_actual can be negative
                        j_plus_neg_ele = max_sum + (j_plus_neg_ele*-1);
                    }
                    dp[i][j] += dp[i-1][j_plus_neg_ele];
                }
                //cout<<"Indexes are "<<j_minus_pos_ele<<" "<<j_plus_neg_ele<<endl;
                // all indexes are positive at this point
                // if(j_minus_pos_ele>=0 && j_minus_pos_ele <=max_range)
                // {
                //     dp[i][j] += dp[i-1][j_minus_pos_ele];
                // }

                // if(j_plus_neg_ele>=0 && j_plus_neg_ele <=max_range)
                // {
                //     dp[i][j] += dp[i-1][j_plus_neg_ele];
                // }

                //dp[i][j] = dp[i-1][j_minus_pos_ele] + dp[i-1][j_plus_neg_ele];
            }
        }
        if(target < 0)
        {
            target = max_sum + (target*-1);
        }
        return dp[n][target];
    }
};
