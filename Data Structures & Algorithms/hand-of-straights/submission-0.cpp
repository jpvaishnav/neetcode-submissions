class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        /*
        Approach:
        similar to longest consecutive subsequence in an array:
            HashMap was used.
        - put all elements in HashTable of <element, frequency>
        In each iteration,
            pick min from elements which have frequency > 0
            check if currMin+1, currMin+2, currMin+n exists
                - if any of them does not exist, return false
                because need to re-arrange all cards
                - and with currMin, this is not possible
        */

        unordered_map<int, int> freqMap;
        for(auto card: hand)
        {
            freqMap[card]++;
        }

        while(true)
        {
            // get min value with >0 frequency
            int min_card = INT_MAX;
            for(auto p: freqMap)
            {
                if(p.second > 0)
                {
                    min_card = min(min_card,p.first);
                }
            }
            if(min_card == INT_MAX)
            {
                // all elements are covered
                return true;
            }
            freqMap[min_card]--;
            for(int i=1; i<groupSize; i++)
            {
                int next_card = min_card+i;
                if(freqMap.find(next_card) == freqMap.end()
                    || freqMap[next_card] == 0)
                {
                    // next_card does not existor used in other group
                    return false;
                }
                freqMap[next_card]--;
            }
        }
    }
};
