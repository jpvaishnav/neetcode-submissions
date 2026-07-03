class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        /*
        Approach: Sliding window or 2 pointers algorithm
        where 2 pointers window_start and window_end will be maintained
        And maintain count[256] that is frequency map of 256 ASCII characters
        in each iteration, we increment window_end
        and if count[window_end] already exists to an index inside the array
        then we update window_start to that index, so that updated window won't have any duplicate characters

        time complexity: O(n)
        Aux space: O(256)
        */
        int window_start = 0;
        int window_end = 0;
        int count[256]; // to store latest index of a character in string
        for(int i = 0; i < 256; i++)
        {
            count[i] = -1;
        }

        int ans = 0;

        for(int i=0; i < s.size(); i++)
        {
            window_end = i;
            int char_index = int(s[i]); // int() gives ascii value
            if(count[char_index] != -1 && window_start <= count[char_index])
            {
                // why window_start <= count[char_index] this condition
                // because if your current window_start is greater than index of your frequent character
                // Then, it doesn't matter. draw/visualise window_start and count[char_index] on index line
                //cout << "updating window_start "<< s[i] << " " << count[char_index]<<endl;
                // s[i] already exists in current window, so need to update window_start
                // so that s[i] is exlcuded
                window_start = count[char_index]+1;
            }

            count[char_index] = i;

            // update ans
            cout << "char " << s[i] << " "<< window_start << " " << window_end << endl;
            ans = max(ans, window_end-window_start+1);
        }

        return ans;
    }
};
