class Solution {
public:
    bool isPalindrome(string s) {
        // Algo
        /*
        left pointer, right pointer
        if doesnt match -> return false // early exit
        skip non alpha numeric ones in same loop -> single traversal
        */

        int left_pointer = 0;
        int right_pointer = s.size() - 1;
        while(left_pointer < right_pointer)
        {
            // left_pointer == right_pointer is same character, so valid palindrom
            // trim non-alpha numeric
            while(left_pointer < right_pointer && isalnum(s[left_pointer]) == false)
            {
                left_pointer++;
            }
            while(left_pointer < right_pointer && isalnum(s[right_pointer]) == false)
            {
                right_pointer--;
            }
            //cout << s[left_pointer] << " " << s[right_pointer] << endl;
            // case insenstive -> check tolower
            if(tolower(s[left_pointer]) != tolower(s[right_pointer]))
            {
                return false;
            }
            left_pointer++;
            right_pointer--;
        }
        return true;
    }
};
