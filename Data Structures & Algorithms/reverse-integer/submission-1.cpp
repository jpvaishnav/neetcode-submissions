class Solution {
public:
    int reverse(int x) {
        /*
        string approach: convert x to string s
        s.reverse()
        if s > string(INT_MAX) then return 0, otherwise return s with + or - sign

        but need to solve question using bitmap.
        - Given bit map representation of number, how to get reverse of number using bitmap?
        12: 1100 -> 21: 10101
        13: 1101 -> 31: 11111

        // Need better solution here from bit patterns of number


        */
        int positive_x = x;
        if(x < 0) 
        {
            positive_x = -1*x;
        }
        string s = to_string(positive_x);
        string int_max_str = to_string(INT_MAX);
        std::reverse(s.begin(), s.end()); // trim initial zero?
        if(s.length() > int_max_str.length())
        {
            return 0;
        }
        if(s.length() == int_max_str.length() && s > int_max_str)
        {
            return 0;
        }

        int reversed_int = std::stoi(s);
        if(x<0)
        {
            return (-1)*reversed_int;
        }
        return reversed_int;
    }
};
