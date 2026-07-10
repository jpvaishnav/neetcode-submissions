class Solution {
public:

    void backTrack(vector<int>& nums,
                vector<vector<int>> & ans,
                vector<int> & solution,
                int i,
                int n,
                bool prev_included)
    {
        if(i==n)
        {
            // cout<<"Inserting solution"<<endl;
            for(auto ele: solution)
            {
                cout<<ele<<" ";
            }
            cout<<endl;
            ans.push_back(solution);
            return;
        }

        bool inclusion_needed = true;
        if(i>0 && nums[i] == nums[i-1] && prev_included == false)
        {
            inclusion_needed = false;
        }

        // include ith
        // given array has unique integars,
        // it had duplicate integars, then we might have to check element existence using hash table in O(1)
        
        if(inclusion_needed == true)
        {
            solution.push_back(nums[i]);
            //cout<<"pushing "<<i<<" "<<nums[i]<<endl;
            backTrack(nums, ans, solution, i+1, n, true);
            solution.pop_back();
            //cout<<"popping "<<i<<" "<<nums[i]<<endl;
        }
        
        // if(i>0 && nums[i]==nums[i-1])
        // {
        //     cout<<"cutting branch at "<<i<<" for "<<nums[i]<<endl;
        //     return;
        // }
        backTrack(nums, ans, solution, i+1, n, false);

        return;
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        /*
        Approach: derived from example on {1,2,1} + previous backtracking solution of subset

        // from tree of {1,2,1} found that for repeat element, we have to be careful in inclusion-exclusion
        sort the array
        and for repeat elements:
            - keep on including them
            - exclude only once
                - duplicate exclusion creates duplicate subsets
        example: {1,1,1,1,2,2}
        {}
        {1}
        {1,1}
        {1,1,1}
        {1,1,1,1}

         The Core Logic Behind prev_includedWhen an array has duplicates (like [1, 1, 1]), elements of the same value lose their individual identity. Choosing the first 1 and skipping the second 1 produces the exact same subset ([1]) as skipping the first 1 and choosing the second 1.To prevent these duplicates, we must enforce a strict structural rule: You can only include a duplicate element if its identical predecessor was also included.Valid Order (Continuous Block): [Include, Include, Exclude] \(\rightarrow \) [1, 1] ✅Invalid Order (Gaps/Skipping): [Exclude, Include, Include] \(\rightarrow \) [1, 1] ❌ (This duplicates the valid block above).

                                Index 0: nums[0] = 1
                                /       \
                      (L) prev=true   (R) prev=false
                              /           \
                             /             \
             Index 1: nums[1] = 1         Index 1: nums[1] = 1
                 /          \                 \
       (L) prev=true   (R) prev=false       (R) prev=false (L is PRUNED! 🛑)
               /              \                 \           nums[1]==nums[0] & prev_included==false
              /                \                 \
      Index 2: nums[2]=1   Index 2: nums[2]=1   Index 2: nums[2]=1
         /        \              \                 \
     (L)true   (R)false       (R)false          (R)false (L is PRUNED! 🛑)
       /          \              \                 \      nums[2]==nums[1] & prev_included==false
  [1, 1, 1]     [1, 1]          [1]                []

     |            |              |                 |
  (Goes to     (Goes to       (Goes to          (Goes to
  nums[3]=2)   nums[3]=2)     nums[3]=2)        nums[3]=2)

        */

        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        vector<int> solution;
        int n = nums.size();
        backTrack(nums, ans, solution, 0, n, false);

        return ans;
    }
};
