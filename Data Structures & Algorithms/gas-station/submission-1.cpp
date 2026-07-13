class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        /*
        Approach: greedy
        in knapsack, optimization was value/weight at every point
        in this problem, optimisation is available gas at every point
            that is gas[i] - cost[i]
            call it netGas[i]
            maintain availableGas global veriable
            and while iterating,
                - if availableGas becomes -ve, then reset start point
                    - similar to Kadane's algo,
                        - if availableGas is becoming negative,
                        that means current status has negative netGas,
                        so no need to include current station, start from next station
            since, cycle is possible, so keep previousGas in a variable,
            so that end of the point, cycle completion can be checked
        */

        int n = gas.size();
        vector<int> netGas(n);
        for(int i=0; i<n; i++)
        {
            netGas[i] = gas[i] - cost[i];
        }

        int availableGas = 0;
        int previousGas = 0;
        int start_index = 0;
        for(int i=0; i<n; i++)
        {
            availableGas = availableGas + netGas[i];
            if(availableGas < 0)
            {
                previousGas = previousGas + availableGas;
                availableGas = 0;
                start_index = i+1;
            }
        }

        if( availableGas + previousGas >=0)
        {
            return start_index;
        }
        return -1;
    }
};
