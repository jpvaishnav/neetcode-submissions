class Solution {
public:

    bool isValid(string s)
    {
        stack<char> st;

        for(int i=0; i<s.size(); i++)
        {
            char c = s[i];
            if(c== '(')
            {
                st.push(c);
            }
            else if(c==')')
            {
                if(st.empty() || st.top()!='(')
                {
                    return false;
                }
                st.pop();
            }
            // ignore *
        }
        return st.empty();
    }
    bool checkValidString(string s) {
        /*
        Approach: Backtracking approach
            Iterate over string, and on every *
            apply 3 possibilities - empty, opening and closing
            and the check using stack approach - isValid
            O(3^n)

            Another approach:
                count number of opening brackets, closing brackets, and *
                eliminate incorrect ones like closing >opening + * count
                //check violation condition on existing substrings
                    like ())**
                Now, iterate over stars, and update them to fix count
                    but order also matters
                    so, check stack as well
                    If only 1 bracket or empty option, then time complexity is
                    O(2^n)

        Prompt to AI:
            for valid paranthese question, can you give hit for solution in O(n), only provide hint and the technique to optimize like should I dry run on few iterations, should I derived optimized solution from example or etc. 
            should save them in a skill or prompt file
            Idea is, we dont get direct solution for a problem,
                but the path of how to reach the solution
            
            The Core HintInstead of trying to decide exactly what each * should be during your iteration, track the range of possible open brackets that could exist at any given moment.A * is flexible: it can increase the open count, decrease it, or leave it unchanged.Think about maintaining a min_open and a max_open count simultaneously as you scan from left to right.

            The Core Rules for the RangeAs you loop through the string from left to right, adjust your range based on the character:( : Increments both min_open and max_open. (More open brackets).) : Decrements both min_open and max_open. (Brackets are being closed).* : It can be ), empty, or (.To minimize open brackets, treat it as ) \(\rightarrow \) decrement min_open.To maximize open brackets, treat it as ( \(\rightarrow \) increment max_open.

            Isn't it similar to train railway platform or meeting counter approach?

            Why it is a Greedy AlgorithmA greedy algorithm makes the locally optimal choice at each stage with the hope of finding a global optimum, without ever looking back or backtracking.
            In this problem, the greedy choice happens at every single character you process:Greedy Maximization (max_open): At every step, you greedily assume the best-case scenario for keeping the string alive. 
            Every time you see a *, you greedily treat it as a ( to see how far you can push the upper limit. 
            If even this ultra-optimistic greedy assumption fails (max_open < 0), you confidently abandon the search immediately.
            Greedy Minimization (min_open): Simultaneously, you greedily try to close as many brackets as possible to see if you can handle future closing brackets. 
            When min_open dips below 0, you make a local correction: you greedily "absorb" the violation by changing a previous flexible choice (a *) from a ) to an empty space or a (, resetting the floor to 0.

            As you loop through the string from left to right, 
            adjust your range based on the character:
                ( : Increments both min_open and max_open. (More open brackets).
                ) : Decrements both min_open and max_open. (Brackets are being closed).
                * : It can be ), empty, or (.
                    To minimize open brackets, treat it as ) \(\rightarrow \) decrement min_open.
                    To maximize open brackets, treat it as ( \(\rightarrow \) increment max_open.
        Too many closing brackets: If max_open < 0, it means even if you turned every single * into a (, you still have too many ) brackets. Return false immediately.Floor constraint: min_open cannot drop below 0. If a * or a ) forces min_open to become negative, reset it to 0. This just means you choose to treat that * as empty or ( instead of ) to keep the prefix valid.Final Check: At the very end of the string, if 0 lies within your valid range (i.e., min_open == 0), the string is valid.

        To understand why min_open resets to 0 when it becomes negative, we need to remember what min_open represents.min_open is the absolute minimum number of open brackets you could possibly have if you aggressively used every * to close brackets or leave them empty.If min_open goes negative, it means your choices were too aggressive, resulting in too many closing brackets. Since a negative number of open brackets is physically impossible in a valid prefix, you must immediately make a local correction. You choose to treat one of those previous * characters as a ( or empty string instead of a ), which pulls your minimum back up to 0.


        */

        // this is like choosing corner most greedy option for local maximisation
        // diagram - https://github.com/jpvaishnav/Profile/blob/main/images/valid_paranthese_greedy.jpg

        int min_open = 0;
        int max_open = 0;
        for(auto c: s)
        {
            if(c=='(')
            {
                min_open++;
                max_open++;
            }
            if(c==')')
            {
                min_open--;
                max_open--;
            }
            if(c=='*')
            {
                max_open++; // c=='('
                min_open--; // c==')'
            }

            if(max_open < 0)
            {
                // closing brackets are greater than opening brackets
                return false;
            }
            if(min_open <0)
            {
                min_open = 0;
                // correcting a local choice for * which was choose as closing bracket )
                // but now we are replacing it by empty
            }
        }

        return (min_open == 0);
        // int opening_brackets = 0;
        // int closing_brackets = 0;
        // int stars = 0;
        // for(auto c: s)
        // {
        //     if(c == '(')
        //     {
        //         opening_brackets++;
        //     }
        //     else if(c==')')
        //     {
        //         closing_brackets++;
        //     }
        //     else
        //     {
        //         stars++;
        //     }
        //     if(closing_brackets > opening_brackets + stars)
        //     {
        //         // )))(**)
        //         return false;
        //     }
        // }

        // for(int i=0; i<s.size(); i++)
        // {
        //     if(s[i] == '*')
        //     {
        //         if(opening_brackets>closing_brackets)
        //         {
        //             s[i]=')';
        //             closing_brackets++;
        //         }
        //         else if(closing_brackets > opening_brackets)
        //         {
        //             s[i]='(';
        //             opening_brackets++;
        //         }
        //         else
        //         {
        //             // no-op
        //         }
        //     }

        //     if(opening_brackets == closing_brackets)
        //     {
        //         if(isValid(s))
        //         {
        //             return true;
        //         }
        //     }
        // }

        // return false;


    }
};
