class Solution {
public:
    int characterReplacement(string s, int k) {
        /*

        Question explanation by AI:
        final answer should have only 1 character like AA, AAAAA, XXXXXXX, etc
        observation: in a given window -> we try to find top frequency element,
        its count, and try to adjust other elements around the top frequent ones.

        hint from AI:
            - Use a sliding window with left and right pointer
            - when we expand towards right,
                - check if
                - total elements in current window - count of most frequent element <= k
                - visualize this on array index platform
                - that means expansion is valid
            Otherwise move left
        */

        int n = s.size();
        if(n <= 1)
        {
            return n;
        }

        int left = 0;
        int right = 0;
        int count[26] = {0};
        int maxCount = 0;
        char maxCountChar;

        int ans = INT_MIN;

        for(int i = 0; i < n ; i++)
        {
            // move right
            right = i;
            char right_char = s[right];
            count[right_char-'A']++;
            if(count[right_char - 'A'] > maxCount)
            {
                maxCount = count[right_char - 'A'];
                maxCountChar = right_char;
            }
            // first check count condition, and keep moving left until not satisfied
            int total_count = right-left+1;
            while(total_count - maxCount > k)
            {
                char left_char = s[left];
                count[left_char-'A']--;
                left++;
                // update maxChar, maxCount if affected
                // reset maxCount here
                maxCount = 0;
                for(int j = 0; j < 26; j++)
                {
                    if(count[j] > maxCount)
                    {
                        maxCount = count[j];
                        maxCountChar = left_char;
                    }
                }
                total_count = right-left+1;
            }
            ans = max(ans, right-left+1);
        }

        return ans;

    }
};
