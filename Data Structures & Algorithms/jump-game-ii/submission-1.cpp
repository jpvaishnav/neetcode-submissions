class Solution {
public:
    int jump(vector<int>& nums) {
        /*
        Approach: maintain minJump array similar to dist array
            and apply edge relaxation
            minJump[j] = min(minKump[j], minJump[i] + 1)

        time complexity: O(n * m)
        what is greedy here?
        */

        int  n = nums.size();
        vector<int> minJump(n, INT_MAX);

        minJump[0] = 0;

        for(int i=0; i<n; i++)
        {
            if(minJump[i] == INT_MAX || minJump[i] >= minJump[n-1])
            {
                //early exit condition
                continue;
            }
            int jump = i+nums[i];
            for(int j=i+1; j<=jump && j<n; j++)
            {
                minJump[j] = min(minJump[j], minJump[i]+1);
            }
        }

        return minJump[n-1];
    }
};
