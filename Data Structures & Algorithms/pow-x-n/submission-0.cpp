class Solution {
public:
    double myPow(double x, int n) {
        /*
        Approach: Naive solution is to run a loop n times, and each time do curr = curr * x;
        Optimized from naive: if we already have x2, then we dont need to do x2*x*x
            - this can be simplified by x2*x2
        Idea:
            - similar to search in inifinite sorted array problem, where we double down(*2) the index
            every time, here we need to do double down the number in every iteration
                - 3 -> 3*3 (2 times) -> 3*3*3*3 (4 times) -> 3^8
            - downside of this is n could be anywhere between two powers
            - Apply backtrack: given n:
                - compute x^n/2 recursively,
                    - and do x^(n/2) * x^(n/2)
                        - based on even and odd, update the computation.
                        if n id odd, then x*x(n/2)*x(/2) 
        -Time complexity: O(log2N) -> since splitting into half in every iteration
        Another pattern here is : reuse the computation value.
        */
        if(n==0)
        {
            return 1;
        }
        if(n==-1)
        {
            return (1/x);
        }
        if(n==1)
        {
            return x;
        }
        double subPower = myPow(x, n/2);
        if(n%2 != 0)
        {
            if(n < 0)
            {
                return (1/x)*subPower*subPower;
            }
            else
            {
                return x*subPower*subPower;
            }
        }
        return subPower*subPower;
    }
};
