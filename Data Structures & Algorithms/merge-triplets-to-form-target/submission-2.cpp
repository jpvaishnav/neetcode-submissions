class Solution {
public:
    bool mergeTriplets(vector<vector<int>>& triplets, vector<int>& target) {
        /*
        Naive algorithm:
        at every pointer, 2 options - include-exclude principle
        create 2 branches-
            include current set in target, and merge
            exclude current set from target
        In the end, when leaf is reached, check if merged tripelt is equal to target triplet
        Time:O(2^n) = O(2^1000)

        Can we apply same technique here, 
        similar to range based technique in last question of valid parathesis?
        maintain include_a, include_b, include_c, and apply max
        and exclude_a, exclude_b, exclude_c
        this one is not working

        be greedy at local path?

        sort all entries by first element in decreasing order,
            and then second element, and so on

        or create group of a, group of b, group of c

        Based on AI(Gemini) hint:
        - what if we merge all triplets(extreme of greedy, picking all max)?
        triplets =

        [[2,5,3],[1,8,4],[1,7,5]]
        target =

        [2,7,5]

        failed
        because [1,8,4] is outlier, where one element(8) is greater than target,
            so detect & remove outliers

        */

        vector<int> merged(3, INT_MIN);

        for(auto triplet: triplets)
        {
            if(triplet[0]>target[0] || 
                triplet[1]>target[1] ||
                triplet[2]>target[2])
            {
                // don't merge
                continue;
            }
            merged[0] = max(merged[0], triplet[0]);
            merged[1] = max(merged[1], triplet[1]);
            merged[2] = max(merged[2], triplet[2]);
            if(merged[0] == target[0] && merged[1] ==target[1] && merged[2] == target[2])
            {
                return true;
            }
            //early exit
        }

        //cout<< merged[0]<<" "<<merged[1]<<" "<<merged[1]<<endl;

        if(merged[0] == target[0] && merged[1] ==target[1] && merged[2] == target[2])
        {
            return true;
        }
        return false;

    }
};
