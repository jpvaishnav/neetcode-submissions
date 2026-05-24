class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        // since array is sorted, so we can use two-pointer alog here
        // In unsorted use hash table
        vector<int> ans;
        int n = numbers.size();
        int left_pointer = 0;
        int right_pointer = n-1;
        while(left_pointer <= right_pointer)
        {
            int curr_sum = numbers[left_pointer] + numbers[right_pointer];
            // Put curr_sum on comparison platform against target sum
            if(curr_sum == target)
            {
                ans.push_back(left_pointer+1);
                ans.push_back(right_pointer+1);
                // since exact one solution exists, return here
                return ans;
            }
            else if(curr_sum < target)
            {
                left_pointer++;
                // Move towards target
            }
            else
            {
                right_pointer--;
            }
        }

        // Although given constraint(exact 1 solution) wont reach here, keeping it to have valid function return type
        return ans;
    }
};
