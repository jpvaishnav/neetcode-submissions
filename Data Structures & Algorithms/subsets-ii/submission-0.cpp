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
            cout<<"Inserting solution"<<endl;
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
            cout<<"pushing "<<i<<" "<<nums[i]<<endl;
            backTrack(nums, ans, solution, i+1, n, true);
            solution.pop_back();
            cout<<"popping "<<i<<" "<<nums[i]<<endl;
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
        */

        sort(nums.begin(), nums.end());
        for(auto num: nums)
        {
            cout << num<< endl;
        }
        vector<vector<int>> ans;
        vector<int> solution;
        int n = nums.size();
        backTrack(nums, ans, solution, 0, n, false);

        return ans;
    }
};
